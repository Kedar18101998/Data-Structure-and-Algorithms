#ifndef _BST_H 
#define _BST_H 

#define SUCCESS 1 
#define TRUE    1
#define FALSE   0 

typedef int data_t; 
typedef int status_t; 
typedef int Bool; 
typedef unsigned int height_t; 
typedef struct bst_node bst_node_t; 
typedef struct bst bst_t; 

struct bst_node
{
    int data;
    struct bst_node* parent; 
    struct bst_node* left; 
    struct bst_node* right; 
}; 

struct bst 
{
    struct bst_node* root_node;     
    size_t nr_elements; 
}; 

bst_t* create_bst(void); 
status_t insert_bst(bst_t* p_bst, data_t new_data); 
status_t remove_bst(bst_t* p_bs, data_t new_data); 
void preorder_traversal(bst_t* p_bst); 
void inorder_traversal(bst_t* p_bst); 
void postorder_traversal(bst_t* p_bst); 
height_t height_bst(bst_t* p_bst); 
status_t destroy_bst(bst_t** pp_bst); 
Bool search_bst(bst_t* p_bst, data_t s_data); 

void preorder_traversal_nodelevel(bst_node_t* root_node); 
void inorder_traversal_nodelevel(bst_node_t* root_node); 
void postorder_traversal_nodelevel(bst_node_t* root_node);
height_t height_bst_nodelevel(bst_node_t* root_node); 
void destroy_bst_nodelevel(bst_node_t* root_node); 
bst_node_t* search_node(bst_node_t* root_node, data_t s_data); 
bst_node_t* get_bst_node(data_t new_data); 
void* xcalloc(size_t nr_elements, size_t size_per_element); 

#endif 