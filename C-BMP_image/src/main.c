#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "stego.h"

void args_message() {
    printf("Error: invalid args.\n");
}

void error_message() {
    printf("Error: memory allocation failed.\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        args_message();
        return 1;
    }

    FILE* input;
    input = fopen(argv[2], "rb");
    if (input == NULL) {
        args_message();
        return 1;
    }
    BMP_header* image_header = malloc(sizeof(struct BMP_header));
    pixel* image = NULL;
    if (load_bmp(input, image_header, &image) == -1) {
        error_message();
        fclose(input);
        free(image_header);
        return 1;
    }
    fclose(input);
    if (strcmp(argv[1], "crop-rotate") == 0) {
        if (argc < 8) {
            free(image_header);
            free(image);
            args_message();
            return 1;
        }
        int x = atoi(argv[4]), y = atoi(argv[5]);
        int w = atoi(argv[6]), h = atoi(argv[7]);

        if(!(image_header->height >= h + y && h >= 0 && y >= 0)) {
            free(image_header);
            free(image);
            args_message();
            return 1;
        }
        if(!(image_header->width >= w + x && x >= 0 && w >= 0)) {
            free(image_header);
            free(image);
            args_message();
            return 1;
        }

        y = image_header->height - y - 1;
        pixel *crop_image = NULL;
        BMP_header *crop_header = malloc(sizeof(struct BMP_header));
        if (crop(image, &crop_image, x, y, h, w, image_header, crop_header) == -1) {
            error_message();
            free(image_header);
            free(image);
            free(crop_header);
            return 1;
        }

        free(image_header);
        free(image);

        BMP_header *rotate_header = malloc(sizeof(struct BMP_header));
        pixel* rotate_image = NULL;
        if (rotate(crop_header, crop_image, rotate_header, &rotate_image) == -1) {
            error_message();
            free(crop_header);
            free(crop_image);
            free(rotate_header);
            return 1;
        }
        FILE* output;
        output = fopen(argv[3], "wb");
        if (output == NULL) {
            args_message();
            return 1;
        }
        save_bmp(output, rotate_header, rotate_image);

        fclose(output);
        free(crop_header);
        free(rotate_header);
        free(crop_image);
        free(rotate_image);
    } else if (strcmp(argv[1], "insert") == 0) {
        if (argc < 6) {
            free(image_header);
            free(image);
            args_message();
            return 1;
        }
        FILE *key, *message;
        key = fopen(argv[4], "r");
        if (key == NULL) {
            args_message();
            free(image_header);
            free(image);
            return 1;
        }
        message = fopen(argv[5], "r");
        if (message == NULL) {
            args_message();
            fclose(key);
            free(image_header);
            free(image);
            return 1;
        }
        insert(image_header, image, key, message);
        FILE* output;
        output = fopen(argv[3], "wb");
        if (output == NULL) {
            args_message();
            fclose(key);
            fclose(message);
            free(image_header);
            free(image);
            return 1;
        }
        save_bmp(output, image_header, image);

        free(image_header);
        free(image);
        fclose(output);
        fclose(key);
        fclose(message);
    } else if (strcmp(argv[1], "extract") == 0) {
        if (argc < 5) {
            free(image_header);
            free(image);
            args_message();
            return 1;
        }
        FILE *key, *message;
        key = fopen(argv[3], "r");
        if (key == NULL) {
            args_message();
            free(image_header);
            free(image);
            return 1;
        }
        message = fopen(argv[4], "w");
        if (message == NULL) {
            args_message();
            fclose(key);
            free(image_header);
            free(image);
            return 1;
        }
        extract(image_header, image, key, message);

        free(image_header);
        free(image);
        fclose(key);
        fclose(message);
    } else {
        free(image_header);
        free(image);
        args_message();
        return 1;
    }
    return 0;
}