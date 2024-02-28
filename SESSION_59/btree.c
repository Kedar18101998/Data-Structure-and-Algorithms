#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define SUCCESS 1 
#define TRUE    1 
#define FALSE   0  

struct btree_node{
    int* K; 
    int KN; 
    struct btree_node** L; 
    int LN; 
    int is_leaf; 
}; 

struct btree{
    struct btree_node* root; 
    int t; 
    int nr_keys; 
}; 

/* interface routines */
struct btree* create_btree(int t); 
int insert_btree(struct btree* btree, int k); 
void inorder(struct btree* btree); 
int destroy_btree(struct btree** pp_btree); 

/* Auxillary routines */
void split_child(struct btree_node* x, int i, int t); 
void btree_insert_nonfull(struct btree_node* x, int k, int t); 
void inorder_nodelevel(struct btree_node* x); 
void destroy_nodelevel(struct btree_node* x); 

/* Intermediate testing routines */
void test_split_child(void); 
void show_node(struct btree_node*, const char*); 

int main(void){
    int t = 3; 
    int data[] = {500, 100, 400, 200, 300, 600,
                  110, 140, 690, 900, 1000, 2000}; 
    int i; 
    int status; 
    struct btree* btree = NULL; 

    btree = create_btree(t); 

    for(i = 0; i < sizeof(data)/sizeof(data[0]); ++i){
        status = insert_btree(btree, data[i]); 
        assert(status == SUCCESS); 
    }

    // show_node(btree->root, "Showing root node"); 

    inorder(btree); 
    status = destroy_btree(&btree); 
    assert(btree == NULL && status == SUCCESS); 

    return 0; 
}

/* Interface routines */

struct btree* create_btree(int t){
    struct btree* p_tree = NULL; 

    assert(t >= 2); 
    p_tree = (struct btree*)malloc(sizeof(struct btree)); 
    assert(p_tree); 

    p_tree->root = NULL; 
    p_tree->nr_keys = 0; 
    p_tree->t = t; 

    return (p_tree); 
}

int insert_btree(struct btree* btree, int k){
    struct btree_node* root_node = NULL; 
    struct btree_node* new_root = NULL; 
    int t; 

    root_node = btree->root;
    if(root_node == NULL){
        btree->root = (struct btree_node*)calloc(1, sizeof(struct btree_node)); 
        assert(btree->root); 

        btree->root->is_leaf = TRUE; 
        btree->root->KN = 1; 
        btree->root->LN = btree->root->KN + 1; 
        btree->root->K = (int*)calloc(btree->root->KN, sizeof(int)); 
        assert(btree->root->K); 
        btree->root->L = (struct btree_node**)calloc(btree->root->LN, 
                                                    sizeof(struct btree_node*)); 
        assert(btree->root->L);
        btree->root->K[0] = k; 
        btree->nr_keys += 1; 
        return (SUCCESS);  
    } 

    t = btree->t; 
    if(root_node->KN == 2*t - 1){
        /* root node is full */
        new_root = (struct btree_node*)calloc(1, sizeof(struct btree_node)); 
        assert(new_root); 
        new_root->is_leaf = FALSE; 
        new_root->KN = 0; 
        new_root->LN = (new_root->KN) + 1; 
        new_root->K = NULL; 
        new_root->L = (struct btree_node**)calloc(new_root->LN, 
                                                    sizeof(struct btree_node*)); 
        new_root->L[0] = root_node; 
        btree->root = new_root; 
        split_child(new_root, 0, t); 
        btree_insert_nonfull(new_root, k, t); 
    }else{
        /* root node is not full */
        btree_insert_nonfull(root_node, k, t); 
    }

    btree->nr_keys += 1; 
    return (SUCCESS); 
}

void inorder(struct btree* btree){
    printf("[START]<->"); 
    inorder_nodelevel(btree->root); 
    puts("[END]"); 
}

