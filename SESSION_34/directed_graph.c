#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 

#define SUCCESS 1 
#define G_INVALID_VERTEX 2 
#define G_INVALID_EDGE 3 
#define G_VERTEX_EXISTS 4 
#define G_EDGE_EXISTS 5 

typedef long long int vertex_t; 
typedef struct hnode hnode_t; 
typedef hnode_t hlist_t; 
typedef struct vnode vnode_t; 
typedef vnode_t vlist_t; 
typedef struct graph graph_t; 
typedef enum color color_t;
typedef int status_t; 

enum color 
{
    WHITE=0, 
    GRAY, 
    BLACK
}; 

struct hnode
{
    vertex_t v; 
    double w; 

    struct hnode* prev; 
    struct hnode* next; 
}; 

struct vnode 
{
    vertex_t v; 
    color_t color; 
    double d; 
    hlist_t* ph_adj; 
    struct vnode* v_pred; 

    struct vnode* prev; 
    struct vnode* next; 
}; 

struct graph
{
    vlist_t* pv_list; 
    size_t nr_vertices; 
    size_t nr_edges; 
}; 

graph_t* create_graph(void); 
status_t add_vertex(graph_t* g, vertex_t v); 
status_t add_edge(graph_t* g, vertex_t u, vertex_t v, double w); 
status_t remove_vertex(graph_t* g, vertex_t v); 
status_t remove_edge(graph_t* g, vertex_t u, vertex_t v); 
void show_graph(graph_t* g, const char* msg); 
status_t destroy_graph(graph_t** pp_g); 

vlist_t* v_create_list(void); 
status_t v_insert_end(vlist_t* pv_list, vertex_t v); 
void v_generic_insert(vnode_t* beg, vnode_t* mid, vnode_t* end); 
void v_generic_delete(vnode_t* pv_node); 
vnode_t* v_searcv_node(vlist_t* pv_list, vertex_t v); 
vnode_t* v_get_node(vertex_t v); 

hlist_t* h_create_list(void); 
status_t h_insert_end(hlist_t* ph_list, vertex_t v); 
void h_generic_insert(hnode_t* beg, hnode_t* mid, hnode_t* end); 
void h_generic_delete(hnode_t* ph_node); 
hnode_t* h_search_node(hlist_t* ph_list, vertex_t v); 
hnode_t* h_get_node(vertex_t v); 

int main(void)
{

}

graph_t* create_graph(void)
{

}

status_t add_vertex(graph_t* g, vertex_t v)
{

}

status_t add_edge(graph_t* g, vertex_t u, vertex_t v, double w)
{

}

status_t remove_vertex(graph_t* g, vertex_t v)
{

}

status_t remove_edge(graph_t* g, vertex_t u, vertex_t v)
{

}

void show_graph(graph_t* g, const char* msg)
{

}

status_t destroy_graph(graph_t** pp_g)
{

}

vlist_t* v_create_list(void)
{

}

status_t v_insert_end(vlist_t* pv_list, vertex_t v)
{

}

void v_generic_insert(vnode_t* beg, vnode_t* mid, vnode_t* end)
{

}

void v_generic_delete(vnode_t* pv_node)
{

}

vnode_t* v_searcv_node(vlist_t* pv_list, vertex_t v)
{
    
}

vnode_t* v_get_node(vertex_t v)
{

}

hlist_t* h_create_list(void)
{

}

status_t h_insert_end(hlist_t* ph_list, vertex_t v)
{

}

void h_generic_insert(hnode_t* beg, hnode_t* mid, hnode_t* end)
{

}

void h_generic_delete(hnode_t* ph_node)
{

}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t v)
{

}

hnode_t* h_get_node(vertex_t v)
{

}