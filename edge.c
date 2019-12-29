#include "edge.h"

struct edge edge_create(int start, int end, int weight)
{
    struct edge e;
    e.start = start;
    e.end = end;
    e.weight = weight;
    return e;
}

void edge_print(struct edge e)
{
    printf("%d - %d : %d\n", e.start, e.end, e.weight);
}