#include "graph.h"

struct graph* graph_create(size_t v)
{
    int i;
    struct graph *g = malloc(sizeof(struct graph));
    g->v_count = v;
    g->is_visited = calloc(sizeof(int), g->v_count);
    g->adj_matrix = malloc(sizeof(int*) * g->v_count);
    for(i = 0;i < g->v_count;i++){
        g->adj_matrix[i] = calloc(sizeof(int), g->v_count);
    }
    return g;
}

size_t graph_edge_count(struct graph *g)
{
    int i, j, count = 0;
    for(i = 0;i < g->v_count;i++){
        for(j = i + 1;j < g->v_count;j++){
            if(g->adj_matrix[i][j]){
                count++;
            }
        }
    }
    return count;
}

size_t graph_d_edge_count(struct graph *g)
{
    int i, j, count = 0;
    for(i = 0;i < g->v_count;i++){
        for(j = 0;j < g->v_count;j++){
            if(g->adj_matrix[i][j]){
                count++;
            }
        }
    }
    return count;
}

int graph_can_accessible(struct graph *g, int v1, int v2)
{
    struct linked_list *stack = list_create();
    int at, to, *is_visited;
    
    if(v1 == v2)return 1;
    
    list_push(stack, v1);
    is_visited = calloc(sizeof(int), g->v_count);
    is_visited[v1] = 1;
    
    while(stack->size){
        at = list_pop(stack);
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to] && !is_visited[to]){
                if(to == v2){
                    free(is_visited);
                    return 1;
                }
                list_push(stack, to);
                is_visited[to] = 1;
            }
        }
    }
    free(is_visited);
    return 0;
}

void graph_copy(struct graph *src, struct graph *dst)
{
    int i, j;
    if(dst->v_count != 0){
        free(dst->is_visited);
        dst->is_visited = 0;
        for(i = 0;i < dst->v_count;i++){
            free(dst->adj_matrix[i]);
            dst->adj_matrix[i] = 0;
        }
        free(dst->adj_matrix);
        dst->adj_matrix = 0;
    }
    
    dst->v_count = src->v_count;
    dst->is_visited = malloc(sizeof(int) * dst->v_count);
    
    dst->adj_matrix = malloc(sizeof(int*) * dst->v_count);
    for(i = 0;i < dst->v_count;i++){
        dst->is_visited[i] = src->is_visited[i];
        dst->adj_matrix[i] = malloc(sizeof(int) * dst->v_count);
        for(j = 0;j < dst->v_count; j++){
            dst->adj_matrix[i][j] = src->adj_matrix[i][j];
        }
    }
}

void graph_undirect(struct graph *g)
{
    int i, j;
    for(i = 0;i < g->v_count;i++){
        for(j = 0;j < g->v_count;j++){
            if(g->adj_matrix[i][j]){
                g->adj_matrix[j][i] = g->adj_matrix[i][j];
            }
        }
    }
}

size_t graph_degree(struct graph *g)
{
    return g->v_count;
}

size_t graph_node_degree(struct graph *g, int at)
{
    int to, count = 0;
    for(to = 0;to < g->v_count;to++){
        if(g->adj_matrix[at][to]){
            count++;
        }
    }
    return count;
}

size_t graph_connected_degree(struct graph *g)
{
    int at, to, count = 0;
    for(at = 0;at < g->v_count;at++){
        if(graph_node_degree(g, at)){
            count++;
        }
    }
    return count;
}

int graph_set_edge(struct graph *g, unsigned int v1, unsigned int v2)
{
    if(v1 != v2 && v1 < g->v_count && v2 < g->v_count){
        g->adj_matrix[v1][v2] = 1;
        g->adj_matrix[v2][v1] = 1;
        return 1;
    }
    return 0;
}

int graph_set_d_edge(struct graph *g, unsigned int v1, unsigned int v2)
{
    if(v1 != v2 && v1 < g->v_count && v2 < g->v_count){
        g->adj_matrix[v1][v2] = 1;
        return 1;
    }
    return 0;
}

int graph_set_w_edge(struct graph *g, unsigned int v1, unsigned int v2, int weight)
{
    if(v1 != v2 && v1 < g->v_count && v2 < g->v_count){
        g->adj_matrix[v1][v2] = weight;
        g->adj_matrix[v2][v1] = weight;
        return 1;
    }
    return 0;
}

