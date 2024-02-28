#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include <math.h>
#include "graph.h"

/* Graph - Interface routines */ 

graph_t *create_graph(void){
	graph_t *g = (graph_t*)xcalloc(1, sizeof(graph_t)); 
	g->pv_list = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 
	
	g->pv_list->v = -1; 
	
	g->pv_list->ph_list = NULL; 
	g->pv_list->prev = g->pv_list; 
	g->pv_list->next = g->pv_list; 
	
	g->nr_vertices = 0; 
	g->nr_edges = 0; 
	
	return (g); 
}

ret_t add_vertex(graph_t *g, vertex_t v){
	vnode_t *pv_node = search_node_v(g->pv_list, v); 
	if(pv_node != NULL)
		return (G_VERTEX_EXISTS); 
	insert_end_v(g->pv_list, v); 
	g->nr_vertices++; 
	return (SUCCESS); 
}

ret_t remove_vertex(graph_t *g, vertex_t v){
	vnode_t *pv_node = NULL; 
	vnode_t *pv_node_of_hv = NULL; 
	hnode_t *ph_run = NULL; 
	hnode_t *ph_run_next = NULL; 
	ret_t ret; 
	
	pv_node = search_node_v(g->pv_list, v); 
	if(pv_node == NULL)
		return (G_INVALID_VERTEX); 

	ph_run = pv_node->ph_list->next; 
	while(ph_run != pv_node->ph_list){
		ph_run_next = ph_run->next; 
		pv_node_of_hv = search_node_v(g->pv_list, ph_run->v);
		ret = remove_vertex_h(pv_node_of_hv->ph_list, v); 
		assert(ret == SUCCESS); 
		free(ph_run); 
		g->nr_edges--; 
		ph_run = ph_run_next; 
	}

	free(pv_node->ph_list); 
	generic_delete_v(pv_node); 
	g->nr_vertices--; 

	return (SUCCESS); 
}

ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end, double w){
	vnode_t *pv_node_start = NULL; 
	vnode_t *pv_node_end = NULL; 
	hnode_t *ph_node = NULL; 

	pv_node_start = search_node_v(g->pv_list, v_start); 
	pv_node_end = search_node_v(g->pv_list, v_end); 
	if(pv_node_start == NULL || pv_node_end == NULL)
		return (G_INVALID_VERTEX); 

	ph_node = search_node_h(pv_node_start->ph_list, v_end); 
	if(ph_node != NULL)
		return (G_EDGE_EXISTS); 

	assert(insert_end_h(pv_node_start->ph_list, v_end, w) == SUCCESS); 
	assert(insert_end_h(pv_node_end->ph_list, v_start, w) == SUCCESS); 

	g->nr_edges++; 
	return (SUCCESS); 
}

ret_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end){
	vnode_t *pv_start = NULL; 
	vnode_t *pv_end = NULL; 
	ret_t ret; 

	pv_start = search_node_v(g->pv_list, v_start); 
	pv_end = search_node_v(g->pv_list, v_end); 

	if(pv_start == NULL || pv_end == NULL)
		return (G_INVALID_VERTEX); 

	ret = remove_vertex_h(pv_start->ph_list, v_end); 
	if(ret == HLIST_DATA_NOT_FOUND)
		return (G_INVALID_EDGE); 

	ret = remove_vertex_h(pv_end->ph_list, v_start); 
	if(ret == HLIST_DATA_NOT_FOUND)
		return (G_INVALID_EDGE); 
	
	g->nr_edges--; 
	return (SUCCESS); 
}

void print_graph(graph_t *g, const char *msg){
	vnode_t *pv_node = NULL; 
	hnode_t *ph_node = NULL; 

	puts(msg); 

	for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next){
		printf("[%d]\t--->\t", pv_node->v); 
		for(ph_node = pv_node->ph_list->next; ph_node != pv_node->ph_list; ph_node = ph_node->next){
			printf("[%d]<->", ph_node->v); 
		}
		puts("[END]"); 
	}
}

int get_nr_vertices(graph_t *g){
	return (g->nr_vertices); 
}

int get_nr_edges(graph_t *g){
	return (g->nr_edges); 
}

ret_t destroy_graph(graph_t **pp_g){
	graph_t *g = NULL; 
	vnode_t *pv_node = NULL; 
	vnode_t *pv_node_next = NULL; 

	g = *pp_g; 

	for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node_next){
		pv_node_next = pv_node->next; 
		destroy_list_h(&pv_node->ph_list); 
		free(pv_node); 
	}

	free(g->pv_list); 
	free(g); 

	*pp_g = NULL; 

	return (SUCCESS); 
}

