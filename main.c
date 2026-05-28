#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/buttons.h"
#include "lib/camera.h"
#include "lib/client.h"
#include "lib/colors.h"
#include "lib/device.h"
#include "lib/display.h"
#include "lib/fonts/fonts.h"
#include "lib/image.h"
#include "lib/log.h"

#define VIEWER_FOLDER "viewer/"
#define MAX_ENTRIES 8
#define MAX_TEXT_SIZE 400
#define MAX_FILE_NAME 100

// Colors — Feel free to change these to fit your preference
#define BACKGROUND_COLOR BLACK
#define FONT_COLOR WHITE
#define SELECTED_BG_COLOR BYU_BLUE
#define SELECTED_FONT_COLOR BYU_LIGHT_SAND

// Makes sure to deinitialize everything before program close
void intHandler(int dummy) {
    log_info("Exiting...");
    display_exit();
    exit(0);
}

void combinePath(char path[], char folderName[], char fileName[]) {
    // TODO: Implement this function
    strcpy(path,folderName);
    int len = strlen(path);
    if(len>0 && path[len-1]!= '/'){
        strcat(path,"/");
    }
    strcat(path,fileName);
}
void getFileExtension(char extension[], char fileName[]) {
    char *dot = strrchr(fileName, '.');
    if (dot != NULL){
        strcpy(extension, dot+1);
    }else{
        extension[0] ='\0';
    }
}

/*
 * Takes in a folder, reads the contents of the folder, filtering out any files that do not end with
 * .log or .bmp. This function should check to make sure the folder exists. It fills in the entries
 * array with all of the entries in the folder, up to 8 (MAX_ENTRIES). The function returns the
 * number of entries it put into the entries array.
 */
int get_entries(char *folder, char entries[][MAX_FILE_NAME]) {
    // TODO: Put your code here
    DIR *dp;
    struct dirent *entry;
    int count = 0;

    dp = opendir(folder);

    if (dp == NULL) {
        return 0;
    }

    while ((entry = readdir(dp)) != NULL) {
        int len = strlen(entry->d_name);

        if (len > 4) {
            char *ext = &entry->d_name[len - 4];

            if (strncmp(ext, ".bmp", 4) == 0 || strncmp(ext, ".log", 4) == 0) {
                strcpy(entries[count], entry->d_name);
                count++;

                if (count >= 8) {
                    break;
                }
            }
        }
    }

    closedir(dp);
    return count;
}

/*
 * Draws the menu of the screen. It uses the entries array to create the menu, with the num_entries
 * specifying how many entries are in the entries array. The selected parameter is the item in the
 * menu that is selected and should be highlighted. Use BACKGROUND_COLOR, FONT_COLOR,
 * SELECTED_BG_COLOR, and SELECTED_FONT_COLOR to help specify the colors of the background, font,
 * select bar color, and selected text color.
 */
void draw_menu(char entries[][MAX_FILE_NAME], int num_entries, int selected) {
    display_clear(WHITE);
    int y = 10;
    
    for (int i = 0; i < num_entries; i++) {
        if (i == selected) {
            display_draw_rectangle(0, y, 128, y + 10, SELECTED_BG_COLOR, true, 1);
            display_draw_string(10, y, entries[i], &Font8, SELECTED_BG_COLOR, SELECTED_FONT_COLOR);
        } else {
            display_draw_string(10, y, entries[i], &Font8, FONT_COLOR, BACKGROUND_COLOR);
        }
        y = y + 15;
    }
}

/*
 * Displays an image or a log file. This function detects the type of file that should be draw. If
 * it is a bmp file, then it calls display_draw_image. If it is a log file, it opens the file, reads
 * 100 characters (MAX_TEXT_SIZE), and displays the text using display_draw_string. Combine folder
 * and file_name to get the complete file path.
 */
