#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

int* create_int(int init_n); 

int main(void)
{
    int* p = 0; 

    p = create_int(100);  
    printf("*p = %d\n", *p); 

    free(p); 
    p = 0; 
   
    return (0); 
}

int* create_int(int init_n)
{
    int* p_int = 0; 
    p_int = malloc(sizeof(int)); 
    assert(p_int != 0); 
    *p_int = init_n; 
    return (p_int); 
}

 