#include <gtk/gtk.h>
#include "graph.h"

enum algorithm{DFS, BFS, BestFS, UCS, KRUSKAL, BORUVKA, PRIM, REVERSE, FLEURY, NEIGHBOUR};

GtkBuilder *builder;
GtkWidget *window, *draw_area, *start_point_entry, *search_for_entry;

struct graph *board_graph, *path;
struct linked_list *path_list;
enum algorithm choosed_algorithm;
int is_clicked, is_line_clicked, from[2], to[2];
char node_to_label[255];
int label_to_node[255];

void on_button_run_clicked(GtkButton*);
void on_button_show_bridges_clicked(GtkButton*);
void on_radio_toggled(GtkToggleButton*);

gboolean on_board_draw(GtkWidget*, cairo_t*, gpointer);
gboolean on_button_press(GtkWidget*, GdkEventButton*, gpointer);
gboolean on_key_press (GtkWidget*, GdkEventKey*, gpointer);

void draw_graph_lines(struct graph*, cairo_t*, float, float, float);
void draw_graph_nodes(struct graph*, cairo_t*, float, float, float);
void draw_graph_connected_nodes(struct graph*, cairo_t*, float, float, float);
void draw_list(struct linked_list*, cairo_t*, float, float, float);
void draw_line(int, int, cairo_t*, float, float, float);

void set_label(int);

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    board_graph = graph_create(100);
    
    path = graph_create(100);
    path_list = list_create();
    
    is_clicked = is_line_clicked = 0;
    choosed_algorithm = DFS;
    
    memset(node_to_label, -1, sizeof(char) * 255);
    memset(label_to_node, -1, sizeof(int) * 255);
    
    builder = gtk_builder_new_from_file("main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    draw_area = GTK_WIDGET(gtk_builder_get_object(builder, "draw_area"));
    start_point_entry = GTK_WIDGET(gtk_builder_get_object(builder, "start_point_entry_1"));
    search_for_entry = GTK_WIDGET(gtk_builder_get_object(builder, "search_for_entry"));
   
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), 0);
    gtk_widget_add_events(draw_area, GDK_BUTTON_PRESS_MASK); 
    gtk_builder_connect_signals(builder, 0);

    gtk_widget_show(window);

    gtk_main();
    return 0;
}

void on_button_run_clicked(GtkButton *b)
{
    graph_clear_edges(path);
    graph_clear_visits(path);
    list_clear(path_list);
    int base, find;
    
    base = label_to_node[(int)gtk_entry_get_text(GTK_ENTRY(start_point_entry))[0]];
    find = label_to_node[(int)gtk_entry_get_text(GTK_ENTRY(search_for_entry))[0]];
    switch(choosed_algorithm){
        case DFS :
        graph_DFS(board_graph, base, find, path);
        graph_track_path(path, find, path_list);
        break;
        case BFS :
        graph_BFS(board_graph, base, find, path);
        graph_track_path(path, find, path_list);
        break;
        case BestFS :
        graph_BestFS(board_graph, base, find, path);
        graph_track_path(path, find, path_list);
        break;
        case UCS :
        graph_UCS(board_graph, base, find, path);
        graph_track_path(path, find, path_list);
        break;
        case KRUSKAL :
        graph_kruskal(board_graph, path);
        break;
        case BORUVKA :
        graph_boruvka(board_graph, path);
        break;
        case PRIM :
        for(base = 0;base < board_graph->v_count;base++){
            for(find = 0;find < board_graph->v_count;find++){
                if(board_graph->adj_matrix[base][find]){
                    base = find;
                    graph_prim(board_graph, base, path);
                    gtk_widget_queue_draw(draw_area);
                    return;
                }
            }
        }
        break;
        case REVERSE :
        graph_reverse_kruskal(board_graph, path);
        break;
        case FLEURY : 
        graph_fleury(board_graph, base, path);
        gtk_widget_queue_draw(draw_area);
        break;
        case NEIGHBOUR :
        graph_nearest_neighbour(board_graph, base, path);
        gtk_widget_queue_draw(draw_area);
        break;
        default:
        break;
    }
    gtk_widget_queue_draw(draw_area);
}

