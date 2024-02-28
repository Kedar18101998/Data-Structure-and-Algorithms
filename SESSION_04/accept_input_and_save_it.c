#include <stdio.h> 
#include <stdlib.h> 

#define TRUE 1 

int main(void)
{
    int* p_arr = NULL;  /* Pointer to store address of first element in array */
    size_t N = 0;       /* Current size of array */
    int choice; 
    int num, i; 

    while(TRUE)
    {
        printf("Do you want to enter another integer?:[YES=1, NO=0]:"); 
        scanf_s("%d", &choice); 
        if(choice != 1)
            break; 
        printf("Enter an integer:"); 
        scanf_s("%d", &num); 

        p_arr = (int*)realloc(p_arr, (N+1) * sizeof(int)); 
        if(p_arr == NULL)
        {
            fprintf(stderr, "realloc():fatal:out of memory\n"); 
            exit(EXIT_FAILURE); 
        }
        N = N + 1; 
        p_arr[N-1] = num; 
    }

    puts("Data entered by user:"); 
    for(i = 0; i < N; ++i)
        printf("p_arr[%d]:%d\n", i, p_arr[i]); 

    puts("releasing the array"); 
    free(p_arr); 
    p_arr = NULL; 

    return (0); 
}