/* 
BFS prototype 

vnode_t* data -> Linked List -> Queue 

Node layout for linked list with vnode_t* as data 

Linked List -> relevant API design 
Queue -> relevant API design 
*/ 

#include <stdio.h> 

typedef long long int vertex_t; 
typedef struct vptr_node vptr_node_t; 
typedef vptr_node_t vptr_list_t; 
typedef vptr_list_t vptr_queue_t; 

typedef struct vnode vnode_t; 
typedef struct hnode hnode_t; 
typedef hnode_t hlist_t; 

typedef int status_t; 

typedef enum color color_t; 

enum color 
{
    WHITE=0, 
    GRAY, 
    BLACK 
}; 

struct hnode 
{
    vertex_t v; 
    struct hnode* prev; 
    struct hnode* next; 
}; 

struct vnode
{
    vertex_t v; 
    hlist_t* ph_adj_list; 
    color_t color; 
    vnode_t* pv_pred; 

    struct vnode* prev; 
    struct vnode* next; 
}; 

struct vptr_node
{
    vnode_t* pv; 
    struct vptr_node* prev; 
    struct vptr_node* next; 
}; 

vptr_queue_t* vptr_create_queue(void); 
status_t vptr_enqueue(vptr_queue_t* pvptr_queue, vnode_t* pv); 
status_t vptr_dequeue(vptr_queue_t* pvptr_queue, vnode_t** pp_v); 
status_t vptr_destroy_queue(vptr_queue_t** pp_queue); 

vptr_list_t* vptr_create_list(void); 
status_t vptr_insert_end(vptr_list_t* pvptr_list, vnode_t* pv); 
status_t vptr_pop_start(vptr_list_t* pvptr_list, vnode_t** pp_v); 
status_t vptr_destroy_list(vptr_list_t** pp_vptr_list); 

void vptr_generic_insert(vptr_node_t* beg, vptr_node_t* mid, vptr_node_t* end); 
void vptr_generic_delete(vptr_node_t* pvptr_delete_node); 
vptr_node_t* vptr_search_node(vptr_list_t* pvptr_list, vnode_t* pv); 

vptr_node_t* vptr_get_node(vnode_t* pv_new_node); 
void* xcalloc(size_t nr_elements, size_t size_per_element); 

// EXERCISE : FINISH THIS IMPLEMENTATION 
// WRITE BFS BASED ON IT 
// INTEGRATE INTO FINAL APP 