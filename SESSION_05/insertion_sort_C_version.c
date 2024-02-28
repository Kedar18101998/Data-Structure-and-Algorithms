#include <stdio.h> 
#include <stdlib.h> 

typedef long long ssize_t; 

void fill_array(int* p, ssize_t N); 
void show_array(int* p, ssize_t N, const char* msg); 
void insert_at_sorting_position(int* p, ssize_t N); 
void sort(int* p, ssize_t N); 

int main(int argc, char* argv[])
{
    int* a = NULL; 
    ssize_t N = 0; 

    if(argc != 2)
    {
        fprintf(stderr, "Usage Error:%s number of elements\n", argv[0]); 
        exit(EXIT_FAILURE); 
    }

    N = atoll(argv[1]);
    if(N <= 0)
    {
        fprintf(stderr, "Bad size for array"); 
        exit(EXIT_FAILURE); 
    }

    a = (int*)calloc(N, sizeof(int)); 
    if(a == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    fill_array(a, N); 
    show_array(a, N, "Array : Before sort"); 
    sort(a, N); 
    show_array(a, N, "Array : After sort"); 

    free(a); 
    a = NULL; 

    return (EXIT_SUCCESS); 
}

void fill_array(int* p, ssize_t N)
{
    ssize_t i; 
    
    srand(time(0)); 
    for(i = 0; i < N; ++i)
        p[i] = rand(); 
}

void show_array(int* p, ssize_t N, const char* msg)
{
    ssize_t i; 

    if(msg)
        puts(msg); 

    for(i = 0; i < N; ++i)
        printf("p[%lld]:%d\n", i, p[i]); 
}

void insert_at_sorting_position(int* p, ssize_t N)
{
    ssize_t i; 
    int key; 

    key = p[N-1]; 
    for(i = N-2; i > -1 && p[i] > key; --i)
        p[i+1] = p[i]; 
    p[i+1] = key; 
}

void sort(int* p, ssize_t N)
{
    ssize_t n;  /* size of subarray */

    for(n = 2; n <= N; ++n)
        insert_at_sorting_position(p, n);   
}