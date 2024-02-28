#include <stdio.h> 
#include <stdlib.h> 
#include <setjmp.h> 

#define BAD_ALLOC       1

struct node{
    int data; 
    struct node* prev; 
    struct node* next; 
}; 

void* xmalloc(size_t); 
struct node* get_node(int data); 

jmp_buf getnode_buffer; 
jmp_buf main_buffer; 

int main(void){
    int ret; 
    struct node* p_new_node = NULL; 
    int flag = 0; 
    while(1){
        ret = setjmp(main_buffer); 
        if(ret == BAD_ALLOC)
        {
            flag = 1; 
            break; 
        }
        p_new_node = get_node(0); 
    }
    if(flag == 1)
        puts("out of virtual memory. BYE"); 

    exit(EXIT_SUCCESS); 
    
}

struct node* get_node(int data){
    struct node* p_new_node = NULL; 
    int ret; 

    ret = setjmp(getnode_buffer); 
    if(ret == BAD_ALLOC)
        longjmp(main_buffer, BAD_ALLOC); 

    p_new_node = (struct node*)xmalloc(0xfffffffff); 
    p_new_node->data = data; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 

    return (p_new_node);    

}

void* xmalloc(size_t number_of_bytes){
    void* p = NULL; 

    p = malloc(number_of_bytes);  
    if(p == NULL)
        longjmp(getnode_buffer, BAD_ALLOC); 

    return (p); 
}

/* The Linux Programming Interface : 6*/
/* Advanced Programming Under Unix Environment */