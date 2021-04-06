#ifndef STEGO_H
#define STEGO_H

void insert(BMP_header* image_header, pixel* image, FILE* key, FILE* message);
void extract(BMP_header* image_header, pixel* image, FILE* key, FILE* message);

#endif //STEGO_H
