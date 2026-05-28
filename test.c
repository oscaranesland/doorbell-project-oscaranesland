#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/buttons.h"
#include "lib/colors.h"
#include "lib/device.h"
#include "lib/display.h"
#include "lib/fonts/fonts.h"
#include "lib/log.h"

#define VIEWER_FOLDER "viewer/"
#define MAX_ENTRIES 8
#define MAX_TEXT_SIZE 400
#define MAX_FILE_NAME 100

// Colors — Feel free to change these to fit your preference
#define BACKGROUND_COLOR WHITE
#define FONT_COLOR BLACK
#define SELECTED_BG_COLOR BYU_BLUE
#define SELECTED_FONT_COLOR BYU_LIGHT_SAND

#define NUM_ENTRIES 5
#define MAX_ENTRY_LENGTH 20

char entries[NUM_ENTRIES][MAX_ENTRY_LENGTH] = {"Clear", "Hello", "Chars", "Stars", "Flag"};

// Makes sure to deinitialize everything before program close
void intHandler(int dummy) {
    log_info("Exiting...");

    // Resets the Screen
    display_clear(BLACK);
    display_draw_string(5, 5, "Goodbye!", &Font16, BLACK, WHITE);
    //display_draw_string(20, 20, "Goodbye2!", &Font16, BLACK, WHITE);


    // Releases control of the display
    display_exit();
    exit(0);
}

// clearScreen
//
//
// Clears the screen to white.
void clearScreen() {
    // TODO: Put your code hereif (button_up() == 0) {

        // Do something while the button is pressed
        display_clear(WHITE);
        delay_ms(1);
}

   


// drawHelloWorld
//
// Draws "Hello World!" on the display 10 times
// Make each line a different color
void drawHelloWorld() {
    display_draw_string(10,10, "HELLO WORLD!", &Font8, WHITE, BLACK);
    display_draw_string(10,20,"HELLO WOLRD!", &Font12, BYU_LIGHT_SAND, BYU_BLUE);
    display_draw_string(10,30, "HELLO WORLD!", &Font24, WHITE, BYU_BLUE);
    display_draw_string(10,40, "HELLO WORLD!", &Font8, WHITE, BYU_LIGHT_SAND);
    display_draw_string(10,50, "HELLO WORLD!", &Font8, BYU_BLUE, ORANGE);
    display_draw_string(10,60, "HELLO WORLD!", &Font12, BYU_LIGHT_SAND, BLACK);
    display_draw_string(10,70, "HELLO WORLD!", &Font16, BYU_BLUE, PURPLE);
    display_draw_string(10,80, "HELLO WORLD!", &Font8, WHITE, GREEN);
    display_draw_string(10,90, "HELLO WORLD!", &Font8, WHITE, YELLOW);
    display_draw_string(10,100, "HELLO WORLD!", &Font20, WHITE, RED);
    // TODO: Put your code here
}

// drawChars
//
// Draw chars of different values, sizes, colors, and locations onto the screen
void drawChars() {
    // TODO: Put your code here
    display_draw_string(10,100, "C", &Font8, WHITE,BLACK);
    display_draw_string(20,100, "h",&Font20, BYU_BLUE,BLACK);
    display_draw_string(30,100,"P",&Font12, BYU_EGGPLANT, BYU_BLUE_GRAY);
    display_draw_string(50,100, "T",&Font16, BYU_BURGUNDY, BYU_PLUM);
    display_draw_string(70,100, "o",&Font16, BYU_BURGUNDY, BLACK);
    display_draw_string(50,100, "3",&Font20, BYU_BLUE,BYU_BURGUNDY);
    display_draw_string(80,100, "1",&Font12, BYU_BURGUNDY,BYU_EGGPLANT);
    display_draw_string(50,50, "R",&Font16, BYU_BURGUNDY, BYU_LIGHT_SAND);
    display_draw_string(100,100, "J",&Font8, BYU_BURGUNDY, WHITE);
    display_draw_string(120,100, "S",&Font16, BYU_BURGUNDY, BYU_BLUE);
}

