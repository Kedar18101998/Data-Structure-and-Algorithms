#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 

#include "avl.h"

avl_tree_t* create_avl_tree(void)
{
    avl_tree_t* p_tree = NULL; 
    p_tree = xcalloc(1, sizeof(avl_tree_t)); 
    p_tree->p_root_node = NULL; 
    p_tree->nr_elements = 0; 
    return (p_tree); 
}

status_t insert_into_avl_tree(avl_tree_t* p_avl_tree, data_t new_data)
{
    avl_node_t* z = NULL; 
    avl_node_t* x = NULL; 
    avl_node_t* y = NULL; 
    avl_node_t* p_run = NULL; 
    long delta; 
    
    z = get_avl_node(new_data); 
    p_run = p_avl_tree->p_root_node; 
    
    if(p_run == NULL)
    {
        p_avl_tree->p_root_node = z; 
        p_avl_tree->nr_elements += 1; 
        return (SUCCESS); 
    }

    while(1)
    {
        if(new_data < p_run->data) 
        {
            if(p_run->left == NULL)
            {
                p_run->left = z; 
                z->parent = p_run; 
                break; 
            }
            else 
            {
                p_run = p_run->left; 
                continue; 
            }
        }
        else 
        {
            if(p_run->right == NULL)
            {
                p_run->right = z; 
                z->parent = p_run; 
                break; 
            }
            else 
            {
                p_run = p_run->right; 
                continue; 
            }
        }
    }

    x = z; 
    y = x->parent; 
    if(y)
        z = y->parent; 

    while(z != NULL)
    {
        delta = get_balance_of_avl_node(z); 
        if(delta < -1 || delta > 1)
            break; 
        z = z->parent; 
        y = y->parent; 
        x = x->parent;  
    }

    if(z == NULL)
        return (SUCCESS); 

    if(y == z->left && x == y->left)
    {
        right_rotate(p_avl_tree, z); 
    }
    else if(y == z->left && x == y->right)
    {
        left_rotate(p_avl_tree, y); 
        right_rotate(p_avl_tree, z); 
    }
    else if(y == z->right && x == y->left)
    {
        right_rotate(p_avl_tree, y); 
        left_rotate(p_avl_tree, z); 
    }
    else if(y == z->right && x == y->right)
    {
        left_rotate(p_avl_tree, z); 
    }

    return (SUCCESS); 
}

status_t remove_data_from_avl_tree(avl_tree_t* p_avl_tree, data_t r_data)
{
    avl_node_t* z = NULL; 
    avl_node_t* tmp = NULL; 
    avl_node_t* z_successor = NULL; 
    avl_node_t* x = NULL; 
    avl_node_t* y = NULL; 
    unsigned long height_of_left_subtree; 
    unsigned long height_of_right_subtree; 

    z = search_avl_tree_nodelevel(p_avl_tree, r_data); 
    if(z == NULL)
        return (AVL_DATA_NOT_FOUND); 

    if(z->left == NULL)
    {
        transplant(p_avl_tree, z, z->right); 
        tmp = z; 
        z = z->right; 
    }
    else if(z->right == NULL)
    {
        transplant(p_avl_tree, z, z->left); 
        tmp = z; 
        z = z->left; 
    }
    else
    {
        z_successor = get_avl_min_node(z->right); 
        if(z_successor != z->right)
        {
            transplant(p_avl_tree, z_successor, z_successor->right); 
            z_successor->right = z->right; 
            z_successor->right->parent = z_successor; 
        }
        transplant(p_avl_tree, z, z_successor); 
        z_successor->left = z->left; 
        z_successor->left->parent = z_successor; 
        tmp = z; 
        z = z_successor; 
    }
    
    free(tmp);  

    while((z = find_next_imbalanced_node(z)) != NULL)
    {
        height_of_left_subtree = get_height_node_level(z->left); 
        height_of_right_subtree = get_height_node_level(z->right); 
        if(height_of_left_subtree > height_of_right_subtree)
            y = z->left; 
        else 
            y = z->right; 
        if(y)
        {
            height_of_left_subtree = get_height_node_level(y->left); 
            height_of_right_subtree = get_height_node_level(y->right); 
            if(height_of_left_subtree > height_of_right_subtree)
                x = y->left; 
            else 
                x = y->right; 
        }

        if(!(x && y && z))
            break; 

        if(y == z->left && x == y->left)
        {
            right_rotate(p_avl_tree, z); 
        }
        else if(y == z->left && x == y->right)
        {
            left_rotate(p_avl_tree, y); 
            right_rotate(p_avl_tree, z); 
        }
        else if(y == z->right && x == y->left)
        {
            right_rotate(p_avl_tree, y); 
            left_rotate(p_avl_tree, z); 
        }
        else if(y == z->right && x == y->right)
        {
            left_rotate(p_avl_tree, z); 
        }
    }
  
    return (SUCCESS); 
}

bool find_data_in_avl_tree(avl_tree_t* p_avl_tree, data_t f_data)
{
    return (search_avl_tree_nodelevel(p_avl_tree, f_data) != NULL); 
}

void inorder_walk(avl_tree_t* p_avl_tree)
{
    printf("[start]<->"); 
    inorder_walk_nodelevel(p_avl_tree->p_root_node); 
    puts("[end]"); 
}

