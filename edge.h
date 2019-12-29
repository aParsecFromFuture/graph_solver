#ifndef EDGE_H
#define EDGE_H
#include <stdio.h>

struct edge{
    int start;
    int end;
    int weight;
};

struct edge edge_create(int, int, int);
void edge_print(struct edge);

#endif