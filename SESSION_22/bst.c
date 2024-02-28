#include <stdio.h> 
#include <stdlib.h> 
#include "bst.h"

bst_t* create_bst(void)
{
    return (bst_t*)xcalloc(1, sizeof(bst_t)); 
}

status_t insert_bst(bst_t* p_bst, data_t new_data)
{
    bst_node_t* p_new_node = NULL; 
    bst_node_t* p_run = NULL; 

    p_new_node = get_bst_node(new_data); 
    if(p_bst->root_node == NULL)
    {
        /* Insert in empty BST */
        p_bst->root_node = p_new_node; 
        p_bst->nr_elements += 1; 
        return (SUCCESS); 
    }

    /* Insert in non-empty BST */
    p_run = p_bst->root_node; 
    while(TRUE)
    {
        if(new_data <= p_run->data)
        {
            if(p_run->left == NULL)            
                break; 
            p_run = p_run->left; 
        }
        else 
        {
            if(p_run->right == NULL)     
                break;  
            p_run = p_run->right; 
        }
    }

    if(new_data <= p_run->data)
        p_run->left = p_new_node; 
    else 
        p_run->right = p_new_node; 
    p_new_node->parent = p_run; 
    p_bst->nr_elements += 1; 

    return (SUCCESS); 
}

Bool search_bst(bst_t* p_bst, data_t s_data)
{
    bst_node_t* p_node = NULL; 

    p_node = search_node(p_bst->root_node, s_data); 
    return (p_node != NULL); 
}

height_t height_bst(bst_t* p_bst)
{
    return (height_bst_nodelevel(p_bst->root_node));
}

status_t max_bst(bst_t* p_bst, data_t* p_max_element)
{
    bst_node_t* p_max_node = NULL; 

    if(p_bst->root_node == NULL)
        return (BST_EMPTY); 

    p_max_node = max_bst_nodelevel(p_bst->root_node); 
    *p_max_element = p_max_node->data; 

    return (SUCCESS);     
} 

status_t min_bst(bst_t* p_bst, data_t* p_min_element)
{
    bst_node_t* p_min_node = NULL; 

    if(p_bst->root_node == NULL)
        return (BST_EMPTY); 

    p_min_node = min_bst_nodelevel(p_bst->root_node); 
    *p_min_element = p_min_node->data; 

    return (SUCCESS); 
}

status_t inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data)
{
    bst_node_t* e_node = NULL; 
    bst_node_t* p_succ_node = NULL; 

    e_node = search_node(p_bst->root_node, e_data); 
    if(!e_node)
        return (BST_DATA_NOT_FOUND); 

    p_succ_node = inorder_successor_nodelevel(e_node); 
    if(!p_succ_node)
        return (BST_NO_SUCCESSOR); 

    *p_succ_data = p_succ_node->data; 
    return (SUCCESS); 
}

status_t inorder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pred_data)
{
    bst_node_t* e_node = NULL; 
    bst_node_t* p_pred_node = NULL; 

    e_node = search_node(p_bst->root_node, e_data); 
    if(!e_node)
        return (BST_DATA_NOT_FOUND); 

    p_pred_node = inorder_predecessor_nodelevel(e_node); 
    if(!p_pred_node)
        return (BST_NO_PREDECESSOR); 

    *p_pred_data = p_pred_node->data; 
    return (SUCCESS);   
}

void preorder_traversal(bst_t* p_bst)
{
    printf("[BEGIN]<->"); 
    preorder_traversal_nodelevel(p_bst->root_node); 
    puts("[END]"); 
}

void inorder_traversal(bst_t* p_bst)
{
    printf("[BEGIN]<->"); 
    inorder_traversal_nodelevel(p_bst->root_node); 
    puts("[END]"); 
}

void postorder_traversal(bst_t* p_bst)
{
    printf("[BEGIN]<->"); 
    postorder_traversal_nodelevel(p_bst->root_node); 
    puts("[END]"); 
}

status_t remove_bst_expanded(bst_t* p_bst, data_t r_data)
{
    bst_node_t* z = NULL; 
    bst_node_t* z_succ = NULL; 

    z = search_node(p_bst->root_node, r_data); 
    if(z == NULL)
        return (BST_DATA_NOT_FOUND); 

    if(z->left == NULL)
    {
        if(z->parent == NULL)
            p_bst->root_node = z->right; 
        else if(z == z->parent->left)
            z->parent->left = z->right; 
        else 
            z->parent->right = z->right; 
        if(z->right)
            z->right->parent = z->parent; 
    }
    else if(z->right == NULL)
    {
        if(z->parent == NULL)
            p_bst->root_node = z->left; 
        else if(z == z->parent->left)
            z->parent->left = z->left; 
        else 
            z->parent->right = z->left; 
        z->left->parent = z->parent; 
    }
    else 
    {
        z_succ = inorder_successor_nodelevel(z); 
        if(z->right != z_succ)
        {
            z_succ->parent->left = z_succ->right; 
            if(z_succ->right)
                z_succ->right->parent = z_succ->parent; 
            
            z_succ->right = z->right; 
            z_succ->right->parent = z_succ; 
        }

        if(z->parent == NULL)
            p_bst->root_node = z_succ; 
        else if(z == z->parent->left)
            z->parent->left = z_succ; 
        else 
            z->parent->right = z_succ; 
        z_succ->parent = z->parent; 

        z_succ->left = z->left; 
        z_succ->left->parent = z_succ; 
    }

    free(z); 
    z = NULL; 
    p_bst->nr_elements -= 1; 

    return (SUCCESS); 
}

