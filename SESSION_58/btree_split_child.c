#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

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

struct btree* create_btree(int t); 
void split_child(struct btree_node* x, int i, int t); 

int main(void){

    return 0; 
}

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