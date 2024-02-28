#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

typedef long long int s64; 

struct fib{
    s64* pa; 
    unsigned int N; 
}; 

s64 compute(struct fib* pfib, unsigned int n); 

int main(void){
    struct fib* pfib = NULL; 
    unsigned long long int start, end; 
    s64 result; 

    pfib = (struct fib*)malloc(sizeof(struct fib));
    if(pfib == NULL){
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    printf("Enter the fibonacci term you want to compute[0-200]:"); 
    scanf("%d", &pfib->N); 

    if(pfib->N > 200){
        puts("Range error"); 
        exit(EXIT_FAILURE); 
    }

    pfib->pa = (s64*)malloc((pfib->N + 1)* sizeof(s64)); 
    if(pfib->pa == NULL){
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    memset(pfib->pa, 0, (pfib->N+1) * sizeof(s64)); 

    start = time(0); 
    result = compute(pfib, pfib->N); 
    end = time(0); 
    printf("Fn = %llu\n", result); 
    printf("TIME(FN) = %llu\n", end-start); 

    free(pfib->pa); 
    free(pfib); 
    pfib = NULL; 

    exit(EXIT_SUCCESS); 
}

s64 compute(struct fib* pfib, unsigned int n){
    if(n == 0) 
        return (0); 
    
    if(n == 1)
        return (1);

    if(pfib->pa[n] > 0)
        return pfib->pa[n]; 
    else {
        pfib->pa[n] =  compute(pfib, n-1) + compute(pfib, n-2); 
        return pfib->pa[n]; 
    }
}