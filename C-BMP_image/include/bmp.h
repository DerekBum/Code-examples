#ifndef BMP_H
#define BMP_H

typedef struct __attribute__((__packed__)) BMP_header {
    short bf_type;
    unsigned int bf_size;
    char reserved[4];
    unsigned int bits_offset;
    unsigned int size;
    int width;
    int height;
    char other_data[8];
    unsigned int image_size;
    char unused_data[16];
} BMP_header;

typedef struct __attribute__((__packed__)) pixel {
    unsigned char chanals[3];
} pixel;

pixel get_pixel(BMP_header* image_header, pixel* image, int x, int y);
void set_pixel(BMP_header* image_header, pixel* image, int x, int y, pixel new_pixel);
int load_bmp(FILE* input, BMP_header* image_header, pixel** image);
int crop(pixel* image, pixel** crop_image, int y, int x, int h, int w, BMP_header* image_header, BMP_header* crop_header);
int rotate(BMP_header* image_header, pixel* image, BMP_header* rotate_header, pixel** rotate_image);
void save_bmp(FILE* output, BMP_header* image_header, pixel* image);

#endif //BMP_H