ret_t dfs(graph_t *g){
	vnode_t *pv_run; 

	reset(g); 
	printf("[BEGINNING]<->"); 
	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		if(pv_run->c == WHITE)
			dfs_visit(g, pv_run); 
	}
	puts("[END]"); 

	return (SUCCESS); 
}

ret_t bfs(graph_t *g, vertex_t v){
	vnode_t *pv_source; 
	vnode_t *u = NULL; 
	vnode_t *pv_of_ph; 
	hnode_t *ph_run; 

	v_queue_t *Q = NULL; 

	reset(g); 

	pv_source = search_node_v(g->pv_list, v); 
	if(pv_source == NULL)
		return (G_INVALID_VERTEX); 

	pv_source->c = GRAY; 

	Q = v_create_queue(); 
	assert(v_enqueue(Q, pv_source)); 
	printf("[BEGINNING]<->"); 
	while(v_is_queue_empty(Q) != TRUE){
		assert(v_dequeue(Q, &u) == SUCCESS); 
		printf("[%d]<->", u->v); 
		ph_run = u->ph_list->next; 
		while(ph_run != u->ph_list){
			pv_of_ph = search_node_v(g->pv_list, ph_run->v); 
			if(pv_of_ph->c == WHITE){
				pv_of_ph->c = GRAY; 
				assert(v_enqueue(Q, pv_of_ph) == SUCCESS); 
			}
			ph_run = ph_run->next; 
		}
		u->c = BLACK; 
	}
	puts("[END]"); 
	assert(v_destroy_queue(&Q) == SUCCESS && Q == NULL); 

	return (SUCCESS); 
}

ret_t dijkstra(graph_t *g, vertex_t s){
	vnode_t *pv_s = NULL; 
	vnode_t *pv_u = NULL; 
	vnode_t *pv_of_ph = NULL; 
	vnode_t *pv_run = NULL; 
	hnode_t *ph_run = NULL; 
	v_prio_queue_t *p_prio_queue = NULL; 

	pv_s = search_node_v(g->pv_list, s); 
	if(pv_s == NULL)
		return (G_INVALID_VERTEX); 

	initialize_single_source(g, pv_s); 
	
	// Q = G.V
	p_prio_queue = v_create_prio_queue(); 
	for(pv_run = g->pv_list->next; 
		pv_run != g->pv_list; 
		pv_run = pv_run->next)
		v_prio_enqueue(p_prio_queue, pv_run); 

	// while Q != PHI 
	while(v_is_prio_queue_empty(p_prio_queue) != TRUE){
		// u = EXTRACT-MIN(Q)
		pv_u = NULL; 
		v_prio_dequeue_min(p_prio_queue, &pv_u); 
		// for every v in Adj[u]
		// 		relax(u, v, w)
		for(ph_run = pv_u->ph_list->next; 
			ph_run != pv_u->ph_list; 
			ph_run = ph_run->next){
			pv_of_ph = search_node_v(g->pv_list, ph_run->v); 
			relax(g, pv_u, pv_of_ph); // relax(u, v, w)
		}
	}

	v_destroy_prio_queue(&p_prio_queue); 
	return (SUCCESS); 
}

/* Graph - Auxillary routines - traversal algorithms */ 

void reset(graph_t *g){
	vnode_t *pv_run; 

	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		pv_run->c = WHITE; 
	}
}

void dfs_visit(graph_t *g, vnode_t *pv_node){
	hnode_t *ph_run = NULL;
	vnode_t *pv_of_hnode = NULL;  

	printf("[%d]<->", pv_node->v); 
	pv_node->c = GRAY; 

	for(ph_run = pv_node->ph_list->next; ph_run != pv_node->ph_list; ph_run = ph_run->next){
		pv_of_hnode = search_node_v(g->pv_list, ph_run->v); 
		if(pv_of_hnode->c == WHITE)
			dfs_visit(g, pv_of_hnode); 
	}
	pv_node->c = BLACK; 
}

/* Graph - Auxillary routines for shortest path algorithms */ 
void initialize_single_source(graph_t *g, vnode_t *pv_s){
	vnode_t *pv_run = NULL; 

	pv_run = g->pv_list->next; 
	while(pv_run != g->pv_list){
		pv_run->d = INFINITY; 
		pv_run->u_pred = NULL; 
		pv_run = pv_run->next; 
	}
	pv_s->d = 0.0; 
} 

