#include <stdio.h> 
#include <stdlib.h> 

void show(int* a, int n, const char* msg); 
int partition(int* a, int p, int r); 

int main(void)
{
    int a[16] = {0, 0, 0, 30, 21, 45, 70, 80, 90, 11, 42, 28, 100, 50, 0, 0}; 
    int p = 3; 
    int r = 13; 
    int q; 

    show(&a[p], r-p+1, "Before partition:"); 
    q = parition(a, p, r); 
    show(&a[p], q-p, "LEFT SUBARRAY:"); 
    printf("a[q]:%d\n", a[q]); 
    show(&a[q+1], r - q, "RIGHT SUBARRAY:"); 

    return (0); 
}

int parition(int *a, int p, int r)
{
    int j;  /* outer loop index variable */ 
    int i;  /* a[p...i] <= a[q] | a[i+1...j-1] > a[q] */ 
    int pivot; 
    int tmp; 

    pivot = a[r]; 
    i = p - 1; 

    for(j = p; j < r; ++j)
    {
        if(a[j] <= pivot)
        {
            i = i + 1; 
            tmp = a[i]; 
            a[i] = a[j]; 
            a[j] = tmp; 
        }
    }

    tmp = a[i+1]; 
    a[i+1] = a[r]; 
    a[r] = tmp; 

    return (i+1); 
}

void show(int* a, int n, const char* msg)
{
    int i; 
    if(msg)
        puts(msg); 
    for(i = 0; i < n; ++i)
        printf("a[%d]:%d\n", i, a[i]); 
}