#include "list.h" 
#include "vector.h" 

int main(void)
{
    init_handle_table(); 

    int h_list_1=-1, h_list_2=-1; 

    h_list_1 = create_list(); 
    h_list_2 = create_list(); 

    insert_end(h_list_1, 100); 
    insert_end(h_list_2, 200); 

    destroy_list(h_list_1); 
    h_list_1 = -1; 

    destroy_list(h_list_2); 
    h_list_2 = -1; 

    release_handle_table(); 
}