#include <stdio.h> 
#include <stdlib.h> 

typedef unsigned long long int u64; 

u64 fib(unsigned int n){
    if(n == 0)
        return (0); 
    else if(n == 1)
        return (1); 
    else
        return (fib(n-1) + fib(n-2)); 
}

int main(void){
    unsigned int n; 
    u64 result; 

    printf("Enter n[between 0 to 10]:"); 
    scanf("%u", &n); 
    if(n > 10){
        puts("n out of range"); 
        exit(EXIT_FAILURE); 
    }

    result = fib(n); 
    printf("fib(%d)=%llu\n", n, result); 

    exit(EXIT_SUCCESS); 
}

// fib(7) TOTAL DRY RUN 