int graph_unset_edge(struct graph *g, unsigned int v1, unsigned int v2)
{
    if(v1 < g->v_count && v2 < g->v_count){
        g->adj_matrix[v1][v2] = 0;
        g->adj_matrix[v2][v1] = 0;
        return 1;
    }
    return 0;
}

int graph_unset_d_edge(struct graph *g, unsigned int v1, unsigned int v2)
{
    if(v1 < g->v_count && v2 < g->v_count){
        g->adj_matrix[v1][v2] = 0;
        return 1;
    }
    return 0;
}

void graph_get_edges(struct graph *g, struct linked_edge_list *list)
{
    int i, j;
    for(i = 0;i < g->v_count;i++){
        for(j = i + 1;j < g->v_count;j++){
            if(g->adj_matrix[i][j]){
                edge_list_insert_ordered(list, edge_create(i, j, g->adj_matrix[i][j]));
            }
        }
    }
}

void graph_clear_edges(struct graph *g)
{
    int i, j;
    for(i = 0;i < g->v_count;i++){
        for(j = 0;j < g->v_count;j++){
            g->adj_matrix[i][j] = 0;
        }
    }
}

void graph_clear_visits(struct graph *g)
{
    int i;
    for(i = 0;i < g->v_count;i++){
        g->is_visited[i] = 0;
    }
}

void graph_print(const struct graph *g)
{
    int i, j;
    printf("vertice count : %ld\n\n", g->v_count);
    for(i = 0;i < g->v_count;i++){
        for(j = i + 1;j < g->v_count;j++){
            if(g->adj_matrix[i][j]){
                printf("%d - %d\n",i,j);
            }
        }
    }
}

void graph_print_d(const struct graph *g)
{
    int i, j;
    printf("vertice count : %ld\n\n", g->v_count);
    for(i = 0;i < g->v_count;i++){
        for(j = 0;j < g->v_count;j++){
            if(g->adj_matrix[i][j]){
                printf("%d - %d\n", i, j);
            }
        }
    }
}

void graph_track_path(struct graph *g, int at, struct linked_list *list)
{
    int to = -1;
    list_push(list, at);
    while(to == -1){
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to]){
                list_push(list, to);
                at = to;
                to = -1;
            }
        }
    }
}

void graph_DFS(struct graph *g, int base, int find, struct graph *path){
    int at, to, *is_visited;
    struct linked_edge_list *stack;
    struct edge e;

    stack = edge_list_create();
    is_visited = calloc(sizeof(int), g->v_count);
    is_visited[base] = 1;
    edge_list_push(stack, edge_create(base, base, 0));
    
    while(stack->size){
        e = edge_list_pop(stack);
        graph_set_d_edge(path, e.end, e.start);
        at = e.end;
        
        if(at == find){
            free(is_visited);
            edge_list_free(stack);
            return;
        }
        
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to] && !is_visited[to]){
                edge_list_push(stack, edge_create(at, to, 1));
                is_visited[to] = 1;
            }
        }
    }
    free(is_visited);
    edge_list_free(stack);
}

void graph_BFS(struct graph *g, int base, int find, struct graph *path){
    int at, to, *is_visited;
    struct linked_edge_list *queue;
    struct edge e;

    queue = edge_list_create();
    is_visited = calloc(sizeof(int), g->v_count);
    is_visited[base] = 1;
    edge_list_push(queue, edge_create(base, base, 0));
    
    while(queue->size){
        e = edge_list_shift(queue);
        graph_set_d_edge(path, e.end, e.start);
        at = e.end;
        
        if(at == find){
            free(is_visited);
            edge_list_free(queue);
            return;
        }
        
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to] && !is_visited[to]){
                edge_list_push(queue, edge_create(at, to, 1));
                is_visited[to] = 1;
            }
        }
    }
    free(is_visited);
    edge_list_free(queue);
}

void graph_BestFS(struct graph *g, int base, int find, struct graph *path){
    int at, to, *is_visited;
    struct linked_edge_list *priority_queue;
    struct edge e;

    priority_queue = edge_list_create();
    is_visited = calloc(sizeof(int), g->v_count);
    edge_list_insert_ordered(priority_queue, edge_create(-1, base, 0));
    
    while(priority_queue->size){
        do{
            e = edge_list_shift(priority_queue);
        }while(priority_queue->size && is_visited[e.end]);
        
        if(e.end == -1)break;
        
        graph_set_d_edge(path, e.end, e.start);
        at = e.end;
        is_visited[at] = 1;
        
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to] && !is_visited[to]){
                if(to == find){
                    graph_set_d_edge(path, to, at);
                    free(is_visited);
                    edge_list_free(priority_queue);
                    return;
                }
                edge_list_insert_ordered(priority_queue, edge_create(at, to, g->adj_matrix[at][to]));
            }
        }
    }
    free(is_visited);
    edge_list_free(priority_queue);
}

