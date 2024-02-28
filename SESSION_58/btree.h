#ifndef _BTREE_H 
#define _BTREE_H 

#define SUCCESS 1 
#define TRUE    1 
#define FALSE   0 

typedef int key_t; 
typedef int status_t; 
typedef struct btree_node btree_node_t; 
typedef struct btree btree_t; 

struct btree_node 
{
    key_t* keys; 
    int keysN; 
    struct btree_node** ptrs; 
    int ptrsN; 
    int is_leaf; 
}; 

struct btree
{
    struct btree_node* root; 
    int t; 
    int nr_keys; 
}; 

struct search_result
{
    btree_node_t* x; 
    int i; 
}; 

/* Interface routine */
btree_t* create_btree(int t); 
status_t search_btree(btree_t* btree, key_t s_key); 
status_t insert_btree(btree_t* p_tree, key_t new_key); 
void inorder_btree(btree_t* btree); 
void destroy_btree(btree_t* btree); 

/* Auxillary routine */
btree_node_t* get_btree_node(); 
struct search_result* search_btree_nodelevel(btree_node_t* x, key_t s_key); 
void btree_split_child(btree_node_t* x, int i, int t); 
void test_btree_split_child(void); 
void btree_insert_nonfull(btree_node_t* x, key_t key, int t); 
void btree_inorder_nodelevel(btree_node_t* y); 
void btree_destroy_nodelevel(btree_node_t* y); 

#endif /* _BTREE_H */
