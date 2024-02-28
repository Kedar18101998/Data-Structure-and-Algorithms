#include "list.h" 
#include "vector.h"

int create_list(void)
{
    list_t* p_list = NULL; 
    ssize_t i; 
    int flag = 0; 
    p_list = get_node(-1); 

    for(i = 0; i < g_handle_table->N; ++i)
    {
        if(g_handle_table->pp_list_ptrs[i] == NULL)
        {
            flag = 1; 
            break; 
        }
    }

    if(flag == 1)
    {
        g_handle_table->pp_list_ptrs[i]=p_list; 
        return (i); 
    }
    else 
    {
        push_back(g_handle_table, p_list); 
        return (g_handle_table->N-1); 
    }
}

int insert_end(int list_handle, int new_data)
{
    list_t* p_list = NULL; 

    assert(list_handle >= 0 && list_handle < g_handle_table->N); 

    p_list = g_handle_table->pp_list_ptrs[list_handle]; 

    // insert at end using p_list 
}