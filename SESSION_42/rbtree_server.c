#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "rbtree.h"

rbtree_t* create_rbtree(void)
{
    rbtree_t* p_rbtree = (rbtree_t*)xcalloc(1, sizeof(rbtree_t)); 
    p_rbtree->N = 0; 
    p_rbtree->nil = (rbnode_t*)xcalloc(1, sizeof(rbnode_t)); 
    p_rbtree->nil->data = -1; 
    p_rbtree->nil->color = BLACK; 
    p_rbtree->nil->left = NULL; 
    p_rbtree->nil->right = NULL; 
    p_rbtree->nil->parent = NULL; 
    p_rbtree->root_node = p_rbtree->nil; 
    return (p_rbtree); 
}

status_t destroy_rbtree(rbtree_t** pp_rbtree)
{
    rbtree_t* p_rbtree = *pp_rbtree; 

    destroy_node_level(p_rbtree->root_node, p_rbtree->nil); 
    free(p_rbtree->nil); 
    free(p_rbtree); 

    *pp_rbtree = NULL; 
    return (SUCCESS); 
}

void preorder_walk(rbtree_t* p_rbtree)
{
    puts("Preorder walk:"); 
    printf("[START]<->"); 
    preorder_node_walk(p_rbtree->root_node, p_rbtree->nil); 
    puts("[END]"); 
}

void inorder_walk(rbtree_t* p_rbtree)
{
    puts("Inorder walk:"); 
    printf("[START]<->"); 
    inorder_node_walk(p_rbtree->root_node, p_rbtree->nil); 
    puts("[END]");  
}

void postorder_walk(rbtree_t* p_rbtree)
{
    puts("Postorder walk:"); 
    printf("[START]<->"); 
    postorder_node_walk(p_rbtree->root_node, p_rbtree->nil); 
    puts("[END]"); 
}

status_t insert_into_rbtree(rbtree_t* p_rbtree, data_t new_data)
{
    rbnode_t* p_run = NULL; 
    rbnode_t* z = NULL; 

    z = get_rbnode(new_data, p_rbtree->nil);

    if(p_rbtree->root_node == p_rbtree->nil)
    {
        p_rbtree->root_node = z; 
        p_rbtree->N += 1; 
        rb_insert_fixup(p_rbtree, z); 
        return (SUCCESS); 
    }

    p_run = p_rbtree->root_node; 
    while(TRUE)
    {
        if(new_data <= p_run->data)
        {
            if(p_run->left == p_rbtree->nil)
            {
                p_run->left = z;
                z->parent = p_run; 
                break; 
            }
            else
                p_run = p_run->left; 
        }
        else
        {
            if(p_run->right == p_rbtree->nil)
            {
                p_run->right = z; 
                z->parent = p_run; 
                break; 
            } 
            else 
                p_run = p_run->right;         
        }
    }
    
    p_rbtree->N += 1; 
    rb_insert_fixup(p_rbtree, z); 
    return (SUCCESS); 
}

status_t remove_from_rbtree(rbtree_t* p_rbtree, data_t r_data)
{
    rbnode_t* z = p_rbtree->nil;     /* Node to be deleted */ 
    rbnode_t* y = p_rbtree->nil;     /* Inorder successor of node to be deleted 
                                        in case 3, 4 for bst_remove */ 
    rbnode_t* x = p_rbtree->nil;     /* To store address of root of subtree 
                                        that requires fixing */ 
    
    color_t y_original_color;   /*  to determine whether subtree rooted x 
                                    required fixing 
                                */ 
    z = search_rb_node(p_rbtree, r_data); 
    if(z == p_rbtree->nil)
        return (RB_DATA_NOT_FOUND); 
    
    /*  bst remove case 1 & 2: 
        z->right or z->left = Tree that will need fixup 
        y_original color = z's color 
    */ 
    y = z; 
    y_original_color = y->color; 

    if(z->left == p_rbtree->nil)
    {
        x = z->right; 
        rb_transplant(p_rbtree, z, z->right); 
    }
    else if(z->right == p_rbtree->nil)
    {
        x = z->left; 
        rb_transplant(p_rbtree, z, z->left); 
    }
    else
    {
        y = get_rb_min_node(p_rbtree, z->right); 
        y_original_color = y->color; 
        x = y->right; 
        if(y->parent == z)
            x->parent = y; 
        else 
        {
            rb_transplant(p_rbtree, y, y->right);
            y->right = z->right; 
            y->right->parent = y;      
        }
        rb_transplant(p_rbtree, z, y); 
        y->left = z->left; 
        y->left->parent = y; 
        y->color = z->color;    
    }

    if(y_original_color == BLACK && x != p_rbtree->nil)
        rb_delete_fixup(p_rbtree, x); 

    return (SUCCESS); 
}

