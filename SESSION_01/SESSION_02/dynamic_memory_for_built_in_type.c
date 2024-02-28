#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 

void int_single_instance(void); 
void int_array(void); 
void array_of_int_ptrs(void); 

int main(void) 
{
    int_single_instance(); 
    int_array(); 
    array_of_int_ptrs(); 
    exit(EXIT_SUCCESS); 
}

void int_single_instance(void)
{
    int* p = NULL;  // S1 
    int m; 
    
    p = (int*)malloc(sizeof(int));  // S2 
    // S3 
    if(p == NULL)
    {
        fprintf(stderr, "fatal:out of virtual address space\n"); 
        exit(EXIT_FAILURE); 
    }

    memset(p, 0, sizeof(int)); // S4 

    *p = 100;   // S5: Write 
    m = *p;     // S5: Read 

    printf("m = %d\n", m); 

    free(p);    // S6
    p = NULL;   // S7  
}

void int_array(void)
{
    int* p = NULL; // S1 
    size_t N = 8; 
    int i; 

    puts("In int_array"); 

    p = (int*)malloc(N * sizeof(int)); // S2 
    // S3 
    if(p == NULL)
    {
        fprintf(stderr, "malloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    memset(p, 0, N * sizeof(int)); //S4 

    for(i = 0; i < N; ++i)
        *(p + i) = (i + 1) * 10; // S5: WRITE: p[i] = (i+1) * 10 

    for(i = 0; i < N; ++i)
        printf("*(p + %d):%d\n", i, *(p+i)); // S5: READ 

    free(p); // S6 
    p = NULL; // S7 
} 

void array_of_int_ptrs(void)
{
    int** pp = NULL;    /* A pointer variable to hold the address of 
                            dynamically allocated array of pointer to 
                            intgers 
                        */
    size_t N = 8; 
    int i; 

    puts("Array of integer pointers"); 

    pp = (int**)malloc(N * sizeof(int*)); 
    if(pp == NULL)
    {
        fprintf(stderr, "malloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    memset(pp, 0, N * sizeof(int*)); 

    for(i = 0; i < N; ++i)
    {
        pp[i] = (int*)malloc(sizeof(int)); 
        if(pp[i] == NULL)
        {
            fprintf(stderr, "malloc():fatal:out of memory\n"); 
            exit(EXIT_FAILURE); 
        }
        memset(pp[i], 0, sizeof(int)); 
    }

    for(i = 0; i < N; ++i)
        *pp[i] = (i+1) * 10; 

    for(i = 0; i < N; ++i)
        printf("*pp[%d]:%d\n", i, *pp[i]); 

    for(i = 0; i < N; ++i)
    {
        free(pp[i]); 
        pp[i] = NULL; 
    }

    free(pp); 
    pp = NULL; 
}

    
/* 
    static time: source finish -> executable/dll
    time elapsed in the building of source code 
    (preprocessing->compile->assemble->link)

    run time/dynamic time: 
    launch exe -> terminate process / application 
    
    malloc(N); // Pre: N > 0
*/