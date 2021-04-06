#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    intrusive_node node;
} point;

void add_point(intrusive_list* list, int x, int y) {
    point* p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    p->node.next = NULL;
    p->node.prev = NULL;
    add_node(list, &(p->node));
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

int main() {
    const int max_input_size = 239;
    char input[max_input_size];
    scanf("%239s", input);
    intrusive_list* list = malloc(sizeof(intrusive_list));
    init_list(list);
    while (strcmp(input, "exit") != 0) {
        if (strcmp(input, "add") == 0) {
            char first[max_input_size], second[max_input_size];
            scanf("%239s%239s", first, second);
            add_point(list, atoi(first), atoi(second));
        } else if (strcmp(input, "rm") == 0) {
            char first[max_input_size], second[max_input_size];
            scanf("%239s%239s", first, second);
            remove_point(list, atoi(first), atoi(second));
        } else if (strcmp(input, "print") == 0) {
            show_all_points(list);
        } else if (strcmp(input, "rma") == 0) {
            remove_all_points(list);
        } else if (strcmp(input, "len") == 0) {
            printf("%d\n", get_length(list));
        } else {
            printf("Unknown command\n");
        }
        scanf("%239s", input);
    }
    remove_all_points(list);
    free(list->head);
    free(list);
    return 0;
}