void relax(graph_t *g, vnode_t *pv_u, vnode_t *pv_v){
	hnode_t *ph_node = NULL; 
	double w; 

	ph_node = search_node_h(pv_u->ph_list, pv_v->v); 
	w = ph_node->w; 

	if(pv_v->d > pv_u->d + w){
		pv_v->d = pv_u->d + w; 
		pv_v->u_pred = pv_u; 
	}
}

/*
struct vnodeptr_node
{
	vnode_t* pv_node; 
	struct vnodeptr_node* prev; 
	struct vnodeptr_node* next; 
}; 

p1[1|hlist_t*|color|pred|d|prev|next]
p2[2|hlist_t*|color|pred|d|prev|next]
p3[3|hlist_t*|color|pred|d|prev|next]
p4[4|hlist_t*|color|pred|d|prev|next]
p5[5|hlist_t*|color|pred|d|prev|next]

[p1]<->[p2]<->[p3]<->[p4]<->[p5]

1->3->5 

print_shortest_path(g, p5)

[p5]<->[p5->u_pred==p3]<->[p3->u_pred==p1]

[p5]
[p3]
[p1]

p1->v == 1 
p3->v == 3 
p5->v == 5 
*/ 

void print_shortest_path(graph_t *g, vnode_t *pv_node){
	v_stack_t *pvq_stack = NULL; 
	vnode_t *pv_poped_node = NULL; 
	vertex_t curr_vertex_number; 
	double d; 

	curr_vertex_number = pv_node->v; 
	d = pv_node->d; 

	pvq_stack = v_create_stack(); 
	while(pv_node != NULL){
		v_push_stack(pvq_stack, pv_node); 
		pv_node = pv_node->u_pred; 
	}

	printf("Shortest path to [%d]\n", curr_vertex_number); 
	printf("[BEGINNING]<->"); 
	while(v_is_stack_empty(pvq_stack) != TRUE){
		pv_poped_node = NULL; 
		v_pop_stack(pvq_stack, &pv_poped_node); 
		printf("[%d]<->", pv_poped_node->v); 	
	}
	printf("[COST:%lf]\n", d); 
	puts("[END]"); 
	
	v_destroy_stack(&pvq_stack); 
}

void print_all_shortest_paths(graph_t *g){
	vnode_t *pv_node = NULL; 
	for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next){
		print_shortest_path(g, pv_node);  
	}
}

/* Graph - Auxillary routines - Part 1 - Vertical List Management */ 

vlist_t *create_list_v(void){
	vnode_t *pv_head_node = get_node_v(-1); 
	pv_head_node->prev = pv_head_node; 
	pv_head_node->next = pv_head_node; 
	return (pv_head_node); 
}

ret_t insert_end_v(vlist_t *pv_list, vertex_t v_new){
	generic_insert_v(pv_list->prev, get_node_v(v_new), pv_list);
	return (SUCCESS);  
}

ret_t remove_vertex_v(vlist_t *pv_list, vertex_t r_vertex){
	vnode_t *pv_node = search_node_v(pv_list, r_vertex); 
	if(pv_node == NULL)
		return (VLIST_DATA_NOT_FOUND);
	generic_delete_v(pv_node);
	return (SUCCESS);  
}

ret_t destroy_list_v(vlist_t **pp_vlist){
	vlist_t *pv_list = *pp_vlist; 
	vnode_t *pv_run = NULL; 
	vnode_t *pv_run_next = NULL; 

	for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run_next){
		pv_run_next = pv_run->next; 
		free(pv_run); 
	}

	free(pv_list); 
	*pp_vlist = NULL; 

	return (SUCCESS); 
}

/* Vertical List - Auxillary Routines */ 
void generic_insert_v(vnode_t *p_beg, vnode_t *p_mid, vnode_t *p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void generic_delete_v(vnode_t *pv_node){
	pv_node->prev->next = pv_node->next; 
	pv_node->next->prev = pv_node->prev; 
	free(pv_node); 
}

vnode_t *search_node_v(vlist_t *pv_list, vertex_t v_search){
	vnode_t *pv_run = NULL; 
	for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next){
		if(pv_run->v == v_search)
			return (pv_run); 
	}

	return (NULL); 
}

vnode_t *get_node_v(vertex_t v_new){
	vnode_t *pv_new_node = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 
	pv_new_node->v = v_new; 
	pv_new_node->ph_list = create_list_h(); 
	pv_new_node->c = WHITE; 
	return (pv_new_node); 
}

