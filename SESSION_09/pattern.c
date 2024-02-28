#include <stdio.h> 

void test_1(void)
{
    #define N 10 
    int A[N]; 
    int i; 
    /* To take a common action on every element of array 
        Take an action on A[i] 
        and make i travel from 0 to N-1
    */

   i = 0; 
   while(i < N)
   {
        // Common Action on A[i] 
        i = i + 1; 
   }

   for(i=0; i<N; ++i)
   {
        // common action on A[i]
   }

}

struct node
{
    int data; 
    struct node* next; 
}; 

void test_2(void)
{
    //  if action must be performed on all elements on 
    //  list, then express that action on run->data 
    struct node* p_start_1 = NULL; 
    // p_start_1 contains some nodes 
    struct node* run; 

    run = p_start_1; 
    while(run != NULL)
    {
        // COMMON ACTION ON run->data
        run = run->next; 
    }

    for(run=p_start_1; run != NULL; run=run->next)
    {
        // COMMON ACTION ON run->data 
    }

}