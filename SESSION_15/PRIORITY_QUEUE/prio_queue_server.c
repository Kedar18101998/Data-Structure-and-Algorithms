#include <stdio.h> 
#include <stdlib.h> 
#include "prio_queue.h"

prio_queue_t* create_prio_queue(void)
{
    return create_list(); 
}

status_t prio_enqueue(prio_queue_t* p_prio_queue, data_t new_data)
{
    return insert_end(p_prio_queue, new_data); 
}

status_t prio_dequeue_min(prio_queue_t* p_prio_queue, int* p_min_data)
{
    int current_min_data; 
    node_t* p_run = NULL;
    node_t* p_min_data_node = NULL; 

    if(is_prio_queue_empty(p_prio_queue) == 1)
        return (LIST_EMPTY); 

    current_min_data = p_prio_queue->next->data; 
    p_min_data_node = p_prio_queue->next; 

    for(p_run = p_prio_queue->next; 
        p_run != p_prio_queue; 
        p_run = p_run->next)
    {
        if(p_run->data < current_min_data)
        {
            p_min_data_node = p_run; 
            current_min_data = p_run->data; 
        }
    }

    generic_delete(p_min_data_node); 
    *p_min_data = current_min_data; 
    return (SUCCESS); 
}


status_t is_prio_queue_empty(prio_queue_t* p_prio_queue)
{
    return is_list_empty(p_prio_queue); 
}

status_t destroy_prio_queue(prio_queue_t** pp_prio_queue)
{
    return destroy_list(pp_prio_queue); 
}

prio_queue_t* create_list()
{
    node_t* p_list = get_node(-1); 
    p_list->prev = p_list; 
    p_list->next = p_list; 

    return (p_list); 
}

status_t insert_beg(prio_queue_t* p_list, status_t new_data)
{
    generic_insert(p_list, get_node(new_data), p_list->next); 
    return (SUCCESS); 
}

status_t insert_end(prio_queue_t* p_list, data_t new_data)
{
    generic_insert(p_list->prev, get_node(new_data), p_list); 
    return (SUCCESS); 
}

status_t remove_beg(prio_queue_t* p_list, data_t* p_beg_data)
{
    if(is_list_empty(p_list) == 1)
        return (LIST_EMPTY); 
    *p_beg_data = p_list->next->data; 
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

status_t remove_end(prio_queue_t* p_list, data_t* p_end_data)
{
    if(is_list_empty(p_list) == 1)
        return (LIST_EMPTY); 
    *p_end_data = p_list->prev->data; 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

status_t is_list_empty(prio_queue_t* p_list)
{
    return (p_list->prev == p_list && p_list->next == p_list); 
}

status_t destroy_list(prio_queue_t** pp_list)
{
    node_t* p_list = *pp_list; 
    node_t* p_run = NULL; 
    node_t* p_run_next = NULL; 

    p_run = p_list->next; 
    while(p_run != p_list)
    {
        p_run_next = p_run->next; 
        free(p_run); 
        p_run = p_run_next; 
    }

    free(p_list); 
    *pp_list = NULL; 
    return (SUCCESS); 
}

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

node_t* get_node(int data)
{
    node_t* p_new_node = NULL; 

    p_new_node = (node_t*)xcalloc(1, sizeof(node_t)); 
    p_new_node->data = data; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 

    return (p_new_node); 
}

void* xcalloc(size_t nr_elements, size_t sizeof_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, sizeof_element); 
    assert(p); 

    return (p); 
}