void graph_UCS(struct graph *g, int base, int find, struct graph *path){
    int at, to, *is_visited;
    struct linked_edge_list *priority_queue;
    struct edge e;

    priority_queue = edge_list_create();
    is_visited = calloc(sizeof(int), g->v_count);
    edge_list_insert_ordered(priority_queue, edge_create(-1, base, 0));
    
    while(priority_queue->size){
        do{
            e = edge_list_shift(priority_queue);
        }while(priority_queue->size && is_visited[e.end]);
        
        if(e.end == -1)break;
        
        graph_set_d_edge(path, e.end, e.start);
        at = e.end;
        is_visited[at] = 1;
        
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to] && !is_visited[to]){
                if(to == find){
                    graph_set_d_edge(path, to, at);
                    free(is_visited);
                    edge_list_free(priority_queue);
                    return;
                }
                edge_list_insert_ordered(priority_queue, edge_create(at, to, g->adj_matrix[at][to] + e.weight));
            }
        }
    }
    free(is_visited);
    edge_list_free(priority_queue);
}

int graph_is_cycle(struct graph *g, int at, int parent)
{
    g->is_visited[at] = 1;
	for(int to = 0;to < g->v_count;to++){
		if(g->adj_matrix[at][to]){
			if(!g->is_visited[to]){
				if(graph_is_cycle(g,to,at)){
					return 1;
				}
			}else if(to != parent){
				return 1;
			}
		}
	}
	return 0;
}

void graph_get_bridges(struct graph *g, int at, int parent, int *ids, int *low, int *is_visited, struct linked_edge_list *list){
	static int id = 0;
	ids[at] = low[at] = id++;
	is_visited[at] = 1;
	for(int to = 0;to < g->v_count;to++){
		if(g->adj_matrix[at][to]){
			if(to == parent){
				continue;
			}
			if(!is_visited[to]){
				graph_get_bridges(g, to, at, ids, low, is_visited, list);
				low[at] = (low[at] < low[to])? low[at] : low[to];
				if(ids[at] < low[to]){
                    edge_list_push(list, edge_create(at, to, g->adj_matrix[at][to]));
				}
			}else{
				low[at] = (low[at] < ids[to])? low[at] : ids[to];
			}
		}
	}
}

int graph_is_bridge(struct graph *g, int v1, int v2){
	int *ids = malloc(sizeof(int) * g->v_count);
	int *low = malloc(sizeof(int) * g->v_count);
    int *is_visited = calloc(sizeof(int), g->v_count);
	struct linked_edge_list *list = edge_list_create();
	graph_get_bridges(g, v1, -1, ids, low, is_visited, list);
	for(struct edge_node *iter = list->head;iter != 0;iter = iter->next){
		if((iter->value.start == v1 && iter->value.end == v2) || (iter->value.start == v1 && iter->value.end == v2)){
            free(ids);
            free(low);
            free(is_visited);
			return 1;
		}
	}
    free(ids);
    free(low);
    free(is_visited);
	return 0;
}

void graph_kruskal(struct graph *src, struct graph *dst)
{
    struct linked_edge_list *list = edge_list_create();
    struct edge edge;
    
    graph_get_edges(src, list);
    graph_copy(src, dst);
    graph_clear_edges(dst);
    
    while(list->size){
        edge = edge_list_shift(list);
        graph_set_w_edge(dst, edge.start, edge.end, edge.weight);
        if(!graph_is_bridge(dst, edge.start, edge.end)){
            graph_unset_edge(dst, edge.start, edge.end);
        }
    }
}

void graph_boruvka(struct graph *src, struct graph *dst)
{
    int seg_count, at, to, edge_count = -1;
    
    struct edge min_edge = edge_create(99, 99, 99);
    struct linked_edge_list *list = edge_list_create();
    struct edge_node *iter = 0;
    
    graph_copy(src, dst);
    graph_clear_edges(dst);
    
    while(edge_count != graph_edge_count(dst)){
        edge_count = graph_edge_count(dst);
        graph_clear_visits(dst);
        edge_list_clear(list);
        for(seg_count = 0;seg_count < dst->v_count;seg_count++){
            min_edge.weight = 99;
            for(at = 0;at < dst->v_count;at++){
                if(graph_can_accessible(dst, seg_count, at) && !dst->is_visited[at]){
                    dst->is_visited[at] = 1;
                    for(to = 0;to < dst->v_count;to++){
                        if(src->adj_matrix[at][to] && !graph_can_accessible(dst, at, to)){
                            if(min_edge.weight > src->adj_matrix[at][to]){
                                graph_set_w_edge(dst, at, to, 1);
                                if(graph_is_bridge(dst, at, to)){
                                    min_edge.start = at;
                                    min_edge.end = to;
                                    min_edge.weight =  src->adj_matrix[at][to];
                                }
                                graph_unset_edge(dst, at, to);
                            }
                        }
                    }
                }
            }
            if(min_edge.weight != 99){
                edge_list_push(list, min_edge);
            }
        }
        
        if(!list->size)break;
        
        iter = list->head;
        while(iter){
            graph_set_w_edge(dst, iter->value.start, iter->value.end, iter->value.weight);
            iter = iter->next;
        }
    }
}

void graph_prim(struct graph *src, int start, struct graph *dst)
{
    struct linked_list *list = list_create();
    struct node *iter = 0;
    struct edge min_edge = edge_create(99, 99, 99);
    int at, to, *is_visited;
    
    is_visited = calloc(sizeof(int), src->v_count);
    list_push(list, start);
    is_visited[start] = 1;
    
    while(list->size != graph_degree(src) - 1){
        min_edge.weight = 99;
        for(iter = list->head;iter != 0;iter = iter->next){
            at = iter->value;
            for(to = 0;to < src->v_count;to++){
                if(src->adj_matrix[at][to] && !is_visited[to]){
                    if(min_edge.weight > src->adj_matrix[at][to]){
                        min_edge.start = at;
                        min_edge.end = to;
                        min_edge.weight = src->adj_matrix[at][to];
                    }
                }
            }
        }
        if(min_edge.weight != 99){
            list_push(list, min_edge.end);
            graph_set_w_edge(dst, min_edge.start, min_edge.end, min_edge.weight);
            is_visited[min_edge.end] = 1;
        }else{
            break;
        }
    }
    free(is_visited);
}

void graph_reverse_kruskal(struct graph *src, struct graph *dst)
{
    struct linked_edge_list *list = edge_list_create();
    struct edge edge;
    
    graph_get_edges(src, list);
    graph_copy(src, dst);
    
    while(list->size){
        edge = edge_list_pop(list);
        if(!graph_is_bridge(dst, edge.start, edge.end)){
            graph_unset_edge(dst, edge.start, edge.end);
        }
    }
}

void graph_fleury(struct graph *src, int base, struct graph *dst)
{
   int prev, at, to;
    graph_copy(src, dst);
    at = base;
    prev = -1;
    
    while(prev != at){
        prev = at;
        for(to = 0;to < dst->v_count;to++){
            if(dst->adj_matrix[at][to] && !graph_is_bridge(dst, at, to)){
                graph_unset_edge(dst, at, to);
                at = to;
                break;
            }
        }
    }
}

void graph_nearest_neighbour(struct graph *src, int base, struct graph *dst)
{
    struct edge min_edge = edge_create(99, 99, 99);
    int at, to, *is_visited;
    
    is_visited = calloc(sizeof(int), src->v_count);
    graph_clear_edges(dst);
    at = base;
    
    while(1){
        min_edge.weight = 99;
        
        for(to = 0;to < dst->v_count;to++){
            if(src->adj_matrix[at][to] && !is_visited[to] && min_edge.weight > src->adj_matrix[at][to]){
                graph_set_edge(dst, at, to);
                if(graph_is_bridge(dst, at, to)){
                    min_edge.start = at;
                    min_edge.end = to;
                    min_edge.weight = src->adj_matrix[at][to];
                }
                graph_unset_edge(dst, at, to);
            }
        }
        if(min_edge.weight != 99){
            graph_set_edge(dst, min_edge.start, min_edge.end);
            at = min_edge.end;
            is_visited[at] = 1;
        }else{
            break;
        }
    }
}
