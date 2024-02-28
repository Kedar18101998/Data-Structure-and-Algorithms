#include <stdio.h> 
#include <stdlib.h> 

int main(void)
{
    int M = 5; 
    int N = 3; 
    int i, j; 

    int* p = (int*)malloc(M * N * sizeof(int)); 
    assert(p); 

    for(i = 0; i < M; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            *(p + i * N + j);  // int A[M][N]; A[i][j]
        }
    }

    free(p); 
}