/* Graph - Auxillary routines - Part 2 - Horizontal List Management */ 
hlist_t *create_list_h(void){
	hnode_t *ph_head_node = get_node_h(-1, 0.0); 
	ph_head_node->prev = ph_head_node; 
	ph_head_node->next = ph_head_node; 
	return (ph_head_node); 
} 

ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new, double w){
	generic_insert_h(ph_list->prev, get_node_h(v_new, w), ph_list); 
	return (SUCCESS); 
}

ret_t remove_vertex_h(hlist_t *ph_list, vertex_t r_vertex){
	hnode_t *ph_node = search_node_h(ph_list, r_vertex); 
	if(ph_node == NULL)
		return (HLIST_DATA_NOT_FOUND);
	generic_delete_h(ph_node); 
	return (SUCCESS);  	
}

ret_t destroy_list_h(hlist_t **pp_hlist){
	hlist_t *ph_list = *pp_hlist; 
	hnode_t *ph_run = NULL; 
	hnode_t *ph_run_next = NULL; 

	for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run_next){
		ph_run_next = ph_run->next; 
		free(ph_run); 
	}

	free(ph_list); 
	*pp_hlist = NULL; 

	return (SUCCESS); 
}

/* Horizontal List - Auxillary Routines */ 
void generic_insert_h(hnode_t *p_beg, hnode_t *p_mid, hnode_t *p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void generic_delete_h(hnode_t *ph_node){
	ph_node->prev->next = ph_node->next; 
	ph_node->next->prev = ph_node->prev; 
	free(ph_node); 
} 

hnode_t *search_node_h(hlist_t *ph_list, vertex_t v_search){
	hnode_t *ph_run = NULL; 
	
	for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run->next){
		if(ph_run->v == v_search)
			return (ph_run); 
	}

	return (NULL); 
}

hnode_t *get_node_h(vertex_t v_new, double init_w){
	hnode_t *ph_new_node = (hnode_t*)xcalloc(1, sizeof(hnode_t)); 
	ph_new_node->v = v_new; 
	ph_new_node->w = init_w; 
	return (ph_new_node); 
}	

/* Graph - Auxillary Routines - BFS Queue */ 
v_queue_t *v_create_queue(void){
	return v_create_list(); 
}

ret_t v_enqueue(v_queue_t *pv_queue, vnode_t *pv_new_node){
	return v_insert_end(pv_queue, pv_new_node); 
}

ret_t v_dequeue(v_queue_t *pv_queue, vnode_t **ppv_beg_node){
	return v_remove_beg(pv_queue, ppv_beg_node); 
}

bool v_is_queue_empty(v_queue_t *pv_queue){
	return v_is_list_empty(pv_queue); 
}

ret_t v_destroy_queue(v_queue_t **ppv_queue){
	return v_destroy_list(ppv_queue); 
}

/* 
	Graph - Auxillary Routines - Stack of vnode_t* 
*/ 

v_stack_t *v_create_stack(){
	return v_create_list(); 
}

ret_t v_push_stack(v_stack_t *pvq_stack, vnode_t *pv_new_node){
	return v_insert_end(pvq_stack, pv_new_node); 
}

ret_t v_pop_stack(v_stack_t *pvq_stack, vnode_t **ppv_node){
	return v_remove_end(pvq_stack, ppv_node); 
}

bool v_is_stack_empty(v_stack_t *pvq_stack){
	return v_is_list_empty(pvq_stack); 
}

ret_t v_destroy_stack(v_stack_t **pvq_stack){
	return v_destroy_list(pvq_stack); 
}

/* Graph - BFS QUEUE - List */ 
v_list_t *v_create_list(void){
	v_list_t *pvq_list = get_node_vq(NULL); 
	pvq_list->prev = pvq_list; 
	pvq_list->next = pvq_list; 
	return (pvq_list);
}

ret_t v_insert_beg(v_list_t *pvq_list, vnode_t *pv_new_node){
	generic_insert_vq(pvq_list, get_node_vq(pv_new_node), pvq_list->next); 
	return (SUCCESS); 
}

ret_t v_insert_end(v_list_t *pvq_list, vnode_t *pv_new_node){
	generic_insert_vq(pvq_list->prev, get_node_vq(pv_new_node), pvq_list); 
	return (SUCCESS); 
}

