int get_random_number_1(); 
void test_call_1()
{
    int num; 

    num = get_random_number_1(); 
}
//////////////////////////////////////////

void get_random_number_2(int* p_num); 
void test_call_2(void)
{
    int num; 

    get_random_number_2(&num); 
}

//////////////////////////////////////////////

int* get_int_1(int num)
{
    int* p = NULL; 

    p = (int*)malloc(sizeof(int)); 
    assert(NULL != p); 

    *p = num; 

    return (p); 
}

void test_call_3(void)
{
    int* p_new_int = NULL; 

    p_new_int = get_int_1(100); 
    // use p_new_int 
    free(p_new_int); 
    p_new_int = NULL; 

}

///////////////////////////////////////////

void get_int_2(int num, int** pp_int)
{
    int* p = NULL; 

    p = (int*)malloc(sizeof(int)); 
    assert(NULL != p); 

    *p = num; 
    *pp_int = p; 
}

void test_call_4(void)
{
    int* p_new_int = NULL; 

    get_int_2(100, &p_new_int); 
    // Use p_new_int 
    free(p_new_int); 
    p_new_int = NULL; 
}
///////////////////////////////////////////////

void get_node_and_previous(struct node* p_list, 
                            int search_data, 
                            struct node** pp_node, 
                            struct node** pp_prev_node
                        ); 
