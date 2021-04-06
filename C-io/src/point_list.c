#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "point_list.h"

void add_point(intrusive_list* list, int x, int y) {
    point* p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    p->node.next = NULL;
    p->node.prev = NULL;
    add_node(list, &(p->node));
}

void add_next_point(intrusive_node* node, int x, int y) {
    point *p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    p->node.next = NULL;
    p->node.prev = node;
    node->next = &p->node;
}

void remove_point(intrusive_list* list, int x, int y) {
    intrusive_node* head = list->head;
    head = head->next;
    while (head) {
        point* p = container_of(head, point, node);
        if (p->x == x && p->y == y) {
            remove_node(&(p->node));
            head = head->next;
            free(p);
        }
        else
            head = head->next;
    }
}

void show_all_points(intrusive_list* list) {
    intrusive_node* head = list->head;
    while (head->next)
        head = head->next;
    int flag = 0;
    while (head->prev) {
        point* p = container_of(head, point, node);
        if (flag != 0)
            printf(" ");
        else flag++;
        printf("(%d %d)", p->x, p->y);
        head = head->prev;
    }
    printf("\n");
}

void remove_all_points(intrusive_list* list) {
    intrusive_node* head = list->head;
    while (head->next)
        head = head->next;
    while (head->prev) {
        point* p = container_of(head, point, node);
        head = head->prev;
        free(p);
    }
    head->next = NULL;
}