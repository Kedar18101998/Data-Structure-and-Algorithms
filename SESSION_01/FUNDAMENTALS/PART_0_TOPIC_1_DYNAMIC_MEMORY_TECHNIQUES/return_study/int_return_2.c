#include <stdio.h> 
#include <stdlib.h> 

void create_int(int* p, int init_n); 

int main(void)
{
    int n; 
    int* ptr = 0; 

    create_int(&n, 500); 
    printf("n = %d\n", 500); 

    ptr = malloc(sizeof(int)); 
    if(ptr == 0)
    {
        puts("Error in memory allocation"); 
        exit(-1); 
    }

    create_int(ptr, 1000); 
    printf("*ptr = %d\n", *ptr); 

    free(ptr); 
    ptr = 0; 

    exit(0); 
}

void create_int(int* p, int init_n)
{
    *p = init_n; 
}