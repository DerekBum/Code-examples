#ifndef POINT_LIST_H
#define POINT_LIST_H

#include "clist.h"

typedef struct point {
    int x, y;
    intrusive_node node;
} point;

void add_point(intrusive_list* list, int x, int y);
void add_next_point(intrusive_node* node, int x, int y);
void remove_point(intrusive_list* list, int x, int y);
void show_all_points(intrusive_list* list);
void remove_all_points(intrusive_list* list);

#endif //POINT_LIST_H