status_t find_rb_data(rbtree_t* p_rbtree, data_t search_data)
{
    rbnode_t* p_find_node = p_rbtree->nil; 
    p_find_node = search_rb_node(p_rbtree, search_data); 
    return (p_find_node != p_rbtree->nil); 
}

unsigned int get_rb_height(rbtree_t* p_tree)
{
    return get_height_nodelevel(p_tree, p_tree->root_node); 
}

/* Implementation of auxillary routines */ 

rbnode_t* search_rb_node(rbtree_t* p_rbtree, data_t search_data)
{
    rbnode_t* p_run = p_rbtree->root_node; 
    while(p_run != p_rbtree->nil)
    {
        if(search_data == p_run->data)
            break; 
        else if(search_data < p_run->data)
            p_run = p_run->left; 
        else 
            p_run = p_run->right; 
    }

    return p_run; 
}


void rb_insert_fixup(rbtree_t* p_rbtree, rbnode_t* z)
{
    rbnode_t* y = NULL; 

    while(z->parent->color == RED)
    {
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if(y->color == RED)
            {
                z->parent->color = BLACK; 
                y->color = BLACK; 
                z->parent->parent->color = RED; 
                z = z->parent->parent; 
            } 
            else
            {
                if(z == z->parent->right)
                {
                    z = z->parent; 
                    left_rotate(p_rbtree, z); 
                }

                z->parent->color = BLACK; 
                z->parent->parent->color = RED; 
                right_rotate(p_rbtree, z->parent->parent); 
            }
        }
        else
        {
            y = z->parent->parent->left; 
            if(y->color == RED)
            {
                z->parent->color = BLACK; 
                y->color = BLACK; 
                z->parent->parent->color = RED; 
                z = z->parent->parent; 
            }
            else 
            {
                if(z == z->parent->left)
                {
                    z = z->parent; 
                    right_rotate(p_rbtree, z); 
                }

                z->parent->color = BLACK; 
                z->parent->parent->color = RED; 
                left_rotate(p_rbtree, z->parent->parent); 
            }
        }
    }

    p_rbtree->root_node->color = BLACK; 
}

void rb_delete_fixup(rbtree_t* p_rbtree, rbnode_t* x)
{
    rbnode_t* w = p_rbtree->nil; 
    while(x != p_rbtree->root_node && x->color == BLACK)
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;     
            if(w->color == RED)
            {
                w->color = BLACK;                   /* case 1 */ 
                x->parent->color = RED;             /* case 1 */
                left_rotate(p_rbtree, x->parent);   /* case 1 */
                w = x->parent->right;               /* case 1 */
            }

            if(w == p_rbtree->nil)
            {
                x = x->parent; 
                continue; 
            }

            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;     /* case 2 */ 
                x = x->parent;      /* case 2 */
            }
            else 
            {
                if(w->right->color == BLACK) 
                {
                    w->left->color = BLACK;     /* case 3 */ 
                    w->color = RED;             /* case 3 */
                    right_rotate(p_rbtree, w);  /* case 3 */
                    w = x->parent->right;       /* case 3 */
                }

                w->color = x->parent->color;        /* case 4 */ 
                x->parent->color = BLACK;           /* case 4 */
                w->right->color = BLACK;            /* case 4 */ 
                left_rotate(p_rbtree, x->parent);   /* case 4 */
                x = p_rbtree->root_node; 
            }
        }
        else
        {
            w = x->parent->left; 
            if(w->color == RED)
            {
                w->color = BLACK;                   /* case 1 */
                x->parent->color = RED;             /* case 1 */
                right_rotate(p_rbtree, x->parent);  /* case 1 */
                w = x->parent->left;                /* case 1 */
            }
                        
            if(w == p_rbtree->nil)
            {
                x = x->parent; 
                continue; 
            }

            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;     /* case 2 */
                x = x->parent;      /* case 2 */
            }
            else 
            {
                if(w->left->color == BLACK) 
                {
                    w->right->color = BLACK;    /* case 3 */
                    w->color = RED;             /* case 3 */
                    left_rotate(p_rbtree, w);   /* case 3 */
                    w = x->parent->left;        /* case 3 */
                }

                w->color = x->parent->color;        /* case 4 */ 
                x->parent->color = BLACK;           /* case 4 */
                w->left->color = BLACK;             /* case 4 */ 
                right_rotate(p_rbtree, x->parent);  /* case 4 */
                x = p_rbtree->root_node; 
            }
        }
    }

    x->color = BLACK;   /*    case 1 -> case 2 -> exit path 
                            in all other cases x is already BLACK
                        */ 
}

