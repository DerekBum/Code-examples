#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

#define min(a,b) ((a) < (b) ? (a) : (b))

int merge(void* array, int left, int mid, int right,
           size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    int left_index = 0, right_index = 0;
    void* sorted_array = malloc((right - left) * element_size);
    if (sorted_array == NULL)
        return -1;
    while ((left + left_index < mid) && (mid + right_index < right)) {
        if (comparator((array + (left + left_index) * element_size),
                       (array + (mid + right_index) * element_size)) < 0) {
            memcpy(sorted_array + (left_index + right_index) * element_size,
                   array + (left + left_index) * element_size, element_size);
            left_index++;
        } else {
            memcpy(sorted_array + (left_index + right_index) * element_size,
                   array + (mid + right_index) * element_size, element_size);
            right_index++;
        }
    }

    while (left + left_index < mid) {
        memcpy(sorted_array + (left_index + right_index) * element_size,
               array + (left + left_index) * element_size, element_size);
        left_index++;
    }

    while (mid + right_index < right) {
        memcpy(sorted_array + (left_index + right_index) * element_size,
               array + (mid + right_index) * element_size, element_size);
        right_index++;
    }
    memcpy(array + left * element_size, sorted_array, (right - left) * element_size);
    free(sorted_array);
    return 0;
}

int mergesort(void* array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    for (int step = 1; step < elements; step *= 2)
        for (int current_block = 0; current_block < elements - step; current_block += 2 * step)
            if (merge(array, current_block, current_block + step,
                  min(current_block + 2 * step, elements), elements, element_size, comparator) == -1)
                return -1;
    return 0;
}