int destroy_btree(struct btree** pp_btree){
    struct btree* btree = *pp_btree; 
    destroy_nodelevel(btree->root); 
    free(btree); 
    *pp_btree = NULL; 
    return (SUCCESS); 
}

/* Auxillary routines */

/* 
    KN = 2*t-1 
    INDEX: 0 to KN-1 == 0 to 2*t-2 
    First t-1 keys: indexed from 0 to t-2 
    t - th keys -> indexed at t-1 
    Rest of t-1 keys: indexed from t to 2*t-2

    LN = 2t 
    INDEX RANGE OF y->L : 0 to 2*t-1
    First t links are indexed from 0 to t-1 
    Rest of the t links are indexed from t to 2*t-1 
*/

void split_child(struct btree_node* x, int i, int t){
    struct btree_node* y = NULL;    /* y == node that is full */
    struct btree_node* nn = NULL;   /* NN == NEW NODE*/
    int ind, new_key, indK, indL; 

    assert(i < 2*t-1); 
    
    y = x->L[i];       
    nn = (struct btree_node*)malloc(sizeof(struct btree_node)); 
    assert(nn); 
    
    nn->is_leaf = y->is_leaf; 
    nn->KN = t-1; 
    nn->LN = t;
    nn->K = (int*)malloc(nn->KN * sizeof(int)); 
    assert(nn->K); 
    nn->L = (struct btree_node**)malloc(nn->LN * sizeof(struct btree_node*)); 
    assert(nn->L);
    
    for(ind = 0; ind < nn->KN; ++ind)
        nn->K[ind] = y->K[t+ind]; 
    for(ind = 0; ind < nn->LN; ++ind)
        nn->L[ind] = y->L[t+ind]; 

    new_key = y->K[t-1];
    
    /* resize y->K to hold t-1 keys*/
    y->K = (int*)realloc(y->K, (t-1) * sizeof(int)); 
    assert(y->K); 
    y->KN = t-1; 
    /* resize y->L to hold t keys*/ 
    y->L = (struct btree_node**)realloc(y->L, t * sizeof(struct btree_node*)); 
    y->LN = t; 

    x->K = (int*)realloc(x->K, (x->KN+1) * sizeof(int)); 
    assert(x->K); 
    x->KN += 1; 

    x->L = (struct btree_node**)realloc(x->L, (x->LN+1) * sizeof(struct btree_node*)); 
    assert(x->L); 
    x->LN += 1; 
    x->L[x->LN - 1] = NULL; 

    indK = x->KN-2; 
    indL = x->LN-2;

    while(indK > i-1){
        x->K[indK+1] = x->K[indK]; 
        x->L[indL+1] = x->L[indL]; 
        indL -= 1; 
        indK -= 1; 
    } 

    x->K[indK+1] = new_key; 
    x->L[indL+1] = nn; 
}   

void btree_insert_nonfull(struct btree_node* x, int k, int t){
    int i; 

    if(x->is_leaf == TRUE){
        /* nonfull + leaf */
        // printf("addr(x):%p\n", x); 
        x->K = (int*)realloc(x->K, (x->KN + 1) * sizeof(int)); 
        assert(x->K); 
        x->KN += 1; 

        x->L = (struct btree_node**)realloc(x->L, (x->LN + 1) * sizeof(struct btree_node*)); 
        x->LN += 1; 
        x->L[x->LN - 1] = NULL; 

        i = x->KN - 2; 
        while(i > -1 && x->K[i] > k){
            x->K[i+1] = x->K[i]; 
            i = i - 1; 
        }
        x->K[i+1] = k; 
    }else{
        /* nonfull + nonleaf */
        i = x->KN - 1; 
        while(i > -1 && x->K[i] > k)
            i = i - 1; 
        i = i + 1; 
        
        // assert(x->L[i] != NULL); 
    
        if(x->L[i] == NULL){
            x->L[i] = (struct btree_node*)calloc(1, sizeof(struct btree_node)); 
            x->L[i]->is_leaf = TRUE; 
            x->L[i]->KN = 0; 
            x->L[i]->LN = x->L[i]->KN + 1; 
            x->L[i]->L = (struct btree_node**)calloc(x->L[i]->LN, sizeof(struct btree_node*)); 
            x->L[i]->K = NULL; 
            // printf("x->L[%d]:%p\n", i, x->L[i]); 
        }else if(x->L[i]->KN == 2*t - 1){
            split_child(x, i, t); 
            if(k > x->K[i])
                i = i + 1; 
        }
        btree_insert_nonfull(x->L[i], k, t); 
    }
}