ret_t v_remove_beg(v_list_t *pvq_list, vnode_t **ppv_beg_node){
	if(pvq_list->prev == pvq_list && pvq_list->next == pvq_list)
		return (V_LIST_EMPTY); 
	*ppv_beg_node = pvq_list->next->pv_node; 
	generic_delete_vq(pvq_list->next); 
	return (SUCCESS); 
}

ret_t v_remove_end(v_list_t *pvq_list, vnode_t **ppv_end_node){
	if(pvq_list->prev == pvq_list && pvq_list->next == pvq_list)
		return (V_LIST_EMPTY); 
	*ppv_end_node = pvq_list->prev->pv_node; 
	generic_delete_vq(pvq_list->prev); 
	return (SUCCESS); 
}

bool v_is_list_empty(v_list_t *pvq_list){
	if(pvq_list->prev == pvq_list && pvq_list->next == pvq_list)
		return (TRUE); 
	return (FALSE); 
}

ret_t v_destroy_list(v_list_t **ppvq_list){
	v_list_t *pvq_list = NULL; 
	v_node_t *pvq_run = NULL; 
	v_node_t *pvq_run_next = NULL;

	pvq_list = *ppvq_list; 
	pvq_run = pvq_list->next; 
	while(pvq_run != pvq_list){
		pvq_run_next = pvq_run->next; 
		free(pvq_run);  
		pvq_run = pvq_run_next; 
	} 

	free(pvq_list); 
	*ppvq_list = NULL; 
	return (SUCCESS); 
}

/* Graph - Auxillary Routines - Priority Queue (of vnode_t* as satellite data, 
	priority field is 'd' (cost of minimum path from source vertex to the 
	said vertex)) */ 


v_prio_queue_t *v_create_prio_queue(void){
	return v_create_list(); 
}

ret_t v_prio_enqueue(v_prio_queue_t *p_prio_queue, vnode_t *pv_node){
	return v_insert_end(p_prio_queue, pv_node); 
}

ret_t v_prio_dequeue_min(v_prio_queue_t *p_prio_queue, vnode_t **ppv_node){
	v_node_t *pvq_run = NULL; 
	v_node_t *pv_curr_min = NULL; ; 
	double curr_min = 0.0; 

	pvq_run = p_prio_queue->next;
	curr_min = pvq_run->pv_node->d;
	pv_curr_min = pvq_run; 

	while(pvq_run != p_prio_queue){
		if(pvq_run->pv_node->d < curr_min){
			curr_min = pvq_run->pv_node->d; 
			pv_curr_min = pvq_run; 
		}
		pvq_run = pvq_run->next; 
	}

	*ppv_node = pv_curr_min->pv_node; 
	generic_delete_vq(pv_curr_min); 
	return (SUCCESS); 
}

bool v_is_prio_queue_empty(v_prio_queue_t *p_prio_queue){
	return (p_prio_queue->next == p_prio_queue && p_prio_queue->prev == p_prio_queue); 
}

ret_t v_destroy_prio_queue(v_prio_queue_t **pp_prio_queue){
	return v_destroy_list(pp_prio_queue); 
}


/* Graph - BFS QUEUE - List - Auxillary */ 
void generic_insert_vq(v_node_t *pvq_beg, v_node_t *pvq_mid, v_node_t *pvq_end){
	pvq_mid->next = pvq_end; 
	pvq_mid->prev = pvq_beg; 
	pvq_beg->next = pvq_mid; 
	pvq_end->prev = pvq_mid; 
}

void generic_delete_vq(v_node_t *pvq_delete_node){
	pvq_delete_node->prev->next = pvq_delete_node->next; 
	pvq_delete_node->next->prev = pvq_delete_node->prev; 
	free(pvq_delete_node); 
} 

v_node_t *get_node_vq(vnode_t *pv_new_node){
	v_node_t *pvq_node = (v_node_t*)xcalloc(1, sizeof(v_node_t)); 
	pvq_node->pv_node = pv_new_node; 
	return (pvq_node); 
}

/* 
node_t* get_node(int new_data)
{
	node_t* p_new_node = NULL; 

	p_new_node = (node_t*)xcalloc(1, sizeof(node_t)); 
	p_new_node->data = new_data; 
	return (p_new_node); 
}

typedef struct node
{
	int data; 
	struct node* prev; 
	struct node* next; 
}node_t; 
*/ 

/* Graph - Auxillary routine - Part - Misc. */ 
void *xcalloc(size_t nr_items, size_t size_per_item){
	void *p = NULL; 
	p = calloc(nr_items, size_per_item); 
	assert(p); 
	return (p); 
}