#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define SUCCESS 1 
#define TRUE    1 
#define FALSE   0 

/* GRAPH  SYMBOLIC CONSTANTS */
#define G_INVALID_VERTEX    2 
#define G_INVALID_EDGE      3 
#define G_VERTEX_EXISTS     4
#define G_EDGE_EXISTS       5
#define G_CORRUPT           6 

/* DCDS SYMBOL CONSTANTS */
#define DCDS_INVALID_SET    7 
#define DCDS_DATA_EXISTS    8
#define DCDS_INVALID_REPR   9

/* GRAPH TYPEDEFS */
typedef int vertex_t; 
typedef struct hnode hnode_t; 
typedef hnode_t hlist_t; 
typedef struct vnode vnode_t; 
typedef vnode_t vlist_t; 
typedef struct graph graph_t; 

/* Edge vector typedefs */
typedef struct edge edge_t; 
typedef struct vector_edges vector_edges_t; 

/* DCDS TYPEDEFS */
typedef int data_t; 
typedef struct set set_t; 
typedef struct node node_t; 
typedef node_t list_t; 
typedef list_t dcds_t; 
typedef int status_t; 

typedef long long int ssize_t; 

/* GRAPH STRUCTURES */
struct hnode 
{
    vertex_t v; 
    double w; 
    int is_visited; 
    struct hnode* prev; 
    struct hnode* next; 
}; 

struct vnode
{
    vertex_t v; 
    hlist_t* ph_list; 

    struct vnode* prev; 
    struct vnode* next; 
}; 

struct graph 
{
    vlist_t* pv_list; 
    size_t nr_v; 
    size_t nr_e; 
}; 

struct edge 
{
    int u, v; 
    double w; 
}; 

/* Vector of struct edge* */
struct vector_edges
{
    struct edge** pp_edges; 
    ssize_t N; 
}; 

/* DCDS STRUCTURES */
struct set 
{
    data_t* arr; 
    ssize_t N; 
    data_t repr_data; 
}; 

struct node 
{
    set_t* p_set; 
    struct node* prev; 
    struct node* next; 
}; 

void test_kruskal(void); 

/* Graph interface routines */
graph_t* create_graph(void); 
status_t add_vertex(graph_t* g, vertex_t v); 
status_t remove_vertex(graph_t* g, vertex_t v); 
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w); 
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end); 
void show_graph(graph_t* g, const char* msg); 
void reset_visited_flag(graph_t* g); 
vector_edges_t* build_vector_of_edges_from_graph(graph_t* g); 
status_t destroy_graph(graph_t** pp_g); 

vector_edges_t* kruskals(graph_t* g); 
void print_mst(vector_edges_t* p_vec_edges, const char* msg); 

/* Vertical list management - Interface routines */
vlist_t* v_create_list(void); 
status_t v_insert_end(vlist_t* pv_list, vertex_t v); 

/* Vertical list management - Auxillary routines */
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end); 
void v_generic_delete(vnode_t* p_delete_node); 
vnode_t* v_search_node(vlist_t* pv_list, vertex_t v); 
vnode_t* v_get_node(vertex_t v); 

/* Horizontal list management - Interface routines */
hlist_t* h_create_list(void); 
status_t h_insert_end(hlist_t* ph_list, vertex_t v, double w); 

/* Horizontal list management - Auxillary routines */
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end); 
void h_generic_delete(hnode_t* p_delete_node); 
hnode_t* h_search_node(hlist_t* ph_list, vertex_t v); 
hnode_t* h_get_node(vertex_t v, double w); 

/* Auxillary routines */
void* xcalloc(size_t nr_elements, size_t size_per_element); 

/* Vector of struct edge* */
vector_edges_t* create_vector_edges(void); 
status_t push_back_edge(vector_edges_t* p_vec_edges, edge_t* p_edge); 
status_t destroy_vector_of_edges(vector_edges_t* p_vec_edges); 
void sort_vector_of_edges(vector_edges_t* p_vec); 
void show_vector_of_edges(vector_edges_t* p_vec_edges, const char* msg); 
struct edge* get_edge(int u, int v, double w); 

/* DCDS MANAGEMENT */
dcds_t* create_dcds(void); 
status_t add_set(dcds_t* p_dcds, set_t* p_set); 
status_t drop_set(dcds_t* p_dcds, set_t* p_set); 
status_t destroy_dcds(dcds_t** p_dcds); 
void show_dcds(dcds_t* p_dcds, const char* msg); 
status_t union_set(dcds_t* p_dcds, data_t repr_data_1, data_t repr_data_2); 
set_t* find_set(dcds_t* p_dcds, data_t repr_element); 
set_t* find_set_general(dcds_t* p_dcds, data_t element); 
set_t* create_set(data_t repr_data); 
node_t* find_set_internal(dcds_t* p_dcds, data_t repr_element); 
void show_set(set_t* p_set); 

void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end); 
void generic_delete(node_t* p_delete_node); 
node_t* search_node(list_t* p_list, set_t* p_set); 
node_t* get_node(set_t* p_set); 
void* xmalloc(size_t size); 

int main(void)
{
    test_kruskal(); 
    return (EXIT_SUCCESS);
}

void test_kruskal(void)
{
    graph_t* g = NULL; 
    vertex_t v; 
    vector_edges_t* p_vec_edges = NULL; 
    vector_edges_t* p_mst = NULL; 

    g = create_graph(); 
    for(v=1; v <= 6; ++v)
        add_vertex(g, v);
    add_edge(g, 1, 2, 2.0); 
    add_edge(g, 1, 6, 3.0); 
    add_edge(g, 2, 3, 1.0); 
    add_edge(g, 2, 6, 1.0); 
    add_edge(g, 2, 5, 2.0); 
    add_edge(g, 3, 4, 4.0); 
    add_edge(g, 3, 6, 1.0); 
    add_edge(g, 3, 5, 3.0); 
    add_edge(g, 4, 5, 2.0); 
    add_edge(g, 5, 6, 1.0); 

    show_graph(g, "GRAPH FOR MIN SPANNING TREE:"); 
    p_mst = kruskals(g); 
    print_mst(p_mst, "MIN SPANNIG TREE OF GRAPH:"); 
    destroy_vector_of_edges(p_mst); 
    p_mst = NULL; 
    destroy_graph(&g); 
    /* 
    p_vec_edges = build_vector_of_edges_from_graph(g);
    show_vector_of_edges(p_vec_edges, "Before sort");  
    sort_vector_of_edges(p_vec_edges); 
    show_vector_of_edges(p_vec_edges, "After sort:"); 
    destroy_vector_of_edges(p_vec_edges); 
    p_vec_edges = NULL; 
    */
}   

vector_edges_t* kruskals(graph_t* g)
{
    vector_edges_t* pE = NULL; 
    vector_edges_t* pA = NULL; 
    dcds_t* p_dcds = NULL; 
    ssize_t i; 
    set_t* p_set_u = NULL; 
    set_t* p_set_v = NULL; 
    
    vnode_t* pv_run = NULL; 

    pE = build_vector_of_edges_from_graph(g); 
    sort_vector_of_edges(pE); 

    pA = create_vector_edges(); 
    p_dcds = create_dcds(); 

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
        make_set(p_dcds, pv_run->v); 

    for(i = 0; i < pE->N; ++i)
    {
        p_set_u = find_set_general(p_dcds, pE->pp_edges[i]->u);
        p_set_v = find_set_general(p_dcds, pE->pp_edges[i]->v); 
        if(p_set_u != p_set_v)
        {
            push_back_edge(pA, get_edge(pE->pp_edges[i]->u, 
                                        pE->pp_edges[i]->v, 
                                        pE->pp_edges[i]->w)
                        ); 
            union_set(p_dcds, p_set_u->repr_data, p_set_v->repr_data); 
        } 
    }

    destroy_vector_of_edges(pE); 
    pE = NULL; 
    destroy_dcds(&p_dcds); 

    return (pA); 
}

void print_mst(vector_edges_t* p_mst, const char* msg)
{
    show_vector_of_edges(p_mst, msg); 
}

/* Graph interface routines */
graph_t* create_graph(void)
{
    graph_t* g = NULL; 

    g = (graph_t*)xcalloc(1, sizeof(graph_t)); 
    g->pv_list = v_create_list(); 
    g->nr_v = 0; 
    g->nr_e = 0; 

    return (g); 
}

status_t add_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL; 

    pv_node = v_search_node(g->pv_list, v); 
    if(pv_node != NULL)
        return (G_VERTEX_EXISTS); 
    v_insert_end(g->pv_list, v); 
    g->nr_v += 1; 

    return (SUCCESS); 
}

status_t remove_vertex(graph_t* g, vertex_t v)
{
    vnode_t* pv_node = NULL; 
    vnode_t* pv_of_hvertex = NULL; 
    hnode_t* ph_run = NULL; 
    hnode_t* ph_run_next = NULL; 
    hnode_t* ph_of_v_in_hlist = NULL; 

    pv_node = v_search_node(g->pv_list, v); 
    if(pv_node == NULL)
        return (G_INVALID_VERTEX); 
    
    for(ph_run = pv_node->ph_list->next; 
        ph_run != pv_node->ph_list; 
        ph_run = ph_run_next)
    {
        ph_run_next = ph_run->next; 
        pv_of_hvertex = v_search_node(g->pv_list, ph_run->v); 
        
        if(pv_of_hvertex == NULL)
            return (G_CORRUPT); 
        
        ph_of_v_in_hlist =  h_search_node(pv_of_hvertex->ph_list, v); 
        if(ph_of_v_in_hlist == NULL)
            return (G_CORRUPT); 
       
        h_generic_delete(ph_of_v_in_hlist); 
        h_generic_delete(ph_run); 
        g->nr_e -= 1; 
    }

    free(pv_of_hvertex->ph_list); 
    v_generic_delete(pv_node); 
    g->nr_v -= 1; 

    return (SUCCESS); 
}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end, double w)
{
    vnode_t* pv_start = NULL; 
    vnode_t* pv_end = NULL; 
    hnode_t* ph_start_in_end = NULL; 
    hnode_t* ph_end_in_start = NULL; 

    pv_start = v_search_node(g->pv_list, v_start); 
    if(pv_start == NULL)
        return (G_INVALID_VERTEX); 
    pv_end = v_search_node(g->pv_list, v_end); 
    if(pv_end == NULL)
        return (G_INVALID_VERTEX); 

    ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start); 

    if(ph_end_in_start != NULL && ph_start_in_end != NULL)
        return (G_EDGE_EXISTS); 

    h_insert_end(pv_start->ph_list, v_end, w); 
    h_insert_end(pv_end->ph_list, v_start, w); 

    g->nr_e += 1;

    return (SUCCESS); 
}

status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end)
{
    vnode_t* pv_start = NULL; 
    vnode_t* pv_end = NULL; 
    hnode_t* ph_end_in_start = NULL; 
    hnode_t* ph_start_in_end = NULL; 

    pv_start = v_search_node(g->pv_list, v_start); 
    pv_end = v_search_node(g->pv_list, v_end); 

    if(pv_start == NULL || pv_end == NULL)
        return (G_INVALID_VERTEX); 

    ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start); 

    if(ph_end_in_start == NULL || ph_start_in_end == NULL)
        return (G_INVALID_EDGE); 

    h_generic_delete(ph_end_in_start); 
    h_generic_delete(ph_start_in_end); 

    g->nr_e -= 1; 

    return (SUCCESS); 
}

void show_graph(graph_t* g, const char* msg)
{
    vnode_t* pv_run = NULL; 
    hnode_t* ph_run = NULL; 

    if(msg)
        puts(msg); 

    printf("G(V,E):|V|=%llu, |E|=%llu\n", g->nr_v, g->nr_e); 
    
    for(pv_run = g->pv_list->next; 
        pv_run != g->pv_list; 
        pv_run = pv_run->next)
    {
        printf("[%d]\t->\t", pv_run->v); 
        for(ph_run = pv_run->ph_list->next; 
            ph_run != pv_run->ph_list; 
            ph_run = ph_run->next)
            printf("[%d]<->", ph_run->v); 
        puts("[END]"); 
    }
}

void reset_visited_flag(graph_t* g)
{
    vnode_t* pv_node = NULL; 
    hnode_t* ph_node = NULL; 

    for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next)
        for(ph_node = pv_node->ph_list->next; ph_node != pv_node->ph_list; ph_node = ph_node->next)
            ph_node->is_visited = FALSE; 
}

vector_edges_t* build_vector_of_edges_from_graph(graph_t* g)
{
    vector_edges_t* p_vec_edges = NULL; 
    vnode_t* pv_run = NULL; 
    vnode_t* pv_of_ph = NULL; 
    hnode_t* ph_run = NULL; 
    hnode_t* ph = NULL; 
    edge_t* p_edge = NULL; 

    reset_visited_flag(g); 
    p_vec_edges = create_vector_edges(); 
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        for(ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run->next)
        {
            if(ph_run->is_visited == FALSE)
            {
                ph_run->is_visited = TRUE; 
                pv_of_ph = v_search_node(g->pv_list, ph_run->v); 
                ph = h_search_node(pv_of_ph->ph_list, pv_run->v); 
                ph->is_visited = TRUE; 
                p_edge = get_edge(pv_run->v, ph_run->v, ph_run->w); 
                push_back_edge(p_vec_edges, p_edge); 
            }
        }
    }

    return (p_vec_edges); 
}

status_t destroy_graph(graph_t** pp_g)
{
    graph_t* g = NULL; 
    vnode_t* pv_run = NULL; 
    vnode_t* pv_run_next = NULL; 
    hnode_t* ph_run = NULL; 
    hnode_t* ph_run_next = NULL; 

    g = *pp_g; 
    for(pv_run = g->pv_list->next; 
        pv_run != g->pv_list; 
        pv_run = pv_run_next)
    {
        pv_run_next = pv_run->next;
        for(ph_run = pv_run->ph_list->next; 
            ph_run != pv_run->ph_list; 
            ph_run = ph_run_next)
        {
            ph_run_next = ph_run->next; 
            free(ph_run); 
        }
   
        free(pv_run->ph_list); 
        free(pv_run); 
    }
    free(g->pv_list); 
    free(g); 
    *pp_g = NULL; 

    return (SUCCESS); 
}

/* Vertical list management - Interface routines */
vlist_t* v_create_list(void)
{
    vlist_t* pv_list = NULL; 

    pv_list = (vlist_t*)xcalloc(1, sizeof(vnode_t)); 
    pv_list->v = -1; 
    pv_list->ph_list = NULL; 
    pv_list->prev = pv_list; 
    pv_list->next = pv_list; 

    return (pv_list); 
}

status_t v_insert_end(vlist_t* pv_list, vertex_t v)
{
    v_generic_insert(pv_list->prev, v_get_node(v), pv_list); 
    return (SUCCESS); 
}

/* Vertical list management - Auxillary routines */
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void v_generic_delete(vnode_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
}

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v)
{
    vnode_t* pv_run = NULL; 

    for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
        if(pv_run->v == v)
            return (pv_run); 
    
    return (NULL); 
}

vnode_t* v_get_node(vertex_t v)
{
    vnode_t* pv_node = NULL; 

    pv_node = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 

    pv_node->v = v; 
    pv_node->ph_list = h_create_list(); 

    return (pv_node); 
}

/* Horizontal list management - Interface routines */
hlist_t* h_create_list(void)
{
    hlist_t* ph_list = NULL; 

    ph_list = h_get_node(-1, 0.0); 
    ph_list->prev = ph_list; 
    ph_list->next = ph_list; 

    return (ph_list); 
}

status_t h_insert_end(hlist_t* ph_list, vertex_t v, double w)
{
    h_generic_insert(ph_list->prev, h_get_node(v, w), ph_list); 
    return (SUCCESS); 
}

/* Horizontal list management - Auxillary routines */
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void h_generic_delete(hnode_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t v)
{
    hnode_t* ph_run = NULL; 

    for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run->next)
        if(ph_run->v == v)
            return (ph_run); 

    return (NULL); 
}

hnode_t* h_get_node(vertex_t v, double w)
{
    hnode_t* ph_new_node = NULL; 

    ph_new_node = (hnode_t*)xcalloc(1, sizeof(hnode_t)); 
    ph_new_node->v = v; 
    ph_new_node->w = w; 
    ph_new_node->is_visited = FALSE; 

    return (ph_new_node); 
}

/* Auxillary routines */
void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    if(p == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}

/* Vector of struct edge* */
vector_edges_t* create_vector_edges(void)
{
    vector_edges_t* p_vec_edges = NULL; 

    p_vec_edges = (vector_edges_t*)xmalloc(sizeof(vector_edges_t)); 
    p_vec_edges->pp_edges = NULL; 
    p_vec_edges->N = 0; 

    return (p_vec_edges); 
}

status_t push_back_edge(vector_edges_t* p_vec_edges, edge_t* p_edge)
{
    p_vec_edges->pp_edges = (edge_t**)realloc(p_vec_edges->pp_edges, 
                                            (p_vec_edges->N + 1) * sizeof(edge_t)); 
    if(p_vec_edges->pp_edges == NULL)
    {
        puts("Error in resizing array"); 
        exit(EXIT_FAILURE); 
    }
    p_vec_edges->N += 1; 
    p_vec_edges->pp_edges[p_vec_edges->N - 1] = p_edge; 

    return (SUCCESS); 
}

status_t destroy_vector_of_edges(vector_edges_t* p_vec_edges)
{
    ssize_t i; 

    for(i = 0; i < p_vec_edges->N; ++i)
        free(p_vec_edges->pp_edges[i]);  
    
    free(p_vec_edges->pp_edges); 
    free(p_vec_edges); 

    return (SUCCESS); 
}

void sort_vector_of_edges(vector_edges_t* p_vec_edges)
{
    ssize_t i, j; 
    edge_t* key; 

    for(j = 1; j < p_vec_edges->N; ++j)
    {
        key = p_vec_edges->pp_edges[j]; 
        i = j - 1;
        while(i > -1 && p_vec_edges->pp_edges[i]->w > key->w)
        {
            p_vec_edges->pp_edges[i+1] = p_vec_edges->pp_edges[i]; 
            i = i - 1; 
        }
        p_vec_edges->pp_edges[i+1] = key; 
    }
}

void show_vector_of_edges(vector_edges_t* p_vec_edges, const char* msg)
{
    ssize_t i; 

    if(msg)
        puts(msg); 

    for(i = 0; i < p_vec_edges->N; ++i)
        printf("EDGE[%d-%d]:%lf\n", p_vec_edges->pp_edges[i]->u, 
                                    p_vec_edges->pp_edges[i]->v, 
                                    p_vec_edges->pp_edges[i]->w); 
}

edge_t* get_edge(int u, int v, double w)
{
    edge_t* p_edge = NULL; 

    p_edge = (edge_t*)xmalloc(sizeof(struct edge)); 
    p_edge->u = u; 
    p_edge->v = v; 
    p_edge->w = w; 

    return (p_edge); 
}

/* DCDS MANAGEMENT */
dcds_t* create_dcds(void)
{
    list_t* p_list = NULL; 

    p_list = get_node(NULL); 
    p_list->prev = p_list; 
    p_list->next = p_list; 

    return (p_list); 
}

status_t make_set(dcds_t* p_dcds, data_t repr_data)
{
    size_t i; 
    node_t* p_run = NULL; 

    for(p_run = p_dcds->next; p_run != p_dcds; p_run = p_run->next)
        for(i = 0; i < p_run->p_set->N; ++i)
            if(p_run->p_set->arr[i] == repr_data)
                return (DCDS_DATA_EXISTS);    
    
    generic_insert(p_dcds->prev, get_node(create_set(repr_data)), p_dcds); 
    return (SUCCESS); 
}

status_t union_set(dcds_t* p_dcds, data_t repr_data_x, data_t repr_data_y)
{
    node_t* p_run_x = NULL; 
    node_t* p_run_y = NULL; 
    size_t i; 

    p_run_x = find_set_internal(p_dcds, repr_data_x); 
    if(p_run_x == NULL)
        return (DCDS_INVALID_REPR); 

    p_run_y = find_set_internal(p_dcds, repr_data_y); 
    if(p_run_y == NULL)
        return (DCDS_INVALID_REPR); 

    p_run_x->p_set->arr = (data_t*)realloc(p_run_x->p_set->arr, 
                                            (p_run_x->p_set->N + p_run_y->p_set->N) * sizeof(int)); 
    if(p_run_x->p_set->arr == NULL)
    {
        puts("Error in resizing array"); 
        exit(EXIT_FAILURE); 
    }
   
    for(i = 0; i < p_run_y->p_set->N; ++i)
        p_run_x->p_set->arr[p_run_x->p_set->N + i] = p_run_y->p_set->arr[i];  
    p_run_x->p_set->N = p_run_x->p_set->N + p_run_y->p_set->N; 
    
    destroy_set(p_run_y->p_set); 
    generic_delete(p_run_y); 
    
    return (SUCCESS); 
}

set_t* find_set(dcds_t* p_dcds, data_t repr_element)
{
    node_t* p_run = NULL; 

    p_run = find_set_internal(p_dcds, repr_element); 
    return (p_run != NULL ? p_run->p_set : NULL); 
}

set_t* find_set_general(dcds_t* p_dcds, data_t element)
{
    node_t* p_run = NULL; 
    size_t i; 

    for(p_run = p_dcds->next; p_run != p_dcds; p_run = p_run->next)
        for(i = 0; i < p_run->p_set->N; ++i)
            if(element == p_run->p_set->arr[i])
                return (p_run->p_set); 

    return (NULL); 
}

node_t* find_set_internal(dcds_t* p_dcds, data_t repr_element)
{
    node_t* p_run = NULL; 

    for(p_run = p_dcds->next; p_run != p_dcds; p_run = p_run->next)
        if(repr_element == p_run->p_set->repr_data)
            return (p_run); 

    return (NULL); 
}

set_t* create_set(data_t repr_data)
{
    set_t* p_set = NULL; 

    p_set = (set_t*)xmalloc(sizeof(set_t)); 
    p_set->repr_data = repr_data; 
    p_set->N = 1; 
    p_set->arr = (data_t*)realloc(NULL, p_set->N * sizeof(data_t)); 
    if(p_set->arr == NULL)
    {
        puts("Error in resizing array"); 
        exit(EXIT_FAILURE); 
    }
    p_set->arr[p_set->N - 1] = repr_data; 

    return (p_set); 
} 

status_t drop_set(dcds_t* p_dcds, set_t* p_set)
{
    node_t* p_delete_node = NULL; 

    p_delete_node = search_node(p_dcds, p_set); 
    if(p_delete_node == NULL)
        return (DCDS_INVALID_SET); 
    destroy_set(p_delete_node->p_set); 
    generic_delete(p_delete_node); 
    return (SUCCESS); 
}

void show_set(set_t* p_set)
{
    size_t i; 
    printf("SET(REPR(%d)):", p_set->repr_data); 
    for(i = 0; i < p_set->N; ++i)
        printf("[%d]", p_set->arr[i]); 
    puts("[END]"); 
}

void show_dcds(dcds_t* p_dcds, const char* msg)
{
    node_t* p_run = NULL; 
    size_t i; 

    if(msg)
        puts(msg);

    for(p_run = p_dcds->next; p_run != p_dcds; p_run = p_run->next)
    {
        printf("SET(REPR(%d)):\t\t", p_run->p_set->repr_data); 
        for(i = 0; i < p_run->p_set->N; ++i)
            printf("[%d]", p_run->p_set->arr[i]); 
        puts("[END]"); 
    } 
}

status_t destroy_dcds(dcds_t** pp_dcds)
{
    dcds_t* p_dcds = NULL; 
    node_t* p_run = NULL; 
    node_t* p_run_next = NULL; 

    p_dcds = *pp_dcds; 
    for(p_run = p_dcds->next; p_run != p_dcds; p_run = p_run_next)
    {
        p_run_next = p_run->next; 
        destroy_set(p_run->p_set); 
        free(p_run); 
    }

    free(p_dcds); 
    *pp_dcds = NULL; 
    return (SUCCESS); 
}

status_t destroy_set(set_t* p_set)
{
    free(p_set->arr); 
    free(p_set); 
    return (SUCCESS); 
}

/* Helper routines -> list */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void generic_delete(node_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
}

node_t* search_node(list_t* p_list, set_t* p_set)
{
    node_t* p_run = NULL; 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        if(p_run->p_set == p_set)
            return p_run; 
    return (NULL); 
}

node_t* get_node(set_t* p_set)
{
    node_t* p_new_node = NULL; 

    p_new_node = (node_t*)xmalloc(sizeof(node_t)); 
    p_new_node->p_set = p_set; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 

    return (p_new_node); 
}

void* xmalloc(size_t size)
{
    void* p = NULL; 

    p = malloc(size); 
    if(p == NULL)
    {
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}

