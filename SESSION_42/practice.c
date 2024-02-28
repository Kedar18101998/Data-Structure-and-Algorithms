#include "rbtree.h"

void left_rotate(rbtree_t* p_tree, rbnode_t* x)
{
    /* 
        PRECONDITION: x->right != p_tree->nil
    */
   rbnode_t* y = NULL; 

   y = x->right; 
   x->right = y->left; 
   if(y->left != p_tree->nil) 
        y->left->parent = x; 

    y->parent = x->parent; 
    if(x->parent == p_tree->nil)
        p_tree->root_node = y; 
    else if(x == x->parent->left)
        x->parent->left = y; 
    else if(x == x->parent->right)
        x->parent->right = y; 

    y->left = x; 
    x->parent = y; 
}

/* PRECONDITION : x->left != p_tree->nil */
void right_rotate(rbtree_t* p_tree, rbnode_t* x)
{
    rbnode_t* y = NULL; 

    y = x->left; 
    x->left = y->right; 
    if(y->right != p_tree->nil)
        y->right->parent = x; 

    y->parent = x->parent; 
    if(x->parent == p_tree->nil)
        p_tree->root_node = y; 
    else if(x->parent->left == x)
        x->parent->left = y; 
    else if(x->parent->right == x)
        x->parent->right = y; 

    y->right = x; 
    x->parent = y; 
}
