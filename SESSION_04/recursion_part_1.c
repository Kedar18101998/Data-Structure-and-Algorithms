#include <stdio.h> 
#include <stdlib.h> 

typedef long long int ssize_t; 

ssize_t factorial(ssize_t); 
ssize_t recursive_sum(int* pa, ssize_t i); 
int bin_search(int* pa, int i, int j, int SE); 

void test_factorial(void); 
void test_recursive_sum(void); 
void test_bin_search(void); 

int main(void) 
{
    test_factorial(); 
    test_recursive_sum(); 
    test_bin_search(); 

    return (0); 
}

ssize_t factorial(ssize_t N)
{
    if(N < 0)
        return (-1); 

    if(N == 0)
        return (1); 

    return (N * factorial(N-1)); 
} 

ssize_t recursive_sum(int* pa, ssize_t i)
{
    if(i == -1)
        return (0); 
    return pa[i] + recursive_sum(pa, i-1); 
}
    
int bin_search(int* pa, int i, int j, int SE)
{
    int mid_index; 

    if(i <= j)
    {
        mid_index = (i+j)/2; 
        if(SE == pa[mid_index])
            return (mid_index); 
        else if(SE < pa[mid_index]) 
            return bin_search(pa, i, mid_index-1, SE); 
        else if(SE > pa[mid_index])
            return (bin_search(pa, mid_index+1, j, SE));    
    }

    return (-1); 
}

void test_factorial(void)
{
    ssize_t N1 = 5, N2 = 20, N3 = 13; 
    ssize_t fact_N1, fact_N2, fact_N3; 

    fact_N1 = factorial(N1); 
    fact_N2 = factorial(N2); 
    fact_N3 = factorial(N3); 

    printf("%lld! = %lld, %lld! = %lld, %lld! = %lld\n", 
            N1, fact_N1, N2, fact_N2, N3, fact_N3); 
}

void test_recursive_sum(void)
{
    const size_t N = 8; 
    int A[8] = {10, 20, 30, 40, 50, 60, 70, 80}; 
    ssize_t S = 0; 
    size_t i; 

    S = recursive_sum(A, N-1);
    puts("Array A:"); 
    for(i = 0; i < N; ++i)
        printf("A[%llu]:%d\n", i, A[i]); 
    puts("Summation of all elements in array:"); 
    printf("S = %lld\n", S); 
}

void test_bin_search(void)
{
    int A[8] = {10, 20, 30, 40, 50, 60, 70, 80}; 
    int B[12] = {   
                    10, 15, 20, -40, 30, 40, 
                    50, 55, 60, 66, 70, 80 
                }; 

    int i, SE, search_index, N=12, NA=8; 

    for(i = 0; i < N; ++i)
    {
        SE = B[i]; 
        search_index = bin_search(A, 0, NA-1, SE); 
        if(search_index == -1)
            printf("%d is not found in A\n", SE); 
        else 
            printf("%d found at index %d\n", SE, search_index); 
    }
}