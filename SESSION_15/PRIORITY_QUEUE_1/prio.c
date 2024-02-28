#include <stdio.h> 
#include <stdlib.h> 
#include "prio.h"

prio_queue_t* create_prio_queue(void)
{
    return create_list(); 
}

status_t enqueue(prio_queue_t* p_prio_queue, data_t new_data)
{
    return insert_end(p_prio_queue, new_data); 
}

status_t min_dequeue(prio_queue_t* p_prio_queue, data_t* p_min_data)
{
    /* Breaking abstraction level*/
    node_t* p_run = NULL; 
    data_t min_data; 
    node_t* min_data_node; 

    if(is_prio_queue_empty(p_prio_queue))
        return PRIO_QUEUE_EMPTY; 
    
    min_data = p_prio_queue->next->data; 
    min_data_node = p_prio_queue->next; 

    for(p_run = p_prio_queue->next; p_run != p_prio_queue; p_run = p_run->next)
        if(p_run->data < min_data)
        {
            min_data = p_run->data; 
            min_data_node = p_run; 
        }

    *p_min_data = min_data; 
    min_data_node->prev->next = min_data_node->next;
    min_data_node->next->prev = min_data_node->prev; 
    free(min_data_node); 

    return (SUCCESS); 
}

status_t max_dequeue(prio_queue_t* p_prio_queue, data_t* p_max_data)
{
    /* Breaking abstraction level*/
    node_t* p_run = NULL; 
    data_t max_data; 
    node_t* max_data_node; 

    if(is_prio_queue_empty(p_prio_queue))
        return PRIO_QUEUE_EMPTY; 
    
    max_data = p_prio_queue->next->data; 
    max_data_node = p_prio_queue->next; 

    for(p_run = p_prio_queue->next; p_run != p_prio_queue; p_run = p_run->next)
        if(p_run->data > max_data)
        {
            max_data = p_run->data; 
            max_data_node = p_run; 
        }

    *p_max_data = max_data; 
    max_data_node->prev->next = max_data_node->next;
    max_data_node->next->prev = max_data_node->prev; 
    free(max_data_node); 

    return (SUCCESS); 
}

status_t is_prio_queue_empty(prio_queue_t* p_prio_queue)
{
    return is_empty(p_prio_queue); 
}

status_t destroy_prio_queue(prio_queue_t** pp_prio_queue)
{
    return destroy_list(pp_prio_queue); 
}