status_t remove_bst(bst_t* p_bst, data_t r_data)
{
    bst_node_t* z = NULL; 
    bst_node_t* z_succ = NULL; 

    z = search_node(p_bst->root_node, r_data); 
    if(z == NULL)
        return (BST_DATA_NOT_FOUND); 

    if(z->left == NULL)
        transplant(p_bst, z, z->right); 
    else if(z->right == NULL)
        transplant(p_bst, z, z->left); 
    else 
    {
        z_succ = inorder_successor_nodelevel(z); 
        if(z->right != z_succ)
        {
            transplant(p_bst, z_succ, z_succ->right); 
            z_succ->right = z->right; 
            z_succ->right->parent = z_succ; 
        }

        transplant(p_bst, z, z_succ); 
        z_succ->left = z->left; 
        z_succ->left->parent = z_succ; 
    }

    free(z); 
    z = NULL; 
    p_bst->nr_elements -= 1; 

    return (SUCCESS); 
}

status_t destroy_bst(bst_t** pp_bst)
{
    bst_t* p_bst = *pp_bst; 
    // Destruction logic 
    destroy_bst_nodelevel(p_bst->root_node); 
    free(p_bst); 
    p_bst = NULL; 
    *pp_bst = NULL; 
    return (SUCCESS); 
}

/* Auxillary routines */

void transplant(bst_t* p_bst, bst_node_t* u, bst_node_t* v)
{
    if(u->parent == NULL)
        p_bst->root_node = v; 
    else if(u->parent->left == v)
        u->parent->left = v; 
    else 
        u->parent->right = v; 

    if(v)
        v->parent = u->parent; 
}

bst_node_t* inorder_successor_nodelevel(bst_node_t* p_node)
{
    bst_node_t* x, *y; 

    if(p_node->right != NULL)
    {
        y = min_bst_nodelevel(p_node->right); 
        return (y);
    }

    x = p_node; 
    y = x->parent; 

    while(y && x == y->right)
    {
        x = y; 
        y = x->parent; 
    }

    return (y); 
}

bst_node_t* inorder_predecessor_nodelevel(bst_node_t* p_node)
{
    bst_node_t* x, *y; 

    if(p_node->left != NULL)
    {
        y = max_bst_nodelevel(p_node->left); 
        return (y);
    }

    x = p_node; 
    y = x->parent; 

    while(y && x == y->left)
    {
        x = y; 
        y = x->parent; 
    }

    return (y); 
}

bst_node_t* max_bst_nodelevel(bst_node_t* root_node)
{
    if(root_node == NULL)
        return (root_node); 
    
    while(root_node->right != NULL)
        root_node = root_node->right; 

    return (root_node); 
}

bst_node_t* min_bst_nodelevel(bst_node_t* root_node)
{
    if(root_node == NULL)
        return (root_node); 

    while(root_node->left == NULL)
        root_node = root_node->left; 

    return (root_node); 
}

height_t height_bst_nodelevel(bst_node_t* root_node)
{
    height_t h_lst, h_rst, h_max; 

    if(root_node == NULL)
        return (0); 

    h_lst = height_bst_nodelevel(root_node->left); 
    h_rst = height_bst_nodelevel(root_node->right); 
    h_max = (h_lst > h_rst) ? (h_lst) : (h_rst); 
    return (h_max + 1); 
}

void destroy_bst_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        destroy_bst_nodelevel(root_node->left); 
        destroy_bst_nodelevel(root_node->right); 
        free(root_node); 
    }
}

void preorder_traversal_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        printf("[%d]<->", root_node->data); 
        preorder_traversal_nodelevel(root_node->left); 
        preorder_traversal_nodelevel(root_node->right); 
    }
}

void inorder_traversal_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        inorder_traversal_nodelevel(root_node->left); 
        printf("[%d]<->", root_node->data); 
        inorder_traversal_nodelevel(root_node->right); 
    }
}

void postorder_traversal_nodelevel(bst_node_t* root_node)
{
    if(root_node != NULL)
    {
        postorder_traversal_nodelevel(root_node->left); 
        postorder_traversal_nodelevel(root_node->right); 
        printf("[%d]<->", root_node->data); 
    }
}

bst_node_t* search_node(bst_node_t* root_node, data_t s_data)
{
    bst_node_t* p_run = NULL; 

    p_run = root_node; 
    while(p_run != NULL)
    {
        if(s_data == p_run->data)
            break; 
        else if(s_data < p_run->data)
            p_run = p_run->left; 
        else 
            p_run = p_run->right; 
    }

    return (p_run); 
}

bst_node_t* get_bst_node(data_t new_data)
{
    bst_node_t* p_node = NULL; 

    p_node = (bst_node_t*)xcalloc(1, sizeof(bst_node_t)); 
    p_node->data = new_data; 
    
    return (p_node); 
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    if(NULL == p)
    {
        fprintf(stderr, "calloc:fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}