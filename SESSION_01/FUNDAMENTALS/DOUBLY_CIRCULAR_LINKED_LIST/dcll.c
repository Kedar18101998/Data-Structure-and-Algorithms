/* Doubly Circular Linked List */ 

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

/* Symbolic constants */ 

#define TRUE 1
#define FALSE 0 
#define SUCCESS 1 
#define FAILURE 0 
#define LIST_DATA_NOT_FOUND 2 
#define LIST_EMPTY 3 

/* typedefs */ 
typedef int data_t; 
typedef int status_t; 
typedef int len_t; 
typedef int bool; 
typedef struct node node_t; 
typedef node_t list_t; 

// typedef enum {FALSE=0, TRUE} bool; 

/* node layout definition */ 
struct node{
    data_t data; 
    struct node *prev; 
    struct node *next; 
}; 

/* interface routines declarations */ 
list_t *create_list(void); 

status_t insert_beg(list_t *p_list, data_t new_data); 
status_t insert_end(list_t *p_list, data_t new_data); 
status_t insert_after(list_t *p_list, data_t e_data, data_t new_data); 
status_t insert_before(list_t *p_list, data_t e_data, data_t new_data); 

status_t get_beg(list_t *p_list, data_t *p_data); 
status_t get_end(list_t *p_list, data_t *p_data); 
status_t pop_beg(list_t *p_list, data_t *p_data); 
status_t pop_end(list_t *p_list, data_t *p_data); 

status_t remove_beg(list_t *p_list); 
status_t remove_end(list_t *p_list); 
status_t remove_data(list_t *p_list, data_t r_data); 

len_t get_length(list_t *p_list); 
bool contains(list_t *p_list, data_t search_data); 
bool is_list_empty(list_t *p_list); 
int get_repeat_count(list_t *p_list, data_t search_data); 
void show_list(list_t *p_list, const char *msg); 

list_t *concat_lists(list_t *p_list1, list_t *p_list2); 
// status_t concat_lists_1(list_t* p_list1, list_t* p_list2, list_t** pp_concat_list); 
list_t *merge_lists(list_t *p_list1, list_t *p_list2); 
// status_t concat_lists_2(list_t* p_list1, list_t* p_list2, list_t** pp_list); 
list_t *get_reversed_list(list_t *p_list); 
// status_t get_reversed_list(list_t* p_list, list_t** pp_reversed_list); 

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size); 
list_t *array_to_list(data_t *p_array, size_t size); 
 
status_t append_list(list_t *p_list1, list_t *p_list2); 
status_t reverse_list(list_t *p_list); 
status_t destroy_list(list_t **pp_list); 

/* list auxillary routines */ 
void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end); 
void generic_delete(node_t *p_delete_node); 
node_t *locate_node(list_t *p_list, data_t search_data); 
node_t *get_list_node(data_t new_data); 

/* memory allocation routines */ 

void *xmalloc(size_t size_in_bytes); 

int main(void){
    status_t s; 
    data_t data; 
    len_t len; 
    list_t *p_list = NULL;
    list_t *p_list1 = NULL, *p_list2 = NULL;  
    list_t *p_concat_list = NULL; 
    list_t *p_merge_list = NULL; 
    list_t *p_reversed_list = NULL; 

    p_list = create_list(); 

    assert(get_beg(p_list, &data) == LIST_EMPTY); 
    assert(get_end(p_list, &data) == LIST_EMPTY); 
    assert(pop_beg(p_list, &data) == LIST_EMPTY); 
    assert(pop_end(p_list, &data) == LIST_EMPTY); 
    assert(remove_beg(p_list) == LIST_EMPTY); 
    assert(remove_end(p_list) == LIST_EMPTY); 
    assert(remove_data(p_list, 0) == LIST_DATA_NOT_FOUND); 
    assert(get_length(p_list) == 0); 

    show_list(p_list, "After create_list():"); 
    for(data = 0; data < 5; data++)
    {
        s = insert_beg(p_list, data); 
        assert(s == SUCCESS); 
    }
    show_list(p_list, "After insert_beg())"); 

    for(data = 5; data < 10; data++)
    {
        s = insert_end(p_list, data); 
        assert(s == SUCCESS); 
    }
    show_list(p_list, "After insert_end():"); 

    s = insert_after(p_list, 0, 100); 
    assert(s == SUCCESS); 
    show_list(p_list, "After insert_after():"); 

    s = insert_before(p_list, 0, 200); 
    assert(s == SUCCESS); 
    show_list(p_list, "After insert_before():"); 

    data = 0; 
    s = get_beg(p_list, &data); 
    assert(s == SUCCESS); 
    printf("Beginning data:%d\n", data); 
    data = 0; 
    s = get_end(p_list, &data); 
    assert(s == SUCCESS); 
    printf("End data:%d\n", data); 
    show_list(p_list, "After get_beg() and get_end():"); 

    data = 0; 
    s = pop_beg(p_list, &data); 
    assert(s == SUCCESS); 
    printf("poped beg data:%d\n", data); 
    show_list(p_list, "After pop_beg():"); 
    data = 0; 
    s = pop_end(p_list, &data); 
    assert(s == SUCCESS); 
    printf("poped end data:%d\n", data); 
    show_list(p_list, "After pop_end():"); 

    s = remove_beg(p_list); 
    assert(s == SUCCESS); 
    show_list(p_list, "After remove_beg():"); 
    s = remove_end(p_list); 
    assert(s == SUCCESS); 
    show_list(p_list, "After remove_end():"); 
    s = remove_data(p_list, 0); 
    assert(s == SUCCESS);
    show_list(p_list, "After remove_data():"); 

    printf("get_length(p_list):%d\n", get_length(p_list)); 
    if(contains(p_list, 200) == TRUE)
    {
        puts("200 is in list"); 
    }
    if(contains(p_list, -5) == FALSE)
    {
        puts("-5 is not in list"); 
    }

    printf("get_repeat_count(p_list, 4):%d\n", get_repeat_count(p_list, 4)); 
    printf("get_repeat_count(p_list, 200):%d\n", get_repeat_count(p_list, 200)); 
    assert(insert_end(p_list, 100) == SUCCESS); 
    printf("get_repeat_count(p_list, 100):%d\n", get_repeat_count(p_list, 100)); 
    
    s = destroy_list(&p_list); 
    assert(s == SUCCESS && p_list == NULL); 

    p_list1 = create_list(); 
    p_list2 = create_list(); 

    for(data = 5; data <= 95; data += 10)
    {
        insert_end(p_list1, data); 
        insert_end(p_list2, data+5); 
    }

    show_list(p_list1, "List1:"); 
    show_list(p_list2, "List2:"); 

    p_concat_list = concat_lists(p_list1, p_list2); 
    show_list(p_concat_list, "Concatenated version of List1 and List2:"); 
    
    p_merge_list = merge_lists(p_list1, p_list2); 
    show_list(p_merge_list, "Merged version of List1 and List2:"); 

    p_reversed_list = get_reversed_list(p_list1); 
    show_list(p_list1, "List1:"); 
    show_list(p_reversed_list, "Reversed version of List1:"); 

    show_list(p_list2, "List2 before undergoing reversal:");
    s = reverse_list(p_list2); 
    assert(s == SUCCESS); 
    show_list(p_list2, "Reversed List2:"); 

    s = append_list(p_list1, p_list2); 
    assert(s == SUCCESS); 
    show_list(p_list1, "List2 is appended behind list1:"); 
    
    s = destroy_list(&p_list1); 
    assert(s == SUCCESS && p_list1 == NULL); 

    s = destroy_list(&p_concat_list); 
    assert(s == SUCCESS && p_concat_list == NULL); 

    s = destroy_list(&p_merge_list); 
    assert(s == SUCCESS && p_merge_list == NULL); 

    s = destroy_list(&p_reversed_list); 
    assert(s == SUCCESS && p_reversed_list == NULL); 

    // #TODO : add test routines for list_to_array() and array_to_list()

    return (EXIT_SUCCESS); 
}

list_t *create_list(void)
{
    node_t *p_new_node = NULL; 
    p_new_node = get_list_node(0); 
    p_new_node->next = p_new_node; 
    p_new_node->prev = p_new_node; 
    return (p_new_node); 
}

status_t insert_beg(list_t *p_list, data_t new_data)
{
    generic_insert(p_list, get_list_node(new_data), p_list->next); 
    return (SUCCESS); 
}

status_t insert_end(list_t *p_list, data_t new_data)
{
    generic_insert(p_list->prev, get_list_node(new_data), p_list); 
    return (SUCCESS); 
}

status_t insert_after(list_t *p_list, data_t e_data, data_t new_data)
{
    node_t *pe_node = locate_node(p_list, e_data); 
    if(pe_node == NULL)
    {
        return (LIST_DATA_NOT_FOUND); 
    }
    generic_insert(pe_node, get_list_node(new_data), pe_node->next); 
    return (SUCCESS); 
}

status_t insert_before(list_t *p_list, data_t e_data, data_t new_data)
{
    node_t *pe_node = locate_node(p_list, e_data); 
    if(pe_node == NULL)
    {
        return (LIST_DATA_NOT_FOUND); 
    }
    generic_insert(pe_node->prev, get_list_node(new_data), pe_node); 
    return (SUCCESS); 
}

status_t get_beg(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *p_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(list_t *p_list, data_t *p_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *p_data = p_list->prev->data; 
    return (SUCCESS); 
}

status_t pop_beg(list_t *p_list, data_t *pp_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *pp_data = p_list->next->data; 
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

status_t pop_end(list_t *p_list, data_t *pp_data)
{
    if(is_list_empty(p_list) == TRUE)
    {
        return (LIST_EMPTY); 
    }
    *pp_data = p_list->prev->data; 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

status_t remove_beg(list_t *p_list)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY); 
    }
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

status_t remove_end(list_t *p_list)
{
    if(is_list_empty(p_list))
    {
        return (LIST_EMPTY); 
    }
    generic_delete(p_list->prev); 
    return (SUCCESS);
}

status_t remove_data(list_t *p_list, data_t r_data)
{
    node_t *pe_node = locate_node(p_list, r_data); 
    if(pe_node == NULL)
    {
        return (LIST_DATA_NOT_FOUND); 
    }
    generic_delete(pe_node); 
    return (SUCCESS); 
}

len_t get_length(list_t *p_list)
{
    node_t *p_run; 
    len_t len; 
    for(p_run = p_list->next, len = 0; p_run != p_list; p_run = p_run->next, ++len)
    {
    }
    return (len); 
}

bool contains(list_t *p_list, data_t search_data)
{
    return (locate_node(p_list, search_data) != NULL);
}

bool is_list_empty(list_t *p_list)
{
    return (p_list->next == p_list && p_list->prev == p_list); 
}

int get_repeat_count(list_t *p_list, data_t search_data)
{
    int count = 0; 
    list_t *p_run; 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        if(p_run->data == search_data)
        {
            ++count; 
        } 
    }
    return (count); 
}

void show_list(list_t *p_list, const char *msg)
{
    node_t *p_run; 
    if(msg)
    {
        puts(msg); 
    }
    printf("[BEG]<->"); 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        printf("[%d]<->", p_run->data); 
    }
    puts("[END]"); 
}

list_t *concat_lists(list_t *p_list1, list_t *p_list2)
{
    list_t *p_new_list = create_list(); 
    node_t *p_run; 
    for(p_run = p_list1->next; p_run != p_list1; p_run = p_run->next)
    {
        insert_end(p_new_list, p_run->data); 
    }
    for(p_run = p_list2->next; p_run != p_list2; p_run = p_run->next)
    {
        insert_end(p_new_list, p_run->data); 
    }
    return (p_new_list); 
}

list_t *merge_lists(list_t *p_list1, list_t *p_list2){
    list_t *p_merge_list = create_list(); 
    node_t *p_run1 = p_list1->next, *p_run2 = p_list2->next; 
    
    while(TRUE)
    {
        if(p_run1 == p_list1)
        {
            while(p_run2 != p_list2)
            {
                insert_end(p_merge_list, p_run2->data); 
                p_run2 = p_run2->next; 
            }
            break; 
        }
        if(p_run2 == p_list2)
        {
            while(p_run1 != p_list1)
            {
                insert_end(p_merge_list, p_run1->data); 
                p_run1 = p_run1->next; 
            }
            break; 
        }
        if(p_run1->data <= p_run2->data)
        {
            insert_end(p_merge_list, p_run1->data); 
            p_run1 = p_run1->next; 
        }
        else
        {
            insert_end(p_merge_list, p_run2->data); 
            p_run2 = p_run2->next; 
        }
    }
    return (p_merge_list); 
}

list_t *get_reversed_list(list_t *p_list)
{
    list_t *p_reversed_list = create_list(); 
    node_t *p_run; 
    p_run = p_list->prev; 
    while(p_run != p_list)
    {
        insert_end(p_reversed_list, p_run->data); 
        p_run = p_run->prev; 
    }
    return (p_reversed_list); 
}

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size){
    data_t *p_array; 
    len_t list_len; 
    node_t *p_run; 
    int i; 
    list_len = get_length(p_list); 
    p_array = (data_t*)xmalloc(list_len * sizeof(data_t)); 
    for(p_run = p_list->next, i = 0; p_run != p_list; p_run = p_run->next, ++i)
    {
        p_array[i] = p_run->data; 
    }
    *pp_array = p_array; 
    *p_size = list_len; 
    return (SUCCESS); 
}

list_t *array_to_list(data_t *p_array, size_t size)
{
    list_t *p_new_list = create_list(); 
    int i; 
    for(i = 0; i < size; ++i)
    {
        insert_end(p_new_list, p_array[i]); 
    }
    return (p_new_list); 
}

status_t append_list(list_t *p_list1, list_t *p_list2)
{
    p_list1->prev->next = p_list2->next; 
    p_list2->next->prev = p_list1->prev;
    p_list1->prev = p_list2->prev; 
    p_list2->prev->next = p_list1; 
    free(p_list2);  
    return (SUCCESS); 
}

status_t reverse_list(list_t *p_list)
{
    node_t *p_run, *p_run_prev, *p_prev_orig;
    p_prev_orig = p_list->prev;  
    for(p_run = p_list->prev->prev; p_run != p_list; p_run = p_run_prev)
    {
        p_run_prev = p_run->prev; 
        generic_insert(p_list->prev, p_run, p_list); 
    }
    p_prev_orig->prev = p_list; 
    p_list->next = p_prev_orig; 
    return (SUCCESS); 
}

status_t destroy_list(list_t **pp_list)
{
    list_t *p_list = *pp_list; 
    node_t *p_run, *p_run_next; 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run_next)
    {
        p_run_next = p_run->next; 
        free(p_run); 
    }
    free(p_list); 
    *pp_list = NULL; 
    return (SUCCESS); 
}

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void generic_delete(node_t *p_delete_node)
{
    p_delete_node->next->prev = p_delete_node->prev; 
    p_delete_node->prev->next = p_delete_node->next; 
    free(p_delete_node); 
}

node_t *locate_node(list_t *p_list, data_t search_data)
{
    node_t *p_run; 
    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
    {
        if(p_run->data == search_data)
        {
            return (p_run); 
        }
    }
    return (NULL); 
}

node_t *get_list_node(data_t new_data)
{
    node_t *p_new_node = NULL; 
    p_new_node = (node_t*)xmalloc(sizeof(node_t)); 
    p_new_node->data = new_data; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 
    return (p_new_node); 
}

void *xmalloc(size_t size_in_bytes)
{
    void *p = NULL; 
    p = malloc(size_in_bytes); 
    assert(p != NULL); 
    return (p); 
}
