#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <math.h> 

#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 
#define G_INVALID_VERTEX 2 
#define G_INVALID_EDGE 3 
#define G_VERTEX_EXISTS 4 
#define G_EDGE_EXISTS 5 

typedef long long int ssize_t; 
typedef long long int vertex_t; 
typedef struct hnode hnode_t; 
typedef hnode_t hlist_t; 
typedef struct vnode vnode_t; 
typedef vnode_t vlist_t;
typedef struct vnode_ptr vnodeptr_t;  
typedef vnodeptr_t vnodeptr_list_t; 
typedef vnodeptr_list_t vnodeptr_stack_t; 
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

struct vnodeptr 
{
    vnode_t* pv; 
    struct vnodeptr* prev; 
    struct vnodeptr* next; 
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
status_t bellman_ford(graph_t* g, vertex_t s); 

vlist_t* v_create_list(void); 
status_t v_insert_end(vlist_t* pv_list, vertex_t v); 
void v_generic_insert(vnode_t* beg, vnode_t* mid, vnode_t* end); 
void v_generic_delete(vnode_t* pv_node); 
vnode_t* v_searcv_node(vlist_t* pv_list, vertex_t v); 
vnode_t* v_get_node(vertex_t v); 

hlist_t* h_create_list(void); 
status_t h_insert_end(hlist_t* ph_list, vertex_t v, double w); 
void h_generic_insert(hnode_t* beg, hnode_t* mid, hnode_t* end); 
void h_generic_delete(hnode_t* ph_node); 
hnode_t* h_search_node(hlist_t* ph_list, vertex_t v); 
hnode_t* h_get_node(vertex_t v, double w); 

vnodeptr_list_t* vnodeptr_create_list(void); 
status_t vnodeptr_insert_end(vnodeptr_list_t* pvnodeptr_list, vnode_t* v); 
status_t vnodeptr_get_end(vnodeptr_list_t* pvnodeptr_list, vnode_t** pp_v); 
status_t vnodeptr_pop_end(vnodeptr_list_t* pvnodeptr_list, vnode_t** pp_v); 
void vnodeptr_generic_insert(vnodeptr_t* beg, vnodeptr_t* mid, vnodeptr_t* end); 
void vnodeptr_generic_delete(vnodeptr_t* pvnodeptr_node); 
vnodeptr_t* vnodeptr_search_node(vnodeptr_list_t* pvnodeptr_list, vertex_t v); 
vnodeptr_t* vnodeptr_get_node(vertex_t v); 

vnodeptr_stack_t* vnodeptr_create_stack(void); 
status_t vnodeptr_push(vnodeptr_stack_t* p_stack, vnode_t* pv); 
status_t vnodeptr_pop(vnodeptr_stack_t* p_stack, vnode_t** pp_v); 
status_t vnodeptr_top(vnodeptr_stack_t* p_stack, vnode_t** pp_v); 
status_t vnodeptr_is_stack_empty(vnodeptr_stack_t* p_stack); 
status_t vnodeptr_destroy_stack(vnodeptr_stack_t** pp_stack); 


int main(void)
{

}

graph_t* create_graph(void)
{
    graph_t* g = NULL; 

    g = (graph_t*)malloc(sizeof(graph_t)); 
    if(g == NULL)
    {
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    g->pv_list = v_create_list(); 
    g->nr_vertices = 0; 
    g->nr_edges = 0; 

    return (g); 
}

status_t add_vertex(graph_t* g, vertex_t v)
{

}

status_t add_edge(graph_t* g, vertex_t u, vertex_t v, double w)
{
    vnode_t* pv_u = NULL; 
    vnode_t* pv_v = NULL; 
    status_t status; 

    pv_u = v_search_node(g->pv_list, u); 
    if(pv_u == NULL)
        return (G_INVALID_VERTEX); 

    pv_v = v_search_node(g->pv_list, v); 
    if(pv_v == NULL)
        return (G_INVALID_VERTEX); 

    status = h_insert_end(pv_u->ph_adj, v, w); 
    if(status != SUCCESS)
    {
        puts("Error"); 
        exit(EXIT_FAILURE); 
    }

    g->nr_edges += 1; 
    return (SUCCESS); 
}

status_t remove_vertex(graph_t* g, vertex_t v)
{

}

status_t remove_edge(graph_t* g, vertex_t u, vertex_t v)
{
    vnode_t* pv_u = NULL; 
    hnode_t* ph_v = NULL; 

    pv_u = v_search_node(g->pv_list, u); 
    if(pv_u == NULL)
        return (G_INVALID_VERTEX); 
    
    ph_v = h_search_node(pv_u->ph_adj, v); 
    if(ph_v == NULL)
        return (G_INVALID_EDGE); 

    h_generic_delete(ph_v); 
    g->nr_edges -= 1; 

    return (SUCCESS); 
}

void show_graph(graph_t* g, const char* msg)
{

}

status_t destroy_graph(graph_t** pp_g)
{

}

status_t bellman_ford(graph_t* g, vertex_t s)
{
    vnode_t* pv_s = NULL;   
    vnode_t* pv_run = NULL; 
    vnode_t* pv_of_ph = NULL;
    hnode_t* ph_run = NULL; 
     
    ssize_t i; 

    pv_s = v_search_node(g->pv_list, s); 
    if(pv_s == NULL)
        return (G_INVALID_VERTEX); 

    /* initialise sing source -> start */
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run  = pv_run->next)
    {
        pv_run->d = INFINITY; 
        pv_run->v_pred = NULL; 
    }

    pv_s->d = 0.0; 
    /* initialise single source -> finish */
    for(i = 0; i < g->nr_vertices-1; ++i)
    {
        for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
        {
            for(ph_run = pv_run->ph_adj->next; ph_run != pv_run->ph_adj; ph_run = ph_run->next)
            {
                pv_of_ph = v_search_node(g->pv_list, ph_run->v); 
                /* relax -> start */
                if(pv_of_ph->d > pv_run->d + ph_run->w)
                {
                    pv_of_ph->d = pv_run->d + ph_run->w; 
                    pv_of_ph->v_pred = pv_run; 
                }
                /* relax -> finish*/
            }
        }
    }

    /* Checking for negative path cycle */
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        for(ph_run = pv_run->ph_adj->next; ph_run != pv_run->ph_adj; ph_run = ph_run->next)
        {
            pv_of_ph = v_search_node(g->pv_list, ph_run->v); 
            if(pv_of_ph->d > pv_run->d + ph_run->w)
                return (FALSE); /* Negative cycle exists */
        }
    }

    return (TRUE); /* Negative cycle does not exist */
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

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    
}

vnode_t* v_get_node(vertex_t v)
{

}

hlist_t* h_create_list(void)
{

}

status_t h_insert_end(hlist_t* ph_list, vertex_t v, double w)
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

hnode_t* h_get_node(vertex_t v, double w)
{

}

vnodeptr_list_t* vnodeptr_create_list(void)
{

}

status_t vnodeptr_insert_end(vnodeptr_list_t* pvnodeptr_list, vnode_t* v)
{

}

status_t vnodeptr_get_end(vnodeptr_list_t* pvnodeptr_list, vnode_t** pp_v)
{

}

status_t vnodeptr_pop_end(vnodeptr_list_t* pvnodeptr_list, vnode_t** pp_v)
{

}

void vnodeptr_generic_insert(vnodeptr_t* beg, vnodeptr_t* mid, vnodeptr_t* end)
{

}

void vnodeptr_generic_delete(vnodeptr_t* pvnodeptr_node)
{

}

vnodeptr_t* vnodeptr_search_node(vnodeptr_list_t* pvnodeptr_list, vertex_t v)
{

}

vnodeptr_t* vnodeptr_get_node(vertex_t v)
{

}

vnodeptr_stack_t* vnodeptr_create_stack(void)
{

}

status_t vnodeptr_push(vnodeptr_stack_t* p_stack, vnode_t* pv)
{

}

status_t vnodeptr_pop(vnodeptr_stack_t* p_stack, vnode_t** pp_v)
{

}

status_t vnodeptr_top(vnodeptr_stack_t* p_stack, vnode_t** pp_v)
{

}

status_t vnodeptr_is_stack_empty(vnodeptr_stack_t* p_stack)
{

}

status_t vnodeptr_destroy_stack(vnodeptr_stack_t** pp_stack)
{

}