#include <stdio.h> 
#include <stdlib.h> 

#define TRUE 1 

void merge_1(int* a, int p, int q, int r)
{
    int* a1 = NULL; 
    int* a2 = NULL; 
    int N1, N2; 
    int i, j, k; 
    int index; 

    N1 = q-p+1; 
    N2 = r-q;

    a1 = (int*)calloc(N1, sizeof(int)); 
    if(a1 == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    a2 = (int*)calloc(N2, sizeof(int)); 
    if(a2 == NULL)
    {
        fprintf(stderr, "calloc():fatal:out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    for(index=0; index < N1; ++index)
        a1[index] = a[p+index]; 

    for(index=0; index < N2; ++index)
        a2[index] = a[q+1+index]; 

    i = 0; 
    j = 0; 
    k = 0; 

    while(TRUE)
    {
        if(a1[i] <= a2[j])
        {
            a[p+k] = a1[i]; 
            ++k; 
            ++i; 
            if(i == N1)
            {
                while(j < N2)
                {
                    a[p+k] = a2[j]; 
                    ++j; 
                    ++k; 
                }
                break; 
            }
        }
        else 
        {
            a[p+k] = a2[j]; 
            ++k; 
            ++j; 
            if(j == N2)
            {
                while(i < N1)
                {
                    a[p+k] = a1[i]; 
                    ++i; 
                    ++k; 
                }
                break; 
            }
        }
    }

    free(a1);
    a1 = NULL; 

    free(a2); 
    a2 = NULL; 
}

/* 
    CURRENT ABILITY: 
        1st CODE : 

        Nth CODE: ?? 

        1st CODE: ABILTIY, VISUALIZATION, SPEED

        2nd CODE: 


        kth CODE: 

*/