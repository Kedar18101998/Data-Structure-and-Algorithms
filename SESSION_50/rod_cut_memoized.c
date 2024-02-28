#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 
#include <assert.h> 

#define ROD_LENGTH 10 

inline double cpa_max(double a, double b){
    return a > b ? a : b; 
}

double rod_cut(double* pd, double* memo, size_t N, int n); 

int main(void){
    // Price table 
    double pd[] = {
                    nan(0), 1.0, 5.0, 8.0, 9.0, 10, 
                    17.0, 17.0, 20.0, 24.0, 30.0
                };
    // Memo 
    double* memo = (double*)calloc(ROD_LENGTH + 1, sizeof(double));
    if(memo == NULL){
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }
    // Length of rod 
    int n = ROD_LENGTH; 

    // Optimized revenue 
    double rs = rod_cut(pd, memo, n+1, n); 
    printf("rs = %.2lf\n", rs); 

    // Release Memo 
    free(memo); 
    memo = NULL; 
    return (0); 
}

double rod_cut(double* pd, double* memo, size_t N, int n){
    // Predoncitions:
    // 1: N == n+1
    // 2: pd[0] : Don't care (NaN)
    // 3. pd[i] == Pi of Cormen (1 <= i <= n)
    // Goal: 
    // Compute the following: 
    // r(n) = max(Pi, r(n-1))
    double rs = -INFINITY; 
    int i; 
    if(n == 0)
        return (0.0);  
    if(memo[n] != 0.0)
        return (memo[n]); 
    for(i = 1; i <= n; ++i)
        rs = cpa_max(rs, pd[i] + rod_cut(pd, memo, N, n-i)); 
    memo[n] = rs; 
    return rs; 
}