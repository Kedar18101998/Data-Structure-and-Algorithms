#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef unsigned long long int u64; 

u64 fib(unsigned int n); 

int main(void){
    unsigned int N; 
    u64 FN; 
    u64 start, end; 

    printf("Enter the fibonacci term you want to compute:[0-200]"); 
    scanf("%d", &N); 
    if(N > 200){
        puts("Range error");
        exit(EXIT_FAILURE); 
    }

    start = time(0); 
    FN = fib(N); 
    end = time(0); 
    printf("FN=%llu\n", FN); 
    printf("Time(FN)=%llu\n", end-start); 

    exit(EXIT_SUCCESS); 
}

u64 fib(unsigned int N){
    if(N == 0)
        return (0); 
    
    if(N == 1)
        return (1); 
    
    return (fib(N-1) + fib(N-2)); 
}