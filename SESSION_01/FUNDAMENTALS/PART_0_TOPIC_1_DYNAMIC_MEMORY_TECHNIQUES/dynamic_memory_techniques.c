#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>

struct point
{
    double x, y, z; 
}; 

void built_in_data_type(void); 
void array_of_built_in_data_type(void); 
void array_of_pointers_to_built_in_data_type(void); 

void user_defined_data_type(void); 
void array_of_user_defined_data_type(void); 
void array_of_pointers_to_user_defined_data_type(void); 

int main(void)
{
    built_in_data_type(); 
    array_of_built_in_data_type(); 
    array_of_pointers_to_built_in_data_type(); 
    user_defined_data_type(); 
    array_of_user_defined_data_type(); 
    array_of_pointers_to_user_defined_data_type(); 
    return (0); 
}

void built_in_data_type(void)
{
    int* p = NULL;                      /* declare & init pointer */ 
    puts("built_in_data_type"); 
    p = (int*)malloc(sizeof(int));      /* allocate memory */ 
    assert(p != NULL);                  /* Check if dynamic memory allocation is a success */ 
    memset(p, 0, sizeof(int));          /* initialize to zero */ 
    *p = 500;                           /* write */ 
    printf("*p = %d\n", *p);            /* read */ 
    free(p);                            /* release */ 
    p = NULL;                           /* make pointer NULL */ 
}

void array_of_built_in_data_type(void)
{
    int* p = NULL;  
    int a_size = 5; 
    int i; 
    puts("array_of_built_in_data_type"); 
    p = (int*)malloc(a_size * sizeof(int)); 
    assert(p != NULL);
    for(i = 0; i < a_size; ++i)
        p[i] = (i+1) * 10; 
    for(i = 0; i < a_size; ++i)
        printf("p[%d]:%d\n", i, p[i]); 
    free(p); 
    p = NULL; 
}

void array_of_pointers_to_built_in_data_type(void)
{
    int** pp = NULL; 
    int a_size = 5; 
    int i; 
    puts("array_of_pointers_built_in_data_type"); 
    pp = (int**)malloc(a_size * sizeof(int*)); 
    assert(pp != NULL);
    memset(pp, 0, a_size * sizeof(int*));
    for(i = 0; i < a_size; ++i)
    {
        pp[i] = (int*)malloc(sizeof(int)); 
        assert(pp[i] != NULL);
        (*pp)[i] = (i+1) * 10; 
    }

    for(i = 0; i < a_size; ++i)
    {
        printf("*pp[%d]:%d\n", i, (*pp)[i]); 
    }

    for(i = 0; i < a_size; ++i)
    {
        free(pp[i]); 
        pp[i] = NULL; 
    }

    free(pp); 
    pp = NULL; 
}

void user_defined_data_type(void)
{
    struct point* p_point = NULL;                               /* allocate and initialize pointer */ 
    
    puts("user defined data type"); 

    p_point = (struct point*)malloc(sizeof(struct point));      /* allocate memory */ 
    assert(p_point != NULL);                                    /* Check if dynamic memory allocation is a success */ 
    memset(p_point, 0, sizeof(struct point));                   /* init memory*/ 
    p_point->x = 1.1;                                           /* write */ 
    p_point->y = 2.2;                                           /* write */
    p_point->z = 3.3;                                           /* write */
    
    printf("p_point->x=%lf p_point->y=%lf p_point->z=%lf\n",    /* read */ 
    p_point->x, p_point->y, p_point->z);    
    
    free(p_point);                                              /* release memory */ 
    p_point = NULL;                                             /* make pointer NULL */ 
}

void array_of_user_defined_data_type(void)
{
    struct point* p_point = NULL; 
    int a_size = 5; 
    int i; 

    puts("array_of_user_defined_data_type"); 
    p_point = (struct point*)malloc(a_size * sizeof(struct point)); 
    assert(p_point != NULL);
    memset(p_point, 0, a_size * sizeof(struct point)); 

    for(i = 0; i < a_size; ++i)
    {
        p_point[i].x = 1.1 + i; 
        p_point[i].y = 2.2 + i; 
        p_point[i].z = 3.3 + i; 
    }

    for(i = 0; i < a_size; ++i)
    {
        printf("p_point[%d].x:%.2lf p_point[%d].y:%.2lf p_point[%d].z:%.2lf\n", 
                i, p_point[i].x, i, p_point[i].y, i, p_point[i].z); 
    } 

    free(p_point); 
    p_point = NULL; 
}

void array_of_pointers_to_user_defined_data_type(void)
{
    struct point** pp_point = NULL; 
    int a_size = 5; 
    int i; 

    puts("array_of_pointers_to_user_defined_data_type"); 

    pp_point = (struct point**)malloc(a_size * sizeof(struct point*)); 
    assert(pp_point); 
    memset(pp_point, 0, a_size * sizeof(struct point*));

    for(i = 0; i < a_size; ++i)
    {
        pp_point[i] = (struct point*)malloc(sizeof(struct point)); 
        assert(pp_point[i] != NULL);
        pp_point[i]->x = 1.1 + i; 
        pp_point[i]->y = 2.2 + i; 
        pp_point[i]->z = 3.3 + i;  
    }

    for(i = 0; i < a_size; ++i)
    {
        printf("pp_point[%d]->x:%.2lf pp_point[%d]->y:%.2lf pp_point[%d]->z:%.2lf\n", 
                i, pp_point[i]->x, i, pp_point[i]->y, i, pp_point[i]->z);         
    }

    for(i = 0; i < a_size; ++i)
    {
        free(pp_point[i]); 
        pp_point[i] = NULL; 
    }

    free(pp_point); 
    pp_point = NULL; 
}

// pp_point[i]->x/y/z = (*pp_point + i)->x/y/z
//                      (*(*pp_pointer+i)).x/y/z

// p->x == (*p).x