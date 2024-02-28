#include <stdio.h>
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 

#include "btree.h"

/* Interface routine */
btree_t* create_btree(int t)
{
    if(t < 2)
    {
        fprintf(stderr, "Minimum degree field of B-tree cannot be less than 2\n"); 
        return (NULL); 
    }

    btree_t* new_tree = (btree_t*)calloc(1, sizeof(btree_t)); 
    assert(new_tree != NULL); 

    new_tree->root = get_btree_node(); 
    new_tree->t = t; 
    new_tree->nr_keys = 0; 

    return (new_tree); 
}

status_t search_btree(btree_t* btree, key_t s_key)
{
    status_t status = FALSE; 
    struct search_result* srs = NULL; 
    
    srs = search_btree_nodelevel(btree->root, s_key); 
    status = (srs != NULL); 
    free(srs); 
    srs = NULL; 

    return (status); 
}

status_t insert_btree(btree_t* btree, key_t new_key)
{
    btree_node_t* root_node = NULL; 
    btree_node_t* new_node = NULL; 
    int t; 

    root_node = btree->root; 
    t = btree->t; 
    if(root_node->keysN == (2*t-1))
    {
        new_node = get_btree_node(); 
        btree->root = new_node; 
        new_node->is_leaf = FALSE; 
        new_node->keysN = 0; 
        new_node->ptrs[0] = root_node; 
        btree_split_child(new_node, 0, t); 
        btree_insert_nonfull(new_node, new_key, t); 
    }
    else 
    {
        btree_insert_nonfull(root_node, new_key, t); 
    }

    return (SUCCESS); 
}

void inorder_btree(btree_t* btree)
{
    printf("[START]<->"); 
    btree_inorder_nodelevel(btree->root); 
    puts("[END]"); 
}

void destroy_btree(btree_t* btree)
{
    btree_destroy_nodelevel(btree->root); 
}

/* Auxillary routine */
btree_node_t* get_btree_node()
{
    btree_node_t* new_node = NULL; 

    new_node = (btree_node_t*)calloc(1, sizeof(btree_node_t)); 
    assert(new_node != NULL); 

    new_node->keys = NULL; 
    new_node->keysN = 0; 

    new_node->ptrs = (btree_node_t**)calloc(1, sizeof(btree_node_t*)); 
    assert(new_node->ptrs != NULL); 
    new_node->ptrsN = 1; 

    new_node->is_leaf = TRUE; 

    return (new_node); 
}

struct search_result* search_btree_nodelevel(btree_node_t* x, key_t s_key)
{
    struct search_result* srs = NULL;
    int i; 

    i = 0; 
    while(i < x->keysN && s_key > x->keys[i])  
        i = i + 1; 
    
    if(i < x->keysN && s_key == x->keys[i])
    {
        srs = (struct search_result*)calloc(1, sizeof(struct search_result)); 
        assert(srs != NULL); 
        srs->x = x; 
        srs->i = i; 
        return (srs); 
    }
    else if(x->is_leaf == TRUE)
    {
        return (NULL); 
    }
    else 
    {
        return search_btree_nodelevel(x->ptrs[i], s_key); 
    }
}

void btree_split_child(btree_node_t* x, int i, int t)
{
    btree_node_t* right_node = NULL; 
    btree_node_t* y = NULL; 
    key_t mid_key; 
    int k; 

    y = x->ptrs[i]; 
    mid_key = y->keys[t-1]; 
 
    right_node = (btree_node_t*)calloc(1, sizeof(btree_node_t)); 
    assert(right_node != NULL);
    
    right_node->keysN = t-1; 
    right_node->ptrsN = t; 
    right_node->is_leaf = y->is_leaf; 

    right_node->keys = (key_t*)calloc(
                                right_node->keysN, 
                                sizeof(key_t)
                            ); 
    assert(right_node->keys != NULL);


    right_node->ptrs = (btree_node_t**)calloc(
                                                right_node->ptrsN, 
                                                sizeof(btree_node_t*)
                                            ); 
    assert(right_node->ptrs != NULL); 
 
    memcpy(
            (void*)right_node->keys, 
            (const void*)&y->keys[t], 
            (t-1)*sizeof(key_t)
        ); 

    if(y->is_leaf == FALSE)
        memcpy(
            (void*)right_node->ptrs, 
            (const void*)&y->ptrs[t], 
            t * sizeof(btree_node_t*)
        ); 

    x->ptrs[i]->keysN = t-1; 
    x->ptrs[i]->ptrsN = t; 

    x->ptrs[i]->keys = (key_t*)realloc(
                                        x->ptrs[i]->keys, 
                                        (t-1) * sizeof(key_t)
                                    ); 
    assert(x->ptrs[i]->keys != NULL); 
    x->ptrs[i]->ptrs = (btree_node_t**)realloc(
                                                x->ptrs[i]->ptrs, 
                                                t * sizeof(btree_node_t*)
                                            ); 
    assert(x->ptrs[i]->ptrs != NULL); 

    x->keys = (key_t*)realloc(
                        x->keys, 
                        ((x->keysN) + 1) * sizeof(key_t)
                    );
    assert(x->keys != NULL); 
    x->keysN += 1; 
 
    x->ptrs = (btree_node_t**)realloc(
                            x->ptrs, 
                            (x->ptrsN + 1) * sizeof(btree_node_t*)
                        ); 
    assert(x->ptrs != NULL); 
    x->ptrsN += 1; 

    for(k = x->keysN - 2; k >= i; --k)
        x->keys[k+1] = x->keys[k]; 
 
    for(k = x->ptrsN - 2; k >= (i+1); --k)
        x->ptrs[k+1] = x->ptrs[k]; 

    x->keys[i] = mid_key; 
    x->ptrs[i+1] = right_node; 
}

