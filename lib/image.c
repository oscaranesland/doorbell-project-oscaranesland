#include <stdlib.h>
#include <string.h>

#include "image.h"

uint8_t create_bmp(Bitmap *dst, uint8_t *src) {
    int offset = 0;
    dst->img = NULL;

    // Copy in the bitmap file header
    memcpy(dst->file_header, src, BMP_FILE_HEADER_SIZE);
    offset += BMP_FILE_HEADER_SIZE;

    // Get filesize
    dst->file_size = (dst->file_header[5] << 8 * 3) | (dst->file_header[4] << 8 * 2) |
                     (dst->file_header[3] << 8 * 1) | (dst->file_header[2]);

    // Get start location of pixel data
    dst->pxl_data_offset = (dst->file_header[13] << 8 * 3) | (dst->file_header[12] << 8 * 2) |
                           (dst->file_header[11] << 8 * 1) | (dst->file_header[10]);

    // // Get DIB header data
    uint8_t dib_header_size = dst->pxl_data_offset - BMP_FILE_HEADER_SIZE;
    dst->dib_header = (uint8_t *)malloc((dib_header_size) * sizeof(uint8_t));
    memcpy(dst->dib_header, src + offset, dib_header_size);
    offset += dib_header_size;

    // Get image width
    dst->img_width = (dst->dib_header[7] << 8 * 3) | (dst->dib_header[6] << 8 * 2) |
                     (dst->dib_header[5] << 8 * 1) | (dst->dib_header[4]);

    // Get image height
    dst->img_height = (dst->dib_header[11] << 8 * 3) | (dst->dib_header[10] << 8 * 2) |
                      (dst->dib_header[9] << 8 * 1) | (dst->dib_header[8]);

    if (dst->img_height < 0) {
        dst->img_height *= -1;
    }

    // Get image data
    dst->pxl_data_size = dst->img_width * dst->img_height * 3;
    dst->pxl_data = malloc(sizeof(uint8_t) * dst->pxl_data_size);
    memcpy(dst->pxl_data, src + offset, dst->pxl_data_size);

    // Create copy of image data for reset
    dst->pxl_data_cpy = malloc(sizeof(uint8_t) * dst->pxl_data_size);
    memcpy(dst->pxl_data_cpy, dst->pxl_data, dst->pxl_data_size);

    return LOAD_SUCCESS;
}

void destroy_bmp(Bitmap *bmp) {
    free(bmp->dib_header);
    free(bmp->pxl_data);
    free(bmp->pxl_data_cpy);
}

void reset_pixel_data(Bitmap *bmp) {
    bmp->pxl_data = memcpy(bmp->pxl_data, bmp->pxl_data_cpy, bmp->pxl_data_size);
}

uint8_t *get_pxl_data(Bitmap *bmp) { return bmp->pxl_data; }

uint8_t *get_original_pxl_data(Bitmap *bmp) { return bmp->pxl_data_cpy; }

void or_filter(Bitmap *bmp) {

    int width  = bmp->img_width;
    int height = bmp->img_height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            int pixel = (y * width + x) * 3;

            for (int i = 0; i < 3; i++) {

                uint8_t result = bmp->pxl_data_cpy[pixel + i];

                if (y > 0) {
                    int up_pixel = ((y - 1) * width + x) * 3;
                    result |= bmp->pxl_data_cpy[up_pixel + i];
                }

                if (y < height - 1) {
                    int down_pixel = ((y + 1) * width + x) * 3;
                    result |= bmp->pxl_data_cpy[down_pixel + i];
                }

                bmp->pxl_data[pixel + i] = result;
            }
        }
    }
}

void remove_color_channel(Color color, Bitmap *bmp) {
    // Put
    int siz = (bmp->pxl_data_size)/3;
    for (int x = 0; x<(siz);x++){
    //int x=0;
    //(bmp->pxl_data_size)/3
    //while(x<(bmp->pxl_data_size)){
        if (color == BLUE_CHANNEL){
        (bmp->pxl_data[x*3])=0; //blue

        //uint8_t green = bmp->pxl_data[x+1];
        //uint8_t red = bmp->pxl_data[x+2];
        }
        else if (color == GREEN_CHANNEL){
            //uint8_t blue = bmp->pxl_data[x]
            (bmp->pxl_data[x*3+1])=0; //green
            //uint8_t red = bmp->pxl_data[x+2]
            }
        else if (color == RED_CHANNEL){//RED
                //uint8_t blue = bmp->pxl_data(x)
                //uint8_t green = bmp->pxl_data[x+1]
                (bmp->pxl_data[x*3+2])=0; //red
            }
            //x++;
        }
        
}