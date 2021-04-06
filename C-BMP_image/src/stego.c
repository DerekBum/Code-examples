#include <stdio.h>
#include "bmp.h"
#include "stego.h"

static char convert_symbol(char from) {
    const int A_symbol_code = 65;

    if (from == ' ')
        return 0;
    if (from == '.')
        return 1;
    if (from == ',')
        return 2;
    return from - A_symbol_code + 3;
}

static char reconvert_symbol(char from) {
    const int A_symbol_code = 65;

    if (from == 0)
        return ' ';
    if (from == 1)
        return '.';
    if (from == 2)
        return ',';
    return from + A_symbol_code - 3;
}

static void insert_bit(BMP_header* image_header, pixel* image, char symbol, int x, int y, int color, int index) {
    pixel update_pixel = get_pixel(image_header, image, x, y);
    char changing_bit = (symbol >> index) & 1;
    update_pixel.chanals[color] = ((update_pixel.chanals[color] >> 1) << 1) | changing_bit;
    set_pixel(image_header, image, x, y, update_pixel);
}

static void extract_bit(BMP_header* image_header, pixel* image, char* symbol, int x, int y, int color, int index) {
    pixel changed_pixel = get_pixel(image_header, image, x, y);
    *symbol |= ((changed_pixel.chanals[color] & 1) << index);
}

void insert(BMP_header* image_header, pixel* image, FILE* key, FILE* message) {
    const int number_of_bits = 5;
    const int max_converted_symbol_value = 28;

    char current_symbol;
    while ((current_symbol = fgetc(message)) != EOF) {
        current_symbol = convert_symbol(current_symbol);
        if (current_symbol < 0 || current_symbol > max_converted_symbol_value)
            continue;
        for (int i = 0; i < number_of_bits; i++) {
            int x, y;
            char color;
            fscanf(key, "%d %d %c", &x, &y, &color);
            y = image_header->height - y - 1;
            if (color == 'R')
                color = 0;
            if (color == 'G')
                color = 1;
            if (color == 'B')
                color = 2;
            insert_bit(image_header, image, current_symbol, x, y, color, i);
        }
    }
}

void extract(BMP_header* image_header, pixel* image, FILE* key, FILE* message) {
    const int number_of_bits = 5;

    int x, y, index = 0;
    char color, current_symbol = 0;
    while (fscanf(key, "%d %d %c", &x, &y, &color) != EOF) {
        y = image_header->height - y - 1;
        if (index == number_of_bits) {
            fprintf(message, "%c", reconvert_symbol(current_symbol));
            index = 0;
            current_symbol = 0;
        }
        if (color == 'R')
            color = 0;
        if (color == 'G')
            color = 1;
        if (color == 'B')
            color = 2;
        extract_bit(image_header, image, &current_symbol, x, y, color, index);
        index++;
    }
    fprintf(message, "%c\n", reconvert_symbol(current_symbol));
}