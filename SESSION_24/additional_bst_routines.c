typedef struct bst_node bst_node_t; 

bst_node_t* preorder_predecessor_nodelevel(bst_node_t*); 
bst_node_t* preorder_successor_nodelevel(bst_node_t*); 
bst_node_t* postorder_predecessor_nodelevel(bst_node_t*); 
bst_node_t* postorder_successor_nodelevel(bst_node_t*); 


status_t bst_preorder_predecessor(bst_t* p_bst, int e_data, int* p_pred_data); 