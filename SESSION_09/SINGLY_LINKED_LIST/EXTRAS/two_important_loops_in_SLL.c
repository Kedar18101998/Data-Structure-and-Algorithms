#include <stdio.h> 
#include "list.h"

void find_end(struct node* p_list)
{
    struct node* p_run = NULL; 

    p_run = p_list; 
    while(p_run->next != NULL)
        p_run = p_run->next; 
}

void visit_all_nodes_except_head_node(struct node* p_list)
{
    struct node* p_run = NULL; 

    p_run = p_list->next; 
    while(p_run != NULL)
    {
        // COMMON ACTION ON ALL NODES WITH DATA 
        p_run = p_run->next; 
    }
}