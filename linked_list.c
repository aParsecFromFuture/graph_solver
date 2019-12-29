#include "linked_list.h"

struct linked_list* list_create()
{
    struct linked_list *list = malloc(sizeof(struct linked_list));
    list->head = 0;
    list->size = 0;
    return list;
}

void list_clear(struct linked_list *list)
{
    struct node *iter, *garbage;
    if(!list->head){
        return;
    }
    garbage = list->head;
    iter = garbage->next;
    while(iter){
        free(garbage);
        garbage = iter;
        iter = iter->next;
    }
    free(garbage);
    list->head = 0;
    list->size = 0;
}

void list_free(struct linked_list *list)
{
    list_clear(list);
    free(list);
}

int list_last(struct linked_list *list)
{
    struct node *iter;
    
    if(!list->head){
        return -1;
    }
    if(!list->head->next){
        return list->head->value;
    }
    iter = list->head;
    while(iter->next->next)iter = iter->next;
    return iter->next->value;
}

void list_push(struct linked_list *list, int v)
{
    if(!list->head){
        list->head = malloc(sizeof(struct node));
        list->head->value = v;
        list->head->next = 0;
    }else{
        struct node *iter = list->head;
        while(iter->next)iter = iter->next;
        iter->next = malloc(sizeof(struct node));
        iter->next->value = v;
        iter->next->next = 0;
    }
    list->size++;
}

int list_pop(struct linked_list *list)
{
    struct node *iter;
    int v;
    
    if(!list->head){
        return -1;
    }
    if(!list->head->next){
        v = list->head->value;
        free(list->head);
        list->head = 0;
        list->size--;
        return v;
    }
    iter = list->head;
    while(iter->next->next)iter = iter->next;
    v = iter->next->value;
    free(iter->next);
    iter->next = 0;
    list->size--;
    return v;
}

void list_unshift(struct linked_list *list, int v)
{
    struct node *head = malloc(sizeof(struct node));
    head->value = v;
    head->next = list->head;
    list->head = head;
    list->size++;
}

int list_shift(struct linked_list *list)
{
    struct node *head;
    int v;
    
    if(!list->head){
        return -1;
    }
    
    v = list->head->value;
    head = list->head;
    list->head = list->head->next;
    free(head);
    list->size--;
    return v;
}

void list_insert_ordered(struct linked_list *list, int v)
{
    struct node *n, *iter;
    if(!list->head){
        list->head = malloc(sizeof(struct node));
        list->head->value = v;
        list->head->next = 0;
    }else if(v < list->head->value){
        n = malloc(sizeof(struct node));
        n->value = v;
        n->next = list->head;
        list->head = n;
    }else{
        iter = list->head;
        while(iter->next && v > iter->next->value)iter = iter->next;
        
        if(iter->next){
            n = malloc(sizeof(struct node));
            n->value = v;
            n->next = iter->next;
            iter->next = n;
        }else{
            iter->next = malloc(sizeof(struct node));
            iter->next->value = v;
            iter->next->next = 0;
        }
    }
    list->size++;
}

int list_is_have(struct linked_list *list, int v)
{
    struct node *iter = list->head;
    while(iter){
        if(iter->value == v)return 1;
    }
    return 0;
}

void list_print(const struct linked_list *list)
{
    struct node *iter = list->head;
    while(iter){
        printf("%d, ",iter->value);
        iter = iter->next;
    }
    printf("\n");
}






struct linked_edge_list* edge_list_create()
{
    struct linked_edge_list *list = malloc(sizeof(struct linked_edge_list));
    list->head = 0;
    list->size = 0;
    return list;
}

void edge_list_clear(struct linked_edge_list *list)
{
    struct edge_node *iter, *garbage;
    if(!list->head){
        return;
    }
    garbage = list->head;
    iter = garbage->next;
    while(iter){
        free(garbage);
        garbage = iter;
        iter = iter->next;
    }
    free(garbage);
    list->head = 0;
    list->size = 0;
}

void edge_list_free(struct linked_edge_list *list)
{
    edge_list_clear(list);
    free(list);
}

void edge_list_push(struct linked_edge_list *list, struct edge v)
{
    if(!list->head){
        list->head = malloc(sizeof(struct edge_node));
        list->head->value = v;
        list->head->next = 0;
    }else{
        struct edge_node *iter = list->head;
        while(iter->next)iter = iter->next;
        iter->next = malloc(sizeof(struct edge_node));
        iter->next->value = v;
        iter->next->next = 0;
    }
    list->size++;
}

struct edge edge_list_pop(struct linked_edge_list *list)
{
    struct edge_node *iter;
    struct edge v;
    
    if(!list->head){
        return edge_create(-1, -1, -1);
    }
    if(!list->head->next){
        v = list->head->value;
        free(list->head);
        list->head = 0;
        list->size--;
        return v;
    }
    iter = list->head;
    while(iter->next->next)iter = iter->next;
    v = iter->next->value;
    free(iter->next);
    iter->next = 0;
    list->size--;
    return v;
}

void edge_list_unshift(struct linked_edge_list *list, struct edge v)
{
    struct edge_node *head = malloc(sizeof(struct edge_node));
    head->value = v;
    head->next = list->head;
    list->head = head;
    list->size++;
}

struct edge edge_list_shift(struct linked_edge_list *list)
{
    struct edge_node *head;
    struct edge v;
    
    if(!list->head){
        return edge_create(-1, -1, -1);
    }
    
    v = list->head->value;
    head = list->head;
    list->head = list->head->next;
    free(head);
    list->size--;
    return v;
}

void edge_list_insert_ordered(struct linked_edge_list *list, struct edge v)
{
    struct edge_node *n, *iter;
    if(!list->head){
        list->head = malloc(sizeof(struct edge_node));
        list->head->value = v;
        list->head->next = 0;
    }else if(v.weight < list->head->value.weight){
        n = malloc(sizeof(struct edge_node));
        n->value = v;
        n->next = list->head;
        list->head = n;
    }else{
        iter = list->head;
        while(iter->next && v.weight > iter->next->value.weight)iter = iter->next;
        
        if(iter->next){
            n = malloc(sizeof(struct edge_node));
            n->value = v;
            n->next = iter->next;
            iter->next = n;
        }else{
            iter->next = malloc(sizeof(struct edge_node));
            iter->next->value = v;
            iter->next->next = 0;
        }
    }
    list->size++;
}

int edge_list_is_have(struct linked_edge_list *list, struct edge v)
{
    struct edge_node *iter = list->head;
    while(iter){
        if(iter->value.start == v.start && iter->value.end == v.end && iter->value.weight == v.weight)return 1;
    }
    return 0;
}

void edge_list_print(const struct linked_edge_list *list)
{
    struct edge_node *iter = list->head;
    while(iter){
        printf("%d - %d : %d\n",iter->value.start, iter->value.end,  iter->value.weight);
        iter = iter->next;
    }
    printf("\n");
}