/* Precondition: x->right != p_tree->nil */ 
void left_rotate(rbtree_t* p_tree, rbnode_t* x)
{
    rbnode_t* y = NULL; 
    
    /* Part 1 */ 
    y = x->right; 
    x->right = y->left; 
    if(y->left != p_tree->nil)
        y->left->parent = x; 

    /* Part 2 */ 
    y->parent = x->parent; 
    if(x->parent == p_tree->nil)
        p_tree->root_node = y; 
    else if(x == x->parent->left)
        x->parent->left = y; 
    else if(x == x->parent->right)
        x->parent->right = y; 

    /* Part 3 */ 
    y->left = x; 
    x->parent = y; 
}

/* Precondition: x->left != p_tree->nil */ 
void right_rotate(rbtree_t* p_tree, rbnode_t* x)
{
    rbnode_t* y = NULL; 
    
    /* Part 1 */ 
    y = x->left; 
    x->left = y->right; 
    if(y->right != p_tree->nil)
        y->right->parent = x; 

    /* Part 2 */ 
    y->parent = x->parent; 
    if(x->parent == p_tree->nil)
        p_tree->root_node = y; 
    else if(x == x->parent->left)
        x->parent->left = y; 
    else if(x == x->parent->right)
        x->parent->right = y; 
    
    /* Part 3 */ 
    y->right = x; 
    x->parent = y; 
}

void rb_transplant(rbtree_t* p_rbtree, rbnode_t* u, rbnode_t* v)
{
    if(u->parent == p_rbtree->nil)
        p_rbtree->root_node = v; 
    else if(u == u->parent->left)
        u->parent->left = v; 
    else if(u == u->parent->right)
        u->parent->right = v; 
    if(v != p_rbtree->nil)
        v->parent = u->parent; 
}

unsigned int get_height_nodelevel(rbtree_t* p_tree, rbnode_t* p_node)
{
    if(p_node == p_tree->nil)
        return 0; 
    return (max(get_height_nodelevel(p_tree, p_node->left), 
                get_height_nodelevel(p_tree, p_node->right)) + 1); 
}

void destroy_node_level(rbnode_t* p_root_node, rbnode_t* nil)
{
    if(p_root_node != nil)
    {
        destroy_node_level(p_root_node->left, nil); 
        destroy_node_level(p_root_node->right, nil); 
        free(p_root_node); 
    }   
}

void preorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    {
        printf("[%d]<->", p_rbnode->data); 
        preorder_node_walk(p_rbnode->left, nil); 
        preorder_node_walk(p_rbnode->right, nil); 
    }   
}

void inorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    { 
        inorder_node_walk(p_rbnode->left, nil);
        printf("[%d]<->", p_rbnode->data); 
        inorder_node_walk(p_rbnode->right, nil); 
    }  
}

void postorder_node_walk(rbnode_t* p_rbnode, rbnode_t* nil)
{
    if(p_rbnode != nil)
    {
        postorder_node_walk(p_rbnode->left, nil); 
        postorder_node_walk(p_rbnode->right, nil); 
        printf("[%d]<->", p_rbnode->data); 
    }
}

rbnode_t* get_rb_max_node(rbtree_t* p_tree, rbnode_t* p_rbnode)
{
    rbnode_t* p_run = p_rbnode; 
    while(p_run->right != p_tree->nil)
        p_run = p_run->right; 
    return (p_run); 
} 

rbnode_t* get_rb_min_node(rbtree_t* p_tree, rbnode_t* p_rbnode)
{
    rbnode_t* p_run = p_rbnode; 
    while(p_run->left != p_tree->nil)
        p_run = p_run->left; 
    return (p_run); 
}

rbnode_t* get_rbnode(data_t new_data, rbnode_t* nil)
{
    rbnode_t* p_new_rbnode = NULL; 

    p_new_rbnode = (rbnode_t*)xcalloc(1, sizeof(rbnode_t)); 
    p_new_rbnode->data = new_data; 
    p_new_rbnode->color = RED; 
    p_new_rbnode->left = nil; 
    p_new_rbnode->right = nil; 
    p_new_rbnode->parent = nil; 

    return (p_new_rbnode); 
}

void *xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    assert(p != NULL); 
    return (p); 
}