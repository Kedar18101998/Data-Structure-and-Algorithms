typedef enum color 
{
    RED=1, 
    BLACK
}; 

struct rb_node 
{
    int data; 
    color_t color; 

    struct rb_node* left; 
    struct rb_node* right; 
    struct rb_node* parent; 
}; 

struct rb_tree 
{
    struct rb_node* p_root_node;
    size_t number_of_elements; 
}; 

struct rb_node* get_rb_node(int new_data)
{
    
}