#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "prio_queue.h"


int main(void)
{
    prio_queue_t* p_prio_queue = NULL; 
    data_t arr[] = {100, 40, 20, 10, 80, 90, 75, 52, 23}; 
    int i; 
    data_t data; 
    status_t ret; 

    p_prio_queue = create_prio_queue(); 
    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
        assert(prio_enqueue(p_prio_queue, arr[i]) == SUCCESS); 

    while(is_prio_queue_empty(p_prio_queue) != TRUE)
    {
        data = -1; 
        prio_dequeue_min(p_prio_queue, &data); 
        printf("data = %d\n", data); 
    }

    ret = destroy_prio_queue(&p_prio_queue); 
    assert(ret == 1 && p_prio_queue == NULL); 
    
    return (0); 
}



/* 
sturct hnode
{
    int v; 
    double w; 

    struct hnode* prev; 
    struct hnode* next; 
}; 

struct vnode
{
    int v; 
    struct hnode* ph_list; 
    int color; 
    double d; 
    struct vnode* u_pred; 

    struct vnode* prev; 
    struct vnode* next; 
}; 

struct vnodeptr_node
{
    struct vnode* pv_node; 
    struct node* prev; 
    struct node* next; 
}; 

int prio_dequeue_min(struct vnodeptr_node* p_list, struct vnode** ppv_node)
{
    struct vnodeptr_node* p_run = NULL; 
    struct vnodeptr_node* p_min_d_node = NULL; 
    double current_min_d; 

    if(is_vnodeptr_node_list_empty(p_list) == 1)
        return (3); 

    p_min_d_node = p_list->next; 
    current_min_d = p_min_d_node->d; 

    for(p_run = p_list->next; 
        p_run != p_list; 
        p_run = p_run->next)
    {
        if(p_run->pv_node->d < current_min_d)
        {
            p_min_d_node = pv_run->pv_node; 
            current_min_d = p_min_d_node->pv_node->d; 
        }
    }

    *ppv_node = p_min_d_node->pv_node; 
    generic_delete(p_min_d_node); 
  
    return (1); 
}

*/ 