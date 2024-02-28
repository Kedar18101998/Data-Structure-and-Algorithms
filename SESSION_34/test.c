vnodeptr_list_t* vnodeptr_create_list(void); 
status_t vnodeptr_insert_end(vnodeptr_list_t* pvnodeptr_list, vertex_t v); 
void vnodeptr_generic_insert(vnodeptr_t* beg, vnodeptr_t* mid, vnodeptr_t* end); 
void vnodeptr_generic_delete(vnodeptr_t* pvnodeptr_node); 
vnodeptr_t* vnodeptr_searcvnodeptr_node(vnodeptr_list_t* pvnodeptr_list, vertex_t v); 
vnodeptr_t* vnodeptr_get_node(vertex_t v); 