void draw_file(char *folder, char *file_name) {
    // TODO: Put your code here
    char path[100]; // max file name is 100
    char extension[5]; 
    combinePath(path,folder,file_name);
    getFileExtension(extension,file_name);
    if (strncmp(extension,"bmp",3)==0){
        display_draw_image(path);
    }
    else if (strncmp(extension,"log",3)==0){
        FILE *fp;
        fp = fopen(path,"r");
        if (fp != NULL){
            char data[MAX_TEXT_SIZE];
            fread(data,1,100,fp);
            data[100] ='\0';
            display_clear(WHITE);
            display_draw_string(4,10,data,&Font8,WHITE,BLACK);
            fclose(fp);
        }

    }
    }
    //char data[5
    // 0];
    //int i = 0;
    //if ()

//else{
//fread(data,1,100,fp);
//log_info(data)
//display_draw_string(0,0,data,&Font12,WHITE,BLUE);
//}
//fclose(fp)
    

int main(void) {
    signal(SIGINT, intHandler);
    char entries[MAX_ENTRIES][MAX_FILE_NAME];
    display_init();
    buttons_init();
    int num_entries = get_entries(VIEWER_FOLDER, entries);
    int current_selection = 0;
    
    if (num_entries > 0) {
        draw_menu(entries, num_entries, current_selection);
    }

    while (true) {
        delay_ms(200);

        if (num_entries > 0) {
            if (button_up() == 0) {
                current_selection = current_selection - 1;
                if (current_selection < 0) {
                    current_selection = num_entries - 1;
                }
                draw_menu(entries, num_entries, current_selection);
                while (button_up() == 0) delay_ms(1);
            }

            if (button_down() == 0) {
                current_selection = current_selection + 1;
                if (current_selection >= num_entries) {
                    current_selection = 0;
                }
                draw_menu(entries, num_entries, current_selection);
                while (button_down() == 0) delay_ms(1);
            }

            if (button_right() == 0) {
                draw_file(VIEWER_FOLDER, entries[current_selection]);
                delay_ms(2000);
                draw_menu(entries, num_entries, current_selection);
                while (button_right() == 0) delay_ms(1);
            }
            if (button_center() ==0){
                display_clear(WHITE);
                Bitmap images;
                char words[12] = ("Say Cheese!");
                display_draw_string(0,40,words,&Font12, BLACK,WHITE);

                uint8_t *my_new_buff = malloc(sizeof(uint8_t) * IMG_SIZE);
                camera_capture_data(my_new_buff,IMG_SIZE);
                camera_save_to_file(my_new_buff,IMG_SIZE,"viewer/doorbell.bmp");
                create_bmp(&images, my_new_buff);
                draw_file(VIEWER_FOLDER,"doorbell.bmp");
                
                
                
                int p =1;
                while(p){
                    if (button_right() ==0){
                        remove_color_channel(1,&images);
                        display_draw_image_data(images.pxl_data, images.img_width, images.img_height);
                        reset_pixel_data(&images);
            
                }
                    if (button_left() ==0){
                        remove_color_channel(0,&images);
                       display_draw_image_data(images.pxl_data, images.img_width, images.img_height);
                        reset_pixel_data(&images);
                }
                    if (button_up() ==0){
                        remove_color_channel(2,&images);
                        display_draw_image_data(images.pxl_data, images.img_width, images.img_height);
                        reset_pixel_data(&images);
                }
                    if (button_down() ==0){
                        or_filter(&images);
                        display_draw_image_data(images.pxl_data, images.img_width, images.img_height);
                        reset_pixel_data(&images);
                }
                    if (button_center() ==0){

                        



                        Config config;
                        config.port = "2240";
                        config.host = "ecen224.byu.edu";
                        config.payload = my_new_buff;
                        config.payload_size = IMG_SIZE;
                        config.hw_id = "A4CD3312D";
                       

                        int sockfd = client_connect(&config);
                        client_send_image(sockfd, &config);
                        client_receive_response(sockfd);
                        client_close(sockfd);

                        p = 0;
                       

                }   
                }
                


                free(my_new_buff);
                destroy_bmp(&images);
                draw_menu(entries, num_entries, current_selection);

                
            }
        }
    }
return 0;}
