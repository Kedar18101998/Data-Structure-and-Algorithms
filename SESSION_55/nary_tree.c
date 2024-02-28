/* 
    This code attempts to increment the number of data elements in 
    BST node, preserving the search tree property. No attempt is being 
    made to balance the tree. 
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define TRUE    1 
#define FALSE   0 
#define SUCCESS 1 
#define NR_ELEMENTS 1000
#define ARY 7

typedef long long int ssize_t; 

struct node{
    int* D; 
    ssize_t DN; 
    ssize_t last_index; 
    struct node** L; 
    ssize_t LN; 
}; 

struct nary_tree{
    struct node* root_node; 
    ssize_t ary; 
    ssize_t nr_elements; 
}; 

struct nary_tree* create_nary_tree(ssize_t ary); 
int insert_nary_tree(struct nary_tree* p, int new_data); 
void inorder_nary(struct nary_tree* p_nary_tree); 
int search_nary(struct nary_tree* p_tree, int search_data); 
ssize_t height_nary_tree(struct nary_tree* p_tree); 
void destroy_nary_tree(struct nary_tree* p_tree); 

ssize_t height_nodelevel(struct node* p); 
struct node* search_nodelevel(struct node* p, int search_data); 
void insert_in_nonfull_node(struct node* p_node, int new_data); 
void nary_inorder_nodelevel(struct node* p); 
struct node* get_node(ssize_t DN); 
void destroy_nodelevel(struct node* p); 

int main(void){
    int* data = (int*)calloc(NR_ELEMENTS, sizeof(int)); 
    assert(data != NULL); 
    srand(time(0)); 
    int i; 
    for(i = 0; i < NR_ELEMENTS; ++i){
        data[i] = rand(); 
        printf("data=%d\n", data[i]); 
    }

    struct nary_tree* p_nary_tree = create_nary_tree(ARY); 
    int status; 
    for(i = 0; i < NR_ELEMENTS; ++i){
        status = insert_nary_tree(p_nary_tree, data[i]); 
        assert(status == SUCCESS); 
        /*
        if(status == SUCCESS)
            printf("%d is successfully inserted\n", data[i]); 
        else 
            printf("%d is insertion failed\n", data[i]); 
        */ 
    }

    inorder_nary(p_nary_tree); 

    puts("Testing for all present data elements"); 
    for(i = 0; i < NR_ELEMENTS; ++i){
        status = search_nary(p_nary_tree, data[i]); 
        if(status == TRUE)
            printf("%d is present in tree\n", data[i]); 
        else 
            printf("%d is absent in tree\n", data[i]); 
    }

    puts("Testing for all absent data elements"); 
    static int absent_data[] = {9500, 106893, 4572434, -5433, 36467, 0}; 
    for(i = 0; i < sizeof(absent_data)/sizeof(absent_data[0]); ++i){
        status = search_nary(p_nary_tree, absent_data[i]); 
        if(status == TRUE)
            printf("%d is present in tree\n", absent_data[i]); 
        else 
            printf("%d is absent in tree\n", absent_data[i]); 
    }

    printf("HEIGHT(TREE)=%lld\n",height_nary_tree(p_nary_tree)); 
    destroy_nary_tree(p_nary_tree); 

    free(data); 
    data = NULL; 
    
    return (EXIT_SUCCESS); 
}

struct nary_tree* create_nary_tree(ssize_t ary){
    struct nary_tree* p = NULL; 

    assert(ary >= 2); 
    p = (struct nary_tree*)calloc(1, sizeof(struct nary_tree)); 
    assert(p != NULL); 
    p->ary = ary; 

    return (p); 
}

int insert_nary_tree(struct nary_tree* p, int new_data){
    ssize_t i; 
    ssize_t index; 
    struct node* p_run = NULL; 

    /* root node is NULL*/
    if(p->root_node == NULL){
        p->root_node = get_node(p->ary-1); 
        insert_in_nonfull_node(p->root_node, new_data); 
        return (SUCCESS);     
    }

    p_run = p->root_node; 
    while(TRUE){
        if(p_run->last_index < p_run->DN){
            insert_in_nonfull_node(p_run, new_data);
            return (SUCCESS); 
        } 

        if(new_data < p_run->D[0])
            index = 0;  
        else if(new_data > p_run->D[p_run->DN-1])
            index = p_run->LN-1;  
        else{
            i = 0; 
            while(i < p_run->DN-1)
            {
                if(new_data > p_run->D[i] && new_data < p_run->D[i+1]){
                    index = i + 1; 
                    break; 
                }
                i = i + 1; 
            }
        }

        if(p_run->L[index] == NULL)
            p_run->L[index] = get_node(p->ary-1); 
        p_run = p_run->L[index]; 
    }
}

