#include "list.h"
#include "prio.h"

status_t enqueue(prio_queue_t* p_prio_queue, data_t new_data)
{
    node_t* p_run; 
    node_t* p_new_node; 

    if(is_prio_queue_empty(p_prio_queue))
        return insert_start(p_prio_queue, new_data); 

    if(p_prio_queue->next->next == p_prio_queue)
    {
        if(new_data <= p_prio_queue->next->data)
            return insert_start(p_prio_queue, new_data); 
        else 
            return insert_end(p_prio_queue, new_data); 
    }


    for(p_run = p_prio_queue->next; p_run->next != p_prio_queue; p_run = p_run->next)
    {
        if(new_data > p_run->data && new_data <= p_run->next->data)
        {
            p_new_node = get_node(new_data); 
            p_new_node->next = p_run->next; 
            p_new_node->prev = p_run; 
            p_run->next->prev = p_new_node; 
            p_run->next = p_new_node; 
            return (SUCCESS); 
        }
    }

    return insert_end(p_prio_queue, new_data); 
}

status_t enqueue_1(prio_queue_t* p_prio_queue, data_t new_data)
{
    node_t* p_run; 
    node_t* p_new_node; 

    for(p_run = p_prio_queue->prev; p_run != p_prio_queue; p_run = p_run->prev)
        if(new_data < p_run->data)
            break; 
    
    p_new_node = get_node(new_data); 
    p_new_node->prev = p_run->prev; 
    p_new_node->next = p_run; 
    p_run->prev->next = p_new_node; 
    p_run->prev = p_new_node; 

    return (SUCCESS); 
}