unsigned long get_height_of_avl_tree(avl_tree_t* p_tree)
{
    return (get_height_node_level(p_tree->p_root_node)); 
}

status_t get_avl_max(avl_tree_t* p_avl_tree, data_t* p_max_data)
{
    avl_node_t* p_avl_node = NULL; 
    if(p_avl_tree->p_root_node == NULL)
        return (AVL_TREE_EMPTY); 
    p_avl_node = get_avl_max_node(p_avl_tree->p_root_node); 
    *p_max_data = p_avl_node->data; 
    return (SUCCESS); 
}

status_t get_avl_min(avl_tree_t* p_avl_tree, data_t* p_min_data)
{
    avl_node_t* p_avl_node = NULL; 
    if(p_avl_tree->p_root_node == NULL)
        return (AVL_TREE_EMPTY); 
    p_avl_node = get_avl_min_node(p_avl_tree->p_root_node); 
    *p_min_data = p_avl_node->data; 
    return (SUCCESS); 
}

/* node level routines */ 

avl_node_t* find_next_imbalanced_node(avl_node_t* p_avl_node)
{
    avl_node_t* u; 
    long delta; 
    if(p_avl_node == NULL)
        return (NULL);
    u = p_avl_node; 
    while(u != NULL)
    {
        delta = get_balance_of_avl_node(u); 
        if(delta < -1 || delta > 1)
            break; 
        u = u -> parent; 
    } 
    return (u); 
}

long get_balance_of_avl_node(avl_node_t* p_avl_node)
{
    if(p_avl_node == NULL)
        return (0); 
    
    return ((long)
            (
            (long)get_height_node_level(p_avl_node->left) - 
            (long)get_height_node_level(p_avl_node->right)
            )
            ); 
}

void left_rotate(avl_tree_t* p_tree, avl_node_t* x)
{
    avl_node_t* y = NULL; 
    
    /* Part 1 */ 
    y = x->right; 
    x->right = y->left; 
    if(y->left != NULL)
        y->left->parent = x; 

    /* Part 2 */ 
    y->parent = x->parent; 
    if(x->parent == NULL)
        p_tree->p_root_node = y; 
    else if(x == x->parent->left)
        x->parent->left = y; 
    else if(x == x->parent->right)
        x->parent->right = y; 

    /* Part 3 */ 
    y->left = x; 
    x->parent = y; 
}

void right_rotate(avl_tree_t* p_tree, avl_node_t* x)
{
   avl_node_t* y = NULL; 
    
    /* Part 1 */ 
    y = x->left; 
    x->left = y->right; 
    if(y->right != NULL)
        y->right->parent = x; 

    /* Part 2 */ 
    y->parent = x->parent; 
    if(x->parent == NULL)
        p_tree->p_root_node = y; 
    else if(x == x->parent->left)
        x->parent->left = y; 
    else if(x == x->parent->right)
        x->parent->right = y; 
    
    /* Part 3 */ 
    y->right = x; 
    x->parent = y; 
}

avl_node_t* search_avl_tree_nodelevel(avl_tree_t* p_avl_tree, data_t search_data)
{
    avl_node_t* p_run = NULL; 
    p_run = p_avl_tree->p_root_node; 
    while(p_run != NULL)
    {
        if(search_data == p_run->data)
            break; 
        else if(search_data < p_run->data)
            p_run = p_run->left; 
        else if(search_data > p_run->data)
            p_run = p_run->right; 
    }

    return (p_run); 
}

void transplant(avl_tree_t* p_avl_tree, avl_node_t* u, avl_node_t* v)
{
    if(u->parent == NULL)
        p_avl_tree->p_root_node = v; 
    else if(u == u->parent->left)
        u->parent->left = v; 
    else if(u == u->parent->right)
        u->parent->right = v; 
    if(v)
        v->parent = u->parent; 
}

unsigned long get_height_node_level(avl_node_t* p_avl_node)
{
    if(p_avl_node == NULL)
        return (0); 
    return (cpa_max(    
                get_height_node_level(p_avl_node->left), 
                get_height_node_level(p_avl_node->right)
                ) 
                + 1
            );
}

void inorder_walk_nodelevel(avl_node_t* p_avl_node)
{
    if(p_avl_node != NULL)
    {
        inorder_walk_nodelevel(p_avl_node->left); 
        printf("[%d]<->", p_avl_node->data); 
        inorder_walk_nodelevel(p_avl_node->right); 
    }
}

avl_node_t* get_avl_min_node(avl_node_t* p_avl_node)
{
    avl_node_t* u = p_avl_node; 
    while(u->left != NULL)
        u = u->left; 
    return (u); 
}

avl_node_t* get_avl_max_node(avl_node_t* p_avl_node)
{
    avl_node_t* u = p_avl_node; 
    while(u->right != NULL)
        u = u->right; 
    return (u); 
}

avl_node_t* get_avl_node(data_t new_data)
{
    avl_node_t* p_node = NULL; 

    p_node = (avl_node_t*)xcalloc(1, sizeof(avl_node_t)); 
    p_node->data = new_data; 
    p_node->left = NULL; 
    p_node->right = NULL; 
    p_node->parent = NULL; 
    return (p_node); 
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    assert(p); 
    return (p); 
}

unsigned long cpa_max(unsigned long a, unsigned long b)
{
    if(a > b)
        return (a); 
    return (b); 
}
