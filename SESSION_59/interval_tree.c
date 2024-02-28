#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define TRUE        1
#define FALSE       0 
#define SUCCESS     1 
#define NO_OVERLAP  2 

struct interval{
    int start, end; 
}; 

struct interval_node{
    struct interval x; 
    int max; 
    struct interval_node* left; 
    struct interval_node* right; 
    struct interval_node* parent; 
}; 

struct interval_tree{
    struct interval_node* root_node; 
    int nr_intervals; 
}; 

/* interface */
struct interval_tree* create_interval_tree(void); 

int insert_interval_tree(   
                            struct interval_tree* intvl_tree, 
                            struct interval new_interval
                        ); 

void search_interval(   
                        struct interval_tree* intvl_tree, 
                        struct interval search_interval, 
                        struct interval*** ppp_search, 
                        int* pN
                    );

int remove_interval(struct interval_tree* intvl_tree, struct interval r_interval); 

int destroy_interval_tree(struct interval_tree** intvl_tree); 



/* auxillary */
int do_overlap( 
                struct interval* search_interval, 
                struct interval* x_interval
            ); 

void compute_max_nodelevel(struct interval_node* p); 
void inorder_nodelevel(struct interval_node* x); 
void destroy_interval_tree_nodelevel(struct interval_node* p); 
void release_search_intervals(struct interval*** ppp_search, int N); 
struct interval_node* get_node(struct interval new_interval); 
void* xcalloc(size_t nr_elements, size_t size_per_element); 

int main(void){
    // test interval tree 
}

struct interval_tree* create_interval_tree(void){
    // BST create 
}

int insert_interval_tree(   
                            struct interval_tree* intvl_tree, 
                            struct interval new_interval
                        ){
                            
    // BST insert as per p_interval_node->x.start as KEY FIELD 
    // compute_max_nodelevel(intvl_tree->root_node)
}

void search_interval(
                        struct interval_tree* intvl_tree, 
                        struct interval search_interval, 
                        struct interval*** ppp_search, 
                        int* pN
                                ){
        //  As explained in class 
        //  search->end >= node->x.start (some nodes along with their RHS are skipped)
        //  search->start > node->max (entire subtree rooted at node along with node 
        //  is skipped )
        //  other than these points its  USUAL search algo 

        //  result of search algorithm must not be returned as true or false 
        //  but it will be a vector (dynamic growing array) if struct interval* 
        //  each struct interval pointer in that array will point to a dynamic 
        //  instance of each overlapping internal from tree. 
        //  overlap will measured between search_interval and node->x for all nodes 
        //  in interval tree pointed by intvl_tree. 
        //  Total size of array should be written on integer pointed by pN
        //  caller will use release_search_intervals to release this array. 
}

int remove_interval(struct interval_tree* intvl_tree, struct interval r_interval){
    // BST remove as per p_interval_node->x.start as KEY FIELD 
    // aftre removal call 
    // compute_max_nodelevel(intvl_tree->root_node)
}

/* Auxillary routines */

int do_overlap( 
                struct interval* search_interval, 
                struct interval* x_interval
            ){
    return (search_interval->end >= x_interval->start && 
            search_interval->start <= x_interval->end); 
}

void compute_max_nodelevel(struct interval_node* p){
    if(p){
        compute_max_nodelevel(p->left); 
        compute_max_nodelevel(p->right);
        if(p->left == NULL && p->right == NULL)
            p->max = p->x.end;
        else
            p->max = (p->left->max > p->right->max ? (p->left->max) : (p->right->max)); 
    }
}

int destroy_interval_tree(struct interval_tree** pp_intvl_tree){
    struct interval_tree* intvl_tree = *pp_intvl_tree; 
    destroy_interval_tree_nodelevel(intvl_tree->root_node);
    return (SUCCESS);  
}

void inorder_nodelevel(struct interval_node* x){
    if(x){
        inorder_nodelevel(x->left); 
        printf("{[%d-%d]}<->\n", x->x.start, x->x.end); 
        inorder_nodelevel(x->right); 
    }
} 

void destroy_interval_tree_nodelevel(struct interval_node* p){
    if(p){
        destroy_interval_tree_nodelevel(p->left); 
        destroy_interval_tree_nodelevel(p->right); 
        free(p); 
    }
}

void release_search_intervals(struct interval*** ppp_search, int N){
    struct interval** pp_search = *ppp_search;
    int i; 

    for(i = 0; i < N; ++i)
        free(pp_search[i]); 

    free(pp_search); 
    *ppp_search = NULL; 
}

struct interval_node* get_node(struct interval new_interval){
    struct interval_node* p = NULL; 

    p = (struct interval_node*)xcalloc(1, sizeof(struct interval_node));
    p->x.start = new_interval.start; 
    p->x.end = new_interval.end; 
    p->max = -1; 
    p->left = NULL; 
    p->right = NULL; 
    p->parent = NULL; 

    return (p); 
}

void* xcalloc(size_t nr_elements, size_t size_per_element){
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    assert(p); 
    return (p); 
}