#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include <time.h> 

#include "avl.h"

#define CAP 1000000
#define NR_NODES 50000

data_t arr[NR_NODES]; 

int main(void)
{
    avl_tree_t* p_avl_tree = NULL; 
    int i; 
    status_t status; 

    for(i = 0; i < NR_NODES; ++i)
        arr[i] = rand() % CAP;

    p_avl_tree = create_avl_tree(); 
    for(i = 0; i < NR_NODES; ++i)
    {
        status = insert_into_avl_tree(p_avl_tree, arr[i]); 
        assert(status == SUCCESS); 
    } 

    inorder_walk(p_avl_tree); 
    printf("NR_NODES=%d\tH=%lu\n", NR_NODES, get_height_of_avl_tree(p_avl_tree)); 

    for(i = 0; i < NR_NODES; ++i)
    {
        status = remove_data_from_avl_tree(p_avl_tree, arr[i]); 
        assert(status == SUCCESS); 
        printf("%d:deleted node=%d:H=%d\n", i, arr[i], get_height_of_avl_tree(p_avl_tree)); 
        puts("------------------------------------------------------------------------"); 
    }

    exit(0); 
}

