#include <stdio.h> 
#include <stdlib.h> 
#include "rbtree.h"

rb_tree_t* create_rb_tree(void)
{
    rb_tree_t* p_tree = NULL; 

    p_tree = (rb_tree_t*)xcalloc(1, sizeof(rb_tree_t)); 
    p_tree->root_node = NULL; 
    p_tree->nr_elements = 0; 
    p_tree->nil = (rb_node_t*)xcalloc(1, sizeof(rb_node_t)); 
    p_tree->nil->data = -1; 
    p_tree->nil->color = BLACK; 
    p_tree->nil->left = NULL; 
    p_tree->nil->right = NULL; 
    p_tree->nil->parent = NULL; 

    return (p_tree); 
} 

rb_node_t* get_node(rb_tree_t* p_rb_tree, data_t new_data)
{
    rb_node_t* p_new_node = NULL; 

    p_new_node = (rb_node_t*)xcalloc(1, sizeof(rb_node_t)); 
    p_new_node->data = new_data; 
    p_new_node->color = RED; 
    p_new_node->left = p_rb_tree->nil; 
    p_new_node->right = p_rb_tree->nil; 
    p_new_node->parent = p_rb_tree->nil; 

    return (p_new_node); 
}

void* xcalloc(size_t number_of_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(number_of_elements, size_per_element); 
    if(p == NULL)
    {
        fprintf(stderr, "Error in allocating memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}