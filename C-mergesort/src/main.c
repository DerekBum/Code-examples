#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

int int_comparator(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int char_comparator(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}

int string_comparator(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

void error_message() {
    printf("Error: memory allocation failed.\n");
}

int main(int argc, char** argv) {
    size_t element_size, elements = argc - 2;
    if (strcmp(*(argv + 1), "int") == 0) {
        element_size = sizeof(int);
        int* array = malloc(elements * element_size);
        if (array == NULL) {
            error_message();
            return 1;
        }
        for (int i = 2; i < argc; i++)
            *(array + i - 2) = atoi(*(argv + i));
        if (mergesort((void*) array, elements, element_size, int_comparator) == -1) {
            error_message();
            free(array);
            return 1;
        }
        for (int i = 0; i + 1 < elements; i++)
            printf("%d ", *(array + i));
        if (elements > 0)
            printf("%d\n", *(array + elements - 1));
        free(array);
    }

    else if (strcmp(*(argv + 1), "char") == 0) {
        element_size = sizeof(char);
        char* array = malloc(elements * element_size);
        if (array == NULL) {
            error_message();
            return 1;
        }
        for (int i = 2; i < argc; i++)
            *(array + i - 2) = **(argv + i);
        if (mergesort((void*) array, elements, element_size, char_comparator) == -1) {
            error_message();
            free(array);
            return 1;
        }
        for (int i = 0; i + 1 < elements; i++)
            printf("%c ", *(array + i));
        if (elements > 0)
            printf("%c\n", *(array + elements - 1));
        free(array);
    }

    else if (strcmp(*(argv + 1), "str") == 0) {
        element_size = sizeof(char*);
        char** array = malloc(elements * element_size);
        if (array == NULL) {
            error_message();
            return 1;
        }
        for (int i = 2; i < argc; i++)
            *(array + i - 2) = *(argv + i);
        if (mergesort((void*) array, elements, element_size, string_comparator) == -1) {
            error_message();
            free(array);
            return 1;
        }
        for (int i = 0; i + 1 < elements; i++)
            printf("%s ", *(array + i));
        if (elements > 0)
            printf("%s\n", *(array + elements - 1));
        free(array);
    }
    return 0;
}