void inorder_nodelevel(struct btree_node* x){
    int i; 
    if(x != NULL){
        for(i = 0; i < x->KN; ++i){
            inorder_nodelevel(x->L[i]);
            printf("[%d]<->", x->K[i]); 
        }
        inorder_nodelevel(x->L[i]); 
    }
}

void destroy_nodelevel(struct btree_node* x){
    int i; 
    if(x != NULL){
        for(i = 0; i < x->LN; ++i)
            destroy_nodelevel(x->L[i]); 
        free(x->K); 
        free(x->L); 
        free(x); 
    }
} 

/* Intermediate testing routines */

void test_split_child(void){
    struct btree_node* x = NULL; 
    struct btree_node* y = NULL; 
    int t = 4; 
    int i; 

    x = (struct btree_node*)calloc(1, sizeof(struct btree_node)); 
    assert(x); 

    x->is_leaf = FALSE; 
    x->KN = 5; 
    x->LN = x->KN + 1; 
    x->K = (int*)calloc(x->KN, sizeof(int));
    assert(x->K); 
    x->L = (struct btree_node**)calloc(x->LN, sizeof(struct btree_node*)); 
    assert(x->L); 

    for(i = 0; i < x->KN; ++i)
        x->K[i] = (i+1) * 100; 
    
    x->L[1] = (struct btree_node*)calloc(1, sizeof(struct btree_node)); 
    assert(x->L[1]); 

    y = x->L[1]; 
    y->is_leaf = TRUE; 
    y->KN = 2*t - 1; 
    y->LN = y->KN + 1; 
    y->K = (int*)calloc(x->KN, sizeof(int)); 
    assert(y->K); 
    y->L = (struct btree_node**)calloc(y->LN, sizeof(struct btree_node*)); 
    assert(y->L); 

    for(i = 0; i < y->KN; ++i)
        y->K[i] = x->K[0] + (i+1) * 10; 

    show_node(x, "Showing x:"); 
    show_node(y, "Showing y:"); 

    split_child(x, 1, t); 

    puts("AFTER SPLIT CHILD"); 
    show_node(x, "Showing x:"); 
    show_node(x->L[1], "Showing x->L[1]:"); 
    show_node(x->L[2], "Showing x->L[2]:"); 

    puts("FREEING"); 
    for(i = 0; i < x->LN; ++i){
        if(x->L[i] != NULL && x->L[i]->is_leaf == TRUE){
            printf("Freeing x->L[%d]:%p\n", i, x->L[i]); 
            free(x->L[i]); 
        }
    }

    free(x); 
    x = NULL; 
}

void show_node(struct btree_node* p_node, const char* msg){
    int i; 

    if(msg)
        puts(msg); 

    printf("Address:%p\n", p_node); 
    printf("Leaf Status:%d\n", p_node->is_leaf); 
    printf("Number of keys:%d\n", p_node->KN); 
    printf("Number of links:%d\n", p_node->LN); 

    puts("KEYS:"); 
    for(i = 0; i < p_node->KN; ++i)
        printf("p_node->K[%d]:%d\n", i, p_node->K[i]); 

    puts("LINKS:"); 
    for(i = 0; i < p_node->LN; ++i)
        if(p_node->L[i] == NULL)
            printf("p_node->L[%d]:NULL\n", i); 
        else 
            printf("p_node->[%d]:%p\n", i, p_node->L[i]); 
}