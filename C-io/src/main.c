#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "clist.h"
#include "point_list.h"

void plus_one(intrusive_node* node, void* number) {
    if (node->prev)
        (*(int*)number)++;
}

void printf_with_style(intrusive_node* node, void* style) {
    if (node->prev) {
        point *p = container_of(node, point, node);
        printf((char*)style, p->x, p->y);
    }
}

void loadtext(intrusive_node* node, void* input) {
    int x, y;
    if (fscanf(input, "%d %d", &x, &y) != EOF)
        add_next_point(node, x, y);
}

void loadbin(intrusive_node* node, void* input) {
    const int max_number = 5000000;
    const int number_of_bytes = 3;
    const int max_len = 24;

    int x = 0, y = 0;
    if (fread(&x, number_of_bytes, 1, input) == 1 && fread(&y, number_of_bytes, 1, input) == 1) {
        if (x > max_number) {
            x = ((1 << max_len) - 1) ^ (x - 1);
            x *= -1;
        }
        if (y > max_number) {
            y = ((1 << max_len) - 1) ^ (y - 1);
            y *= -1;
        }
        add_next_point(node, x, y);
    }
}

void savetext(intrusive_node* node, void* output) {
    if (node->prev) {
        point* p = container_of(node, point, node);
        fprintf(output, "%d %d\n", p->x, p->y);
    }
}

void savebin(intrusive_node* node, void* output) {
    const int number_of_bytes = 3;
    const int max_len = 24;

    if (node->prev) {
        point* p = container_of(node, point, node);
        if (p->x < 0)
            p->x = (((1 << max_len) - 1) ^ (p->x * (-1))) + 1;
        if (p->y < 0)
            p->y = (((1 << max_len) - 1) ^ (p->y * (-1))) + 1;
        unsigned char* bytes_for_x = (unsigned char*)&p->x;
        unsigned char* bytes_for_y = (unsigned char*)&p->y;
        fwrite(bytes_for_x, sizeof(char), number_of_bytes, output);
        fwrite(bytes_for_y, sizeof(char), number_of_bytes, output);
    }
}

int main(int argc, char** argv) {
    assert(argc > 1 && "Input error");

    intrusive_list* list = malloc(sizeof(intrusive_list));
    init_list(list);
    if (strcmp(argv[1], "loadtext") == 0) {
        FILE* input;
        input = fopen(argv[2], "r");
        apply(list, loadtext, input);
        fclose(input);
    } else {
        FILE* input;
        input = fopen(argv[2], "rb");
        apply(list, loadbin, input);
        fclose(input);
    }
    if (strcmp(argv[3], "savetext") == 0) {
        FILE* output;
        output = fopen(argv[4], "w");
        apply(list, savetext, output);
        fclose(output);
    } else if (strcmp(argv[3], "savebin") == 0) {
        FILE* output;
        output = fopen(argv[4], "wb");
        apply(list, savebin, output);
        fclose(output);
    } else if (strcmp(argv[3], "count") == 0) {
        int res = 0;
        apply(list, plus_one, &res);
        printf("%d\n", res);
    } else if (strcmp(argv[3], "print") == 0) {
        char* style = argv[4];
        apply(list, printf_with_style, style);
        printf("\n");
    }

    remove_all_points(list);
    free(list->head);
    free(list);
    return 0;
}