#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

static int padding(int x) {
    const int padding_size = 4;

    int extra = x % padding_size;
    if (extra == 0)
        extra = padding_size;
    return x + padding_size - extra;
}

static int set_size(BMP_header* header, int h, int w) {
    header->height = h;
    header->width = w;
    header->image_size = h * padding(w * sizeof(pixel));
    header->bf_size = sizeof(BMP_header) + header->image_size;
    return header->image_size;
}

pixel get_pixel(BMP_header* image_header, pixel* image, int x, int y) {     // used in stego.c
    int true_width = padding(image_header->width * sizeof(pixel));
    return ((pixel *)((void *)image + true_width * y))[x];
}

void set_pixel(BMP_header* image_header, pixel* image, int x, int y, pixel new_pixel) {     // used in stego.c
    int true_width = padding(image_header->width * sizeof(pixel));
    ((pixel *)((void *)image + true_width * y))[x] = new_pixel;
}

int load_bmp(FILE* input, BMP_header* image_header, pixel** image) {
    fread(image_header, sizeof(BMP_header), 1, input);
    *image = calloc(1, set_size(image_header, image_header->height, image_header->width));
    if (*image == NULL)
        return -1;
    fseek(input, image_header->bits_offset, 0);
    fread(*image, image_header->bf_size - image_header->bits_offset, 1, input);
    return 0;
}

int crop(pixel* image, pixel** crop_image, int x, int y, int h, int w,
          BMP_header* image_header, BMP_header* crop_header) {
    *crop_header = *image_header;
    *crop_image = calloc(1, set_size(crop_header, h, w));
    if (*crop_image == NULL)
        return -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            set_pixel(crop_header, *crop_image, j, h - i - 1,
                      get_pixel(image_header, image, x + j, y - i));
    }
    return 0;
}

int rotate(BMP_header* image_header, pixel* image, BMP_header* rotate_header, pixel** rotate_image) {
    *rotate_header = *image_header;
    *rotate_image = calloc(1, set_size(rotate_header, image_header->width, image_header->height));
    if (*rotate_image == NULL)
        return -1;
    for (int i = 0; i < image_header->height; i++) {
        for (int j = 0; j < image_header->width; j++)
            set_pixel(rotate_header, *rotate_image, i, image_header->width - j - 1,
                      get_pixel(image_header, image, j, i));
    }
    return 0;
}

void save_bmp(FILE* output, BMP_header* image_header, pixel* image) {
    fwrite(image_header, sizeof(BMP_header), 1, output);
    fseek(output, image_header->bits_offset, 0);
    fwrite(image, image_header->bf_size - image_header->bits_offset, 1, output);
}