void inorder_nary(struct nary_tree* p_nary_tree){
    printf("[START]<->"); 
    nary_inorder_nodelevel(p_nary_tree->root_node); 
    printf("[END]\n"); 
}

int search_nary(struct nary_tree* p_tree, int search_data){
    struct node* p = NULL; 
    
    p = search_nodelevel(p_tree->root_node, search_data); 
    return (p != NULL ? TRUE : FALSE); 
}

ssize_t height_nary_tree(struct nary_tree* p_tree){
    return height_nodelevel(p_tree->root_node); 
}

void destroy_nary_tree(struct nary_tree* p_tree){
    destroy_nodelevel(p_tree->root_node); 
    free(p_tree); 
}

struct node* search_nodelevel(struct node* p, int search_data){
    ssize_t i; 

    if(p == NULL)
        return (NULL);

    if(search_data < p->D[0]) 
        return (search_nodelevel(p->L[0], search_data)); 
    
    for(i = 0; i < p->last_index-2; ++i)
        if(p->D[i] == search_data)
            return (p); 
        else if(search_data > p->D[i] && search_data < p->D[i+1])
            return (search_nodelevel(p->L[i+1], search_data)); 
        
    if(search_data > p->D[p->last_index-1])
        return (search_nodelevel(p->L[p->last_index], search_data)); 
}

void insert_in_nonfull_node(struct node* p_node, int new_data){
    ssize_t i; 

    /* Check if the node pointed by p_node is really nonfull*/
    assert(p_node->last_index < p_node->DN);
    for(i = 0; i < p_node->LN; ++i)
        assert(p_node->L[i] == NULL); 

    i = p_node->last_index-1; 
    while(i > -1 && p_node->D[i] > new_data){
        p_node->D[i+1] = p_node->D[i]; 
        i = i - 1; 
    }
    p_node->D[i+1] = new_data; 
    p_node->last_index += 1; 
}

void nary_inorder_nodelevel(struct node* p){
    ssize_t i; 

    if(p == NULL)
        return; 
    for(i = 0; i < p->last_index; ++i){
        nary_inorder_nodelevel(p->L[i]);
        printf("[%d]<->", p->D[i]); 
    }
    nary_inorder_nodelevel(p->L[p->LN-1]); 
}

void destroy_nodelevel(struct node* p){
    ssize_t i; 
    if(p != NULL){
        for(i = 0; i < p->last_index+1; ++i)
            destroy_nodelevel(p->L[i]);
        free(p->D); 
        free(p->L); 
        free(p);  
    }
}

ssize_t height_nodelevel(struct node* p){
    ssize_t* h_arr = NULL; 
    ssize_t i; 
    ssize_t h_max; 

    if(p == NULL)
        return (0); 

    h_arr = (ssize_t*)calloc((p->last_index) + 1, sizeof(ssize_t)); 
    if(h_arr == NULL){
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }  

    for(i = 0; i < (p->last_index) + 1; ++i)
        h_arr[i] = height_nodelevel(p->L[i]); 
    
    h_max = h_arr[0]; 
    for(i = 1; i < (p->last_index) + 1; ++i)
        if(h_arr[i] > h_max)
            h_max = h_arr[i]; 

    free(h_arr); 
    h_arr = NULL; 

    return (h_max+1); 
}

struct node* get_node(ssize_t DN){
    struct node* p = NULL; 

    assert(DN >= 1); 
    p = (struct node*)malloc(sizeof(struct node)); 
    assert(p != NULL); 

    p->DN = DN; 
    p->LN = DN+1; 

    p->D = (int*)calloc(p->DN, sizeof(int)); 
    assert(p->D != NULL); 

    p->L = (struct node**)calloc(p->LN, sizeof(struct node*)); 
    assert(p->L != NULL); 
    p->last_index = 0; 

    return (p); 
}