// drawStars
//
// Draw at least 20 stars on the screen
// TIP: Make a function that uses display_draw_# functions to make the shape of the star,
// Then call that function at multiple locations
void drawStars() {
    // TODO: Put your code here
    display_draw_string(83,92, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(51,18, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(50,76, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(52,87, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(72,107, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(59,103, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(54,102, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(80,110, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(50,98, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(26,67, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(53,36, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(60,17, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(80,10, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(20,16, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(60,80, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(10,64, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(90,90, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(100,60, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(23,90, "*",&Font16, BYU_BURGUNDY,BLACK);
    display_draw_string(67,10, "*",&Font16, BYU_BURGUNDY,BLACK);
}


// drawFlag
//
// Use at least 5 other display_draw functions to make any flag you want.
// It must have at least 3 colors, and use 3 unique display_draw functions
void drawFlag() {;
    display_clear(DARK_RED);
    display_draw_rectangle(40,0,20,120,WHITE,true,1);
    display_draw_rectangle(0,50,128,20,WHITE,true,1);
    display_draw_rectangle(40,0,10,120,BYU_BLUE, true, 1);
    display_draw_rectangle(0,50,128,10,BYU_BLUE,true, 1);
    // TODO: Put your code here
}

// draw_menu
//
// Draw the menu of the screen. It uses the entries array to create the menu, with the num_entries
// specifying how many entries are in the entries array. The selected parameter is the item in the
// menu that is selected and should be highlighted. Use BACKGROUND_COLOR, FONT_COLOR,
// SELECTED_BG_COLOR, and SELECTED_FONT_COLOR to help specify the colors of the background, font,
// select bar color, and selected text color.
void drawMenu(char entries[][MAX_ENTRY_LENGTH], int num_entries, int selected) {
    // TODO: Put your code here
    int x=0;
    int y=0;
    for(int i=0; i<num_entries;i++){
        if (i == selected){
            display_draw_rectangle(x,y,DISPLAY_WIDTH,10+y, BYU_BLUE,true,1);
            display_draw_string(x,y,entries[i],&Font8, SELECTED_BG_COLOR, SELECTED_FONT_COLOR);
            
        }
        else{
            display_draw_rectangle(x,y,DISPLAY_WIDTH,10+y, BACKGROUND_COLOR,true,1);
            display_draw_string(x,y,entries[i],&Font8,BACKGROUND_COLOR,FONT_COLOR);
        }
        y+=10;
    }
}   



int main(void) {
    display_init();
    buttons_init();
    clearScreen();
    int i = 0;
    drawMenu(entries, NUM_ENTRIES,i);
    signal(SIGINT, intHandler);

    log_info("Starting...");
    
    
    while (true) {
        delay_ms(200);
        if (button_up() == 0) {
            // Do something upon detecting button press
                ++i;
                if (i>NUM_ENTRIES){
                    i=0;
                };
                drawMenu(entries,NUM_ENTRIES,i);
            while (button_up() == 0) {
                // Delay while the button is pressed to avoid repeated actions
                delay_ms(100);
                ++i;
                if (i>NUM_ENTRIES){
                    i=0;
                };
                drawMenu(entries,NUM_ENTRIES,i);
            }
        }
        if (button_down() ==0){
            drawMenu(entries,NUM_ENTRIES,--i);
                --i;
                if (i<0){
                    i=4;
                };
                drawMenu(entries,NUM_ENTRIES,i);
            
            while (button_down() ==0){
                delay_ms(100);
                --i;
                if (i<0){
                    i=4;
                };
                drawMenu(entries,NUM_ENTRIES,i);
            }
        }
        if (button_right() == 0){
            if (i == 0){
                clearScreen();
            }
            if (i == 1){
                clearScreen();
                drawHelloWorld();
            }
            if (i == 2){
                clearScreen();
                drawChars();
            }
            if (i == 3){
                clearScreen();
                drawStars();
            }
            if (i == 4){
                clearScreen();
                drawFlag();
            }
            }
        if (button_left() ==0){
            clearScreen();
            int i = 0;
            drawMenu(entries,NUM_ENTRIES,i);
        }
            
        }
        // Implement other button logic here
    }