void btree_insert_nonfull(btree_node_t* x, key_t key, int t)
{
    int k; 

    if(x->is_leaf == TRUE)
    {
        x->keys = (key_t*)realloc(x->keys, (x->keysN + 1) * sizeof(key_t)); 
        assert(x->keys != NULL);
        x->keysN += 1; 
        x->ptrs = (btree_node_t**)realloc(x->ptrs, 
                                            (x->ptrsN + 1)*sizeof(btree_node_t*)
                                        ); 
        x->ptrsN += 1; 
        for(k = x->keysN-2; k > 0 && x->keys[k] > key; --k)
            x->keys[k+1] = x->keys[k]; 
        x->keys[k+1] = key; 
        return; 
    }
    else 
    {
        k = x->keysN - 1; 
        while(k > 0 && x->keys[k] > key)
            k = k - 1; 
        k = k + 1; 
        if(x->ptrs[k]->keysN == (2*t-1))
        {
            btree_split_child(x, k, t); 
            if(key > x->keys[k])
                k = k + 1; 
        }
        btree_insert_nonfull(x->ptrs[k], key, t); 
    }
}

void btree_inorder_nodelevel(btree_node_t* y)
{
    int i; 
    
    if(y == NULL)
        return; 
  
    for(i = 0; i < y->keysN; ++i)
    {
        btree_inorder_nodelevel(y->ptrs[i]); 
        printf("[%d]<->", y->keys[i]); 
    }
    btree_inorder_nodelevel(y->ptrs[i]); 
}

void btree_destroy_nodelevel(btree_node_t* y)
{
    int i; 

    if(y != NULL)
    {
        for(i = 0; i < y->ptrsN; ++i)
            btree_destroy_nodelevel(y->ptrs[i]);
            
        free(y->keys); 
        free(y->ptrs); 
        free(y); 
    }
}

void test_btree_split_child(void)
{
    btree_node_t* x = NULL; 
    btree_node_t* y = NULL; 
    int t = 4; 
    int i, j; 
    int new_key = 550; 
    
    x = (btree_node_t*)calloc(1, sizeof(btree_node_t)); 
    x->is_leaf = FALSE; 
    assert(x != NULL); 
    x->keysN = 5; 
    x->ptrsN = x->keysN + 1; 
    x->keys = (key_t*)calloc(x->keysN, sizeof(key_t)); 
    assert(x->keys != NULL);
    x->ptrs = (btree_node_t**)calloc(x->ptrsN, sizeof(btree_node_t*)); 
    assert(x->ptrs); 

    for(i = 0; i < x->keysN; ++i)
        x->keys[i] = (i+1) * 100; 

    x->ptrs[1] = (btree_node_t*)calloc(1, sizeof(btree_node_t)); 
    y = x->ptrs[1]; 
 
    y->keysN = 2*t - 1; 
    y->ptrsN = y->keysN + 1; 
    y->is_leaf = TRUE; 
    y->keys = (key_t*)calloc(y->keysN, sizeof(key_t)); 
    assert(y->keys != NULL); 
    y->ptrs = (btree_node_t**)calloc(y->ptrsN, sizeof(btree_node_t*)); 
    assert(y->ptrs != NULL); 
    for(i = 0; i < y->keysN; ++i)
        y->keys[i] = 100 + (i+1) * 10; 
 
    btree_split_child(x, 1, t); 
    printf("x->keysN = %d\n", x->keysN); 
    printf("x->ptrsN = %d\n", x->ptrsN); 
   
    puts("Data in x:"); 
    for(i = 0; i < x->keysN; ++i)
        printf("x->keys[%d]:%d\n", i, x->keys[i]); 

    puts("Data in children of x:"); 
    for(i = 0; i < x->ptrsN; ++i)
    {
        if(x->ptrs[i] == NULL)
        {
            printf("x->ptrs[%d] is empty\n", i); 
            continue;
        } 

        y = x->ptrs[i]; 
        printf("Data in child %d in x\n", i); 
        printf("x->is_leaf=%d, x->keyN=%d, x->ptrsN=%d\n", x->is_leaf, 
                x->keysN, x->ptrsN); 
        for(j = 0; j < y->keysN; ++j)
            printf("x->ptrs[%d]->keys[%d]:%d\n", i, j, y->keys[j]); 
        for(j = 0; j < y->ptrsN; ++j)
            printf("y->ptrs[%d]:%p\n", j, y->ptrs[j]);
        printf("y->is_leaf = %d\n", y->is_leaf); 
        printf("y->keysN=%d, y->ptrsN=%d\n", y->keysN, y->ptrsN);  
    }

    puts("Search Testing:"); 
    struct search_result* rs = NULL; 

    key_t data[] = {100, 200, 300, 400, 500, 110, 120, 130, 140, 150, 160, 170}; 
    for(i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        rs = search_btree_nodelevel(x, data[i]); 
        if(rs != NULL)
            printf("data=%d, Address=%p, index=%d\n", data[i], rs->x, rs->i); 
        else 
            printf("data=%d not found\n", data[i]); 
    }

    for(i = 0; i < x->ptrsN; ++i)
    {
        if(x->ptrs[i] != NULL)
        {
            y = x->ptrs[i]; 
            if(y->is_leaf)
            {
                free(y->keys); 
                free(y->ptrs); 
                free(y); 
                y = NULL;
            }
        }
    }

    free(x->keys); 
    free(x->ptrs); 
    free(x); 
    x = NULL; 

    free(rs); 
    rs  = NULL; 
}