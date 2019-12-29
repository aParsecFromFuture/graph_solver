#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"

struct node{
    int value;
    struct node *next;
};

struct linked_list{
    struct node *head;
    size_t size;
};

struct edge_node{
    struct edge value;
    struct edge_node *next;
};

struct linked_edge_list{
    struct edge_node *head;
    size_t size;
};

struct linked_list* list_create();
void list_clear(struct linked_list*);
void list_free(struct linked_list*);
int list_last(struct linked_list*);
void list_push(struct linked_list*, int);
int list_pop(struct linked_list*);
void list_unshift(struct linked_list*, int);
int list_shift(struct linked_list*);
void list_insert_ordered(struct linked_list*, int);  //insert ordered
int list_is_have(struct linked_list*, int);
void list_print(const struct linked_list*);

struct linked_edge_list* edge_list_create();
void edge_list_clear(struct linked_edge_list*);
void edge_list_free(struct linked_edge_list*);
void edge_list_push(struct linked_edge_list*, struct edge);
struct edge edge_list_pop(struct linked_edge_list*);
void edge_list_unshift(struct linked_edge_list*, struct edge);
struct edge edge_list_shift(struct linked_edge_list*);
void edge_list_insert_ordered(struct linked_edge_list*, struct edge);  //insert ordered
int edge_list_is_have(struct linked_edge_list*, struct edge);
void edge_list_print(const struct linked_edge_list*);

#endif