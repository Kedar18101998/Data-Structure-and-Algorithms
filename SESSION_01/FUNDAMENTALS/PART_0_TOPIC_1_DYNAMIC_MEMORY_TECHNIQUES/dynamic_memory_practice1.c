#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 

struct point
{
    double x; 
    double y; 
    double z; 
}; 

void array_of_pointers_to_user_defined_data_type(void); 

int main(void)
{
    array_of_pointers_to_user_defined_data_type(); 
    return (0); 
}

void array_of_pointers_to_user_defined_data_type(void)
{
    struct point** pp_point = NULL; 
    int a_size = 5; 
    int i; 

    pp_point = (struct point**)malloc(a_size * sizeof(struct point*)); 
    assert(pp_point != NULL); 
    memset(pp_point, 0, a_size * sizeof(struct point*)); 

    for(i = 0; i < a_size; ++i)
    {
        pp_point[i] = (struct point*)malloc(sizeof(struct point)); 
        memset(pp_point[i], 0, sizeof(struct point)); 
        pp_point[i]->x = 1.1 + i; 
        pp_point[i]->y = 2.2 + i; 
        pp_point[i]->z = 3.3 + i; 
    }

    for(i = 0; i < a_size; ++i)
        printf("pp_point[%d]->x=%.2lf\tpp_point[%d]->y=%.2lf\tpp_point[%d]->z=%.2lf\n", 
                i, pp_point[i]->x, i, pp_point[i]->y, i, pp_point[i]->z); 
    
    for(i = 0; i < a_size; ++i)
    {
        free(pp_point[i]); 
        pp_point[i] = NULL; 
    }

    free(pp_point); 
    pp_point = NULL; 
}