#include <stdio.h> 

struct node 
{
    int data; 
    struct node* next; 
}; 

void test_2(void)
{
    struct node* p_start_1 = NULL; 
    /* assume that linked list is populated */
    struct node* run = NULL; 
    struct node* tmp = NULL; 

    run = p_start_1; 
    while(run != NULL)
    {
        tmp = run->next; 
        free(run); 
        run = tmp; 
    } 
}