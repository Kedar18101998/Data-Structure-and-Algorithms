#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define SUCCESS 1 
#define DCDS_INVALID_SET 2 
#define DCDS_DATA_EXISTS 3 
#define DCDS_INVALID_REPR 4 

typedef int data_t; 
typedef struct set set_t; 
typedef struct node node_t; 
typedef node_t list_t; 
typedef list_t dcds_t; 
typedef int status_t; 

struct set 
{
    data_t* arr; 
    size_t N; 
    data_t repr_data; 
}; 

struct node 
{
    set_t* p_set; 
    struct node* prev; 
    struct node* next; 
}; 

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

/* Helper routines -> list */
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end); 
void generic_delete(node_t* p_delete_node); 
node_t* search_node(list_t* p_list, set_t* p_set); 
node_t* get_node(set_t* p_set); 
void* xmalloc(size_t size); 

int main(void) 
{
    status_t status; 
    dcds_t* p_dcds = NULL; 
    data_t data = 0; 
    set_t* p_set = NULL; 

    p_dcds = create_dcds(); 
    for(data = 0; data < 15; ++data)
    {
        status = make_set(p_dcds, data); 
        assert(status == SUCCESS); 
    }
    show_dcds(p_dcds, "INITIAL STATE:"); 
   
    status = union_set(p_dcds, 0, 4); 
    assert(status); 
    show_dcds(p_dcds, "union_set(p_dcds, 0, 4)"); 
    status = union_set(p_dcds, 0, 8); 
    assert(status); 
    show_dcds(p_dcds, "union_set(p_dcds, 0, 8):"); 
    status = union_set(p_dcds, 0, 12); 
    assert(status); 
    show_dcds(p_dcds, "union_set(p_dcds, 0, 12)"); 

    p_set = find_set(p_dcds, 0); 
    show_set(p_set);

    p_set = find_set(p_dcds, 5); 
    show_set(p_set);  
    
    status = destroy_dcds(&p_dcds); 
    assert(status == SUCCESS); 

    exit(EXIT_SUCCESS); 
}


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