void on_button_show_bridges_clicked(GtkButton *b)
{
    int at, to;
    graph_clear_edges(path);
    for(at = 0;at < board_graph->v_count;at++){
        for(to = 0;to < board_graph->v_count;to++){
            if(graph_is_bridge(board_graph, at, to)){
                graph_set_edge(path, at, to);
            }
        }
    }
    gtk_widget_queue_draw(draw_area);
}

void on_radio_toggled(GtkToggleButton *b)
{
    if(gtk_toggle_button_get_active(b)){
        choosed_algorithm = atoi(gtk_widget_get_name(GTK_WIDGET(b)));
    }
}

gboolean on_board_draw(GtkWidget *w, cairo_t *cr, gpointer p)
{
    draw_graph_lines(board_graph, cr, 0.8, 0, 0);
    draw_graph_nodes(board_graph, cr, 0.8, 0, 0);
    
    if(choosed_algorithm == DFS || choosed_algorithm == BFS || choosed_algorithm == BestFS || choosed_algorithm == UCS){
        draw_graph_lines(path, cr, 0, 0, 0.8);
        draw_graph_connected_nodes(path, cr, 0, 0, 0.8);
        
        draw_list(path_list, cr, 0.8, 0, 0.8);
    }else{
        draw_graph_lines(path, cr, 0, 0, 0.8);
        draw_graph_connected_nodes(path, cr, 0, 0, 0.8);
    }
    
    int from_x, from_y;
    char tmp[10];
    
    if(is_clicked && node_to_label[from[0] + from[1] * 10] != -1){
        from_x = 48 * ((from[0] + from[1] * 10) % 10) + 25;
        from_y = 48 * ((from[0] + from[1] * 10) / 10) + 25;
        
        cairo_set_source_rgb(cr, 0.8, 0.8, 0);
        cairo_move_to(cr, from_x, from_y);
        cairo_arc(cr, from_x, from_y, 8, 0, 8);
        cairo_fill(cr);
        
        cairo_set_source_rgb(cr, 1 -  0.8, 1 - 0.8, 1);
        cairo_move_to(cr, from_x - 3, from_y + 3);
        sprintf(tmp, "%c", node_to_label[from[0] + from[1] * 10]);
        cairo_show_text(cr, tmp);
        cairo_stroke(cr);
    }
    
    if(is_line_clicked){
        draw_line(from[0] + from[1] * 10, to[0] + to[1] * 10, cr, 0.8, 0.8, 0);
    }

    return FALSE;
}

gboolean on_button_press(GtkWidget *w, GdkEventButton *e, gpointer data)
{
    int coord_x, coord_y;
    
    coord_x = (int)((e->x - 25) / 48);
    coord_y = (int)((e->y - 25) / 48);
    
    if(e->x > 480)return TRUE;
    
    if(is_clicked){
        to[0] = coord_x;
        to[1] = coord_y;
        
        int vertice_from = from[0] + from[1] * 10;
        int vertice_to = to[0] + to[1] * 10;
            
        if(vertice_from != vertice_to){
            if(board_graph->adj_matrix[vertice_from][vertice_to]){
                is_line_clicked = 1;
                char tmp[20];
                sprintf(tmp, "%d", board_graph->adj_matrix[vertice_from][vertice_to]);
            }else{
                if(node_to_label[vertice_from] == -1){
                    set_label(vertice_from);
                }
                if(node_to_label[vertice_to] == -1){
                    set_label(vertice_to);
                }
                graph_set_edge(board_graph, vertice_from, vertice_to);
            }
        }else{
            if(node_to_label[vertice_from] == -1){
                set_label(vertice_from);
            }
            if(node_to_label[vertice_to] == -1){
                set_label(vertice_to);
            }
        }
        is_clicked = 0;
    }else{
        from[0] = coord_x;
        from[1] = coord_y;
        is_line_clicked = 0;
        is_clicked = 1;
    }
    
    gtk_widget_queue_draw(draw_area);
    
    return TRUE;
}

gboolean on_key_press (GtkWidget *w, GdkEventKey *e, gpointer data)
{
    int vertice_from, vertice_to;
    
    vertice_from = from[0] + from[1] * 10;
    vertice_to = to[0] + to[1] * 10;
    
    if(e->keyval == 65293){
        is_clicked = 0;
        is_line_clicked = 0;
        gtk_widget_queue_draw(draw_area);
        return TRUE;
    }
    
    if(is_clicked){
        if(e->keyval == GDK_KEY_Delete){
            label_to_node[(int)node_to_label[vertice_from]]= -1;
            node_to_label[vertice_from] = -1;
            for(vertice_to = 0;vertice_to < board_graph->v_count;vertice_to++){
                board_graph->adj_matrix[vertice_from][vertice_to] = 0;
                board_graph->adj_matrix[vertice_to][vertice_from] = 0;
            }
            is_clicked = 0;
            gtk_widget_queue_draw(draw_area);
        }else if(('a' <= e->keyval && e->keyval <= 'z') || ('A' <= e->keyval && e->keyval <= 'Z')){
            if(label_to_node[(int)e->keyval] == -1){
                label_to_node[(int)node_to_label[vertice_from]] = -1;
                label_to_node[(int)e->keyval] = vertice_from;
                node_to_label[vertice_from] = e->keyval;
                is_clicked = 0;
            gtk_widget_queue_draw(draw_area);
            }
        }
    }else if(is_line_clicked){
        if(e->keyval == GDK_KEY_Delete){
            board_graph->adj_matrix[vertice_from][vertice_to] = 0;
            board_graph->adj_matrix[vertice_to][vertice_from] = 0;
            gtk_widget_queue_draw(draw_area);
            is_line_clicked = 0;
        }else if('0' <= e->keyval && e->keyval <= '9'){
            board_graph->adj_matrix[vertice_from][vertice_to] = e->keyval - '0';
            board_graph->adj_matrix[vertice_to][vertice_from] = e->keyval - '0';
            gtk_widget_queue_draw(draw_area);
            is_line_clicked = 0;
        }
    }
    return TRUE;
}

void draw_graph_lines(struct graph *g, cairo_t *cr, float red, float green, float blue)
{
    int at, to, from_x, from_y, to_x, to_y;
    char tmp[10];
    
    cairo_set_source_rgb(cr, red, green, blue);
    
    for(at = 0;at < g->v_count;at++){
        from_x = (at % 10) * 48 + 25;
        from_y = (at / 10) * 48 + 25;
        for(to = 0;to < g->v_count;to++){
            if(g->adj_matrix[at][to]){
                to_x = (to % 10) * 48 + 25;
                to_y = (to / 10) * 48 + 25;
                
                draw_line(at, to, cr, red, green, blue);
                
                cairo_set_source_rgb(cr, 0, 0, 0);
                cairo_move_to(cr, (from_x + to_x) / 2 + 5, (from_y + to_y) / 2 + 5);
                sprintf(tmp, "%d", g->adj_matrix[at][to]);
                cairo_show_text(cr, tmp);
                cairo_stroke(cr);
            }
        }
    }
}

void draw_graph_nodes(struct graph *g, cairo_t *cr, float red, float green, float blue)
{
    int at, from_x, from_y;
    char tmp[10];
    
    for(at = 0;at < g->v_count;at++){
        from_x = 48 * (at % 10) + 25;
        from_y = 48 * (at / 10) + 25;
        
        if(node_to_label[at] != -1){
            cairo_set_source_rgb(cr, red, green, blue);
            cairo_move_to(cr, from_x, from_y);
            cairo_arc(cr, from_x, from_y, 8, 0, 8);
            cairo_fill(cr);
        
            cairo_set_source_rgb(cr, 1 - red, 1 - green, 1 - blue);
            cairo_move_to(cr, from_x - 3, from_y + 3);
            sprintf(tmp, "%c", node_to_label[at]);
            cairo_show_text(cr, tmp);
            cairo_stroke(cr);
        }
    }
}

void draw_graph_connected_nodes(struct graph *g, cairo_t *cr, float red, float green, float blue)
{
    int at, from_x, from_y;
    char tmp[10];
    
    for(at = 0;at < g->v_count;at++){
        from_x = 48 * (at % 10) + 25;
        from_y = 48 * (at / 10) + 25;
        
        if(graph_node_degree(g, at) != 0 && node_to_label[at] != -1){
            cairo_set_source_rgb(cr, red, green, blue);
            cairo_move_to(cr, from_x, from_y);
            cairo_arc(cr, from_x, from_y, 8, 0, 8);
            cairo_fill(cr);
        
            cairo_set_source_rgb(cr, 1 - red, 1 - green, 1 - blue);
            cairo_move_to(cr, from_x - 3, from_y + 3);
            sprintf(tmp, "%c", node_to_label[at]);
            cairo_show_text(cr, tmp);
            cairo_stroke(cr);
        }
    }
}

void draw_list(struct linked_list *list, cairo_t *cr, float red, float green, float blue)
{
    int at, to;
    struct node *iter;
    
    if(!list->size)return;
    
    at = list->head->value;
    
    for(iter = list->head->next;iter != 0;iter = iter->next){
        to = iter->value;
        draw_line(at, to, cr, red, green, blue);
        at = to;
    }
}

void draw_line(int at, int to, cairo_t *cr, float red, float green, float blue)
{
    int from_x, from_y, to_x, to_y;
    char tmp[10];
    
    from_x = 48 * (at % 10) + 25;
    from_y = 48 * (at / 10) + 25;
                
    to_x = 48 * (to % 10) + 25;
    to_y = 48 * (to / 10) + 25;
                
    cairo_set_source_rgb(cr, red, green, blue);
    cairo_move_to(cr, from_x, from_y);                
    cairo_line_to(cr, to_x, to_y);
    cairo_stroke(cr);
                
    cairo_set_source_rgb(cr, red, green, blue);
    cairo_move_to(cr, from_x, from_y);
    cairo_arc(cr, from_x, from_y, 8, 0, 8);
    cairo_fill(cr);
        
    cairo_set_source_rgb(cr, 1 - red, 1 - green, 1 - blue);
    cairo_move_to(cr, from_x - 3, from_y + 3);
    sprintf(tmp, "%c", node_to_label[at]);
    cairo_show_text(cr, tmp);
    cairo_stroke(cr);
        
    cairo_set_source_rgb(cr, red, green, blue);
    cairo_move_to(cr, to_x, to_y);
    cairo_arc(cr, to_x, to_y, 8, 0, 8);
    cairo_fill(cr);
        
    cairo_set_source_rgb(cr, 1 - red, 1 - green, 1 - blue);
    cairo_move_to(cr, to_x - 3, to_y + 3);
    sprintf(tmp, "%c", node_to_label[to]);
    cairo_show_text(cr, tmp);
    cairo_stroke(cr);
                
    cairo_fill(cr);
}

void set_label(int at)
{
    int i;
    for(i = 'A';i <= 'Z';i++){
        if(label_to_node[i] == -1){
            label_to_node[i] = at;
            node_to_label[at] = i;
            return;
        }
    }
    
    for(i = 'a';i <= 'z';i++){
        if(label_to_node[i] == -1){
            label_to_node[i] = at;
            node_to_label[at] = i;
            return;
        }
    }
}

