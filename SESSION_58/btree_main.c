#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 
#include "btree.h"

int main(void)
{
    status_t status; 
    btree_t* btree = NULL; 
    int data[] = {100, 500, 200, 300, 400, 600, 113, 654, 373, 217, 
                    1000, 341, 564, 8765, 32, 6434, 76434, 5343, 32}; 
    int i; 
    /*
    btree = create_btree(3); 
    if(btree == NULL)
    {
        fprintf(stderr, "Failed to create B-Tree\n"); 
        exit(EXIT_FAILURE); 
    }

    for(i = 0; i < sizeof(data)/sizeof(data[i]); ++i){
        status = insert_btree(btree, data[i]); 
        if(status != SUCCESS){
            fprintf(stderr, "Insert not successful\n"); 
            exit(EXIT_SUCCESS); 
        }
    }

    inorder_btree(btree); 
    */

    test_btree_split_child(); 

    exit(EXIT_SUCCESS); 
}