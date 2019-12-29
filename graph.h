#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

struct graph{
    size_t v_count;
    int *is_visited;
    int **adj_matrix;
};

struct graph* graph_create(size_t);
void graph_copy(struct graph*, struct graph*);
void graph_undirect(struct graph*);

size_t graph_degree(struct graph*);
size_t graph_node_degree(struct graph*, int);
size_t graph_connected_degree(struct graph*);
size_t graph_edge_count(struct graph*);
size_t graph_d_edge_count(struct graph*);

int graph_can_accessible(struct graph*, int, int);

int graph_set_edge(struct graph*, unsigned int, unsigned int);
int graph_set_d_edge(struct graph*, unsigned int, unsigned int);
int graph_set_w_edge(struct graph*, unsigned int, unsigned int, int);
int graph_unset_edge(struct graph*, unsigned int, unsigned int);
int graph_unset_d_edge(struct graph*, unsigned int, unsigned int);

void graph_get_edges(struct graph*, struct linked_edge_list*);
void graph_clear_edges(struct graph*);
void graph_clear_visits(struct graph*);

void graph_print(const struct graph*);
void graph_print_d(const struct graph*);

void graph_track_path(struct graph*, int, struct linked_list*);

void graph_DFS(struct graph*, int, int, struct graph*);
void graph_BFS(struct graph*, int, int, struct graph*);
void graph_BestFS(struct graph*, int, int, struct graph*);
void graph_UCS(struct graph*, int, int, struct graph*);

int graph_is_cycle(struct graph*, int, int);
void graph_get_bridges(struct graph*, int, int, int*, int*, int*, struct linked_edge_list*);
int graph_is_bridge(struct graph *, int, int);

void graph_kruskal(struct graph*, struct graph*);
void graph_boruvka(struct graph*, struct graph*);
void graph_prim(struct graph*, int, struct graph*);
void graph_reverse_kruskal(struct graph*, struct graph*);

void graph_fleury(struct graph*, int, struct graph*);
void graph_nearest_neighbour(struct graph*, int, struct graph*);

#endif