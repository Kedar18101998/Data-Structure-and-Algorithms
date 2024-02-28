#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <time.h> 
#include "rbtree.h"

data_t arr[500]; 

int main(void)
{
    rbtree_t* p_rb = NULL; 
    status_t status; 
    int i; 
    srand(time(0)); 
    for(i = 0; i < 500; ++i)
        arr[i] = rand(); 

    p_rb = create_rbtree(); 

    for(i = 0; i < 500; ++i)
        assert(insert_into_rbtree(p_rb, arr[i]) == SUCCESS); 
    printf("H = %d\n", get_rb_height(p_rb)); 
    inorder_walk(p_rb);  
  
    for(i = 0; i < 500; i = i + 1)
    {   
        status = remove_from_rbtree(p_rb, arr[i]); 
        assert(status == SUCCESS); 
        printf("%d:Removed data:%d\n", i, arr[i]); 
        printf("Remaining nodes = %d, H = %d\n", 500 - (i+1),  get_rb_height(p_rb)); 
    }
   
    status = destroy_rbtree(&p_rb); 
    assert(status == SUCCESS && p_rb == NULL); 

    exit(EXIT_SUCCESS);
}