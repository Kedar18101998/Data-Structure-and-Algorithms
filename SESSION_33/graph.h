#ifndef _GRAPH_H 
#define _GRAPH_H 

#include <stdio.h> 
#include <stdlib.h> 

/* Symbolic constants */ 
#define SUCCESS 1 

#define TRUE 1 
#define FALSE 0 

#define HLIST_DATA_NOT_FOUND 2 
#define VLIST_DATA_NOT_FOUND HLIST_DATA_NOT_FOUND

#define G_VERTEX_EXISTS 	3 
#define G_EDGE_EXISTS 		4
#define G_INVALID_VERTEX 	5 
#define G_INVALID_EDGE 		6

#define V_LIST_EMPTY 		7 
#define V_QUEUE_EMPTY 		V_LIST_EMPTY

 /* typedefs */
typedef struct graph graph_t; 
typedef struct hnode hnode_t; 
typedef hnode_t hlist_t;
typedef struct vnode vnode_t; 
typedef vnode_t vlist_t;  
typedef enum color color_t;  
typedef int ret_t; 
typedef int vertex_t; 
typedef int bool; 

typedef struct vnodeptr_node v_node_t; 
typedef v_node_t v_list_t; 
typedef v_list_t v_queue_t; 
typedef v_list_t v_stack_t; 
typedef v_list_t v_prio_queue_t; 

/* Internal layout *. 

/* Color enumerations */ 

enum color{
	WHITE = 0, 
	GRAY, 
	BLACK
}; 
 
 /* A node in horizontal list */ 
struct hnode{
	vertex_t v; 
	double w; 
	struct hnode *prev; 
	struct hnode *next; 
}; 

/* A node in vertical list */ 
struct vnode{
	vertex_t v; 
	hlist_t *ph_list; 
	color_t c; 
	double d; 
	vnode_t *u_pred; 

	struct vnode *prev; 
	struct vnode *next; 
}; 

/* A graph data structure */ 
struct graph{
	vlist_t *pv_list; 
	int nr_vertices; 
	int nr_edges; 
}; 

/* A node for vertical node queue */ 
struct vnodeptr_node{
	vnode_t *pv_node; 
	struct vnodeptr_node *prev; 
	struct vnodeptr_node *next; 
}; 

/* Part I : Graph management */ 

/* Graph interface routines */
graph_t *create_graph(void); 
ret_t add_vertex(graph_t *g, vertex_t v); 
ret_t remove_vertex(graph_t *g, vertex_t v); 
ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end, double w); 
ret_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end); 
void print_graph(graph_t *g, const char *msg); 
int get_nr_vertices(graph_t *g); 
int get_nr_edges(graph_t *g); 
ret_t destroy_graph(graph_t **pp_g); 

ret_t dfs(graph_t *g); 
ret_t bfs(graph_t *g, vertex_t v); 
ret_t dijkstra(graph_t *g, vertex_t s); 

/* Graph - Auxillary routines for traversal algorithms */ 

void reset(graph_t *g); 
void dfs_visit(graph_t *g, vnode_t *pv_node);

/* Graph - Auxillary routines for shortest path algorithms */ 
void initialize_single_source(graph_t *g, vnode_t *pv_s); 
void relax(graph_t *g, vnode_t *pv_u, vnode_t *pv_v); 
void print_shortest_path(graph_t *g, vnode_t *pv_node);  
void print_all_shortest_paths(graph_t *g); 

/* Graph - Auxillary routines - Part 1 - Vertical List Management */ 

vlist_t *create_list_v(void); 
ret_t insert_end_v(vlist_t *pv_list, vertex_t v_new); 
ret_t remove_vertex_v(vlist_t *pv_list, vertex_t r_vertex); 
ret_t destroy_list_v(vlist_t **pp_vlist); 

/* Vertical List - Auxillary Routines */ 
void generic_insert_v(vnode_t *p_beg, vnode_t *p_mid, vnode_t *p_end); 
void generic_delete_v(vnode_t *pv_node); 
vnode_t *search_node_v(vlist_t *pv_list, vertex_t v_search); 
vnode_t *get_node_v(vertex_t v_new); 

/* Graph - Auxillary routines - Part 2 - Horizontal List Management */ 
hlist_t *create_list_h(void); 
ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new, double w); 
ret_t remove_vertex_h(hlist_t *ph_list, vertex_t r_vertex); 
ret_t destroy_list_h(hlist_t **pp_hlist);

/* Horizontal List - Auxillary Routines */ 
void generic_insert_h(hnode_t *p_beg, hnode_t *p_mid, hnode_t *p_end); 
void generic_delete_h(hnode_t *ph_node); 
hnode_t *search_node_h(hlist_t *ph_list, vertex_t v_search); 
hnode_t *get_node_h(vertex_t v_new, double init_w); 

/* Graph - Auxillary Routines - BFS Queue */ 
v_queue_t *v_create_queue(void); 
ret_t v_enqueue(v_queue_t *pv_queue, vnode_t *pv_new_node); 
ret_t v_dequeue(v_queue_t *pv_queue, vnode_t **ppv_beg_node); 
bool v_is_queue_empty(v_queue_t *pv_queue); 
ret_t v_destroy_queue(v_queue_t **ppv_queue); 

/* 
	Graph - Auxillary routines - Stack of vnode_t* 
*/ 

v_stack_t *v_create_stack(); 
ret_t v_push_stack(v_stack_t *pvq_stack, vnode_t *pv_new_node); 
ret_t v_pop_stack(v_stack_t *pvq_stack, vnode_t **ppv_node); 
bool v_is_stack_empty(v_stack_t *pvq_stack); 
ret_t v_destroy_stack(v_stack_t **pvq_stack); 

/* Graph - Auxillary Routines - Priority Queue (of vnode_t* as satellite data, 
	priority field is 'd' (cost of minimum path from source vertex to the 
	said vertex)) */ 

v_prio_queue_t *v_create_prio_queue(void); 
ret_t v_prio_enqueue(v_prio_queue_t *p_prio_queue, vnode_t *pv_node); 
ret_t v_prio_dequeue_min(v_prio_queue_t *p_prio_queue, vnode_t **ppv_node); 
bool v_is_prio_queue_empty(v_prio_queue_t *p_prio_queue); 
ret_t v_destroy_prio_queue(v_prio_queue_t **pp_prio_queue); 

/* Graph - BFS QUEUE - List */ 
v_list_t *v_create_list(void); 
ret_t v_insert_beg(v_list_t *pvq_list, vnode_t *pv_new_node); 
ret_t v_insert_end(v_list_t *pvq_list, vnode_t *pv_new_node);
ret_t v_remove_beg(v_list_t *pvq_list, vnode_t **ppv_beg_node);
ret_t v_remove_end(v_list_t *pvq_list, vnode_t **ppv_end_node);  
bool v_is_list_empty(v_list_t *pvq_list); 
ret_t v_destroy_list(v_list_t **ppvq_list); 

/* Graph - BFS QUEUE - List - Auxillary */ 
void generic_insert_vq(v_node_t *pvq_beg, v_node_t *pvq_mid, v_node_t *pvq_end); 
void generic_delete_vq(v_node_t *pvq_delete_node); 
v_node_t *get_node_vq(vnode_t *pv_new_node); 


/* Graph - Auxillary routine - Part - Misc. */ 
void *xcalloc(size_t nr_items, size_t size_per_item); 

#endif /* _GRAPH_H */ 