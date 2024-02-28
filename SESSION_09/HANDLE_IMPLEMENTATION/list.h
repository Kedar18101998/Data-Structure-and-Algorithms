#ifndef _LIST_H 
#define _LIST_H 

typedef int data_t; 
typedef struct node node_t; 
typedef node_t list_t; 

#define NULL ((void*)0)

struct node
{
    data_t data; 
    struct node* next; 
}; 

int create_list(void); 
int insert_end(int list_handle, int new_data); 


node_t* get_node(data_t new_data); 


#endif 