#include <stdlib.h>
#include "clist.h"

void init_list(intrusive_list* list) {
    list->head = malloc(sizeof(intrusive_node));
    list->head->next = NULL;
    list->head->prev = NULL;
}

void add_node(intrusive_list* list, intrusive_node* elem) {
    intrusive_node* head = list->head;
    while (head->next)
        head = head->next;
    elem->prev = head;
    head->next = elem;
}

void remove_node(intrusive_node* elem) {
    if (elem->prev && elem->next) {
        elem->prev->next = elem->next;
        elem->next->prev = elem->prev;
    }
    else if (elem->prev)
        elem->prev->next = NULL;
}

int get_length(intrusive_list* list) {
    intrusive_node* head = list->head;
    int res = 0;
    head = head->next;
    while (head) {
        res++;
        head = head->next;
    }
    return res;
}