#include <stdio.h> 
#include <stdlib.h> 

unsigned long long fact(unsigned long long); 
unsigned long long sigma(int* pa, int N); 
void print_array_reverse_r(int* pa, int N); 
void print_array_r(int* pa, int index, int size);
void array_reverse_in_place_r(int* pa, int start_index, int end_index); 

void insertion_sort(int* pa, int size); 

int main(void)
{
	/* CAUTION : Array : For which recursive function 
		N = size of array argument 
		N-1 = last index of array : argument 
	*/ 
    unsigned long long n = 15; 
    unsigned long long summation = 0; 
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; 
    int b[15] = {
                    345345, 9463, 46353, 4635325, 424525, 
                    345436, 3524, 36525, 375555547, 58463, 
                    57634535, 325245, 325, 64, 47353
                }; 
    int i; 
    int max_element; 
    int index; 

    printf("fact(%llu):%llu\n", n, fact(n)); 
    summation = sigma(a, 10); 
    printf("sigma(a,10):%llu\n", summation); 
    print_array_reverse_r(a, 10); 
    print_array_r(a, 0, 10); 
    puts("Array BEFORE INPLACE REVERSAL"); 
    for(i = 0; i < 10; ++i)
        printf("a[%d]:%d\n", i, a[i]); 
    array_reverse_in_place_r(a, 0, 9); 
    puts("Array AFTER INPLACE REVERSAL");  
    for(i = 0; i < 10; ++i)
        printf("a[%d]:%d\n", i, a[i]); 
    array_reverse_in_place_r(a, 2, 8); 
    puts("Array AFTER INPLACE REVERSAL A[2:8]:");  
    for(i = 0; i < 10; ++i)
        printf("a[%d]:%d\n", i, a[i]); 
    max_element = find_max(b, 0, 14); 
    printf("max_element = %d\n", max_element); 
    insertion_sort(b, 15); 
    for(i = 0; i < 15; ++i)
    {
        index = search(b, b[i], 0, 14); 
        printf("Element %d is found at index %d\n", b[i], index); 
    }
    return (EXIT_SUCCESS); 
}

/* 
                =   n * fact(n-1)   ....    if n > 0 
    fact(n)

                =   1               ....    if n = 0 
*/ 

unsigned long long fact(unsigned long long n)
{
    if(n == 0)
        return (1); 
    return (n * fact(n-1)); 
}

/* 
    Summation of all elements in array. 
                    = A[N-1] + SIGMA(A, N-1)    ....    if N >= 1
    SIGMA(A, N)
                    = 0                         ....    if N = 0 
*/ 

unsigned long long sigma(int* pa, int N)
{
    if(N == 0)
        return (0); 
    return pa[N-1] + sigma(pa, N-1); 
}

/* 
    void print_array_in_reverse_r(int* pa, int n); 

                                =   print(A[N-1])
                                    PrintArrayReverse(A, N-1)     .... if N > 0
                                                               
    PrintArrayReverse(A, N)
                                = 
                                    print(END)                   .... if N==0 
*/ 
void print_array_reverse_r(int* pa, int N)
{
    if(N==0)
    {
        puts("END"); 
        return; 
    }
    printf("pa[%d]:%d\n", N-1, pa[N-1]); 
    print_array_reverse_r(pa, N-1); 
}

///////////////////////////////////////////////////

/*
f(a, N)

    a[N-1]

f(a, N-1)

0           8    9 
                a[9]

f(a, 9)
                a[8]
f(a, 8)
                a[7]
f(a, 7) 
                a[6]
f(a, 6)         
                a[5]
f(a, 5)
                a[4]
f(a, 4)
                a[3] 
f(a, 3)
                a[2]
f(a, 2)
                a[1]
f(a, 1)
                a[0]
f(a, 0)
    print("END")
*/ 

/* 
                        print(a[index])
                        PA(a, index+1, size)    ... if index < size 
PA(a, index, size)  = 
                        print(END)              ... if index == size 
*/ 

void print_array_r(int* pa, int index, int size)
{
    if(index == size)
    {
        puts("End"); 
        return; 
    }

    printf("a[%d]:%d\n", index, pa[index]); 
    print_array_r(pa, index+1, size); 
}

// INPLACE REVERSAL OF ARRAY : RECURSIVE VERSION  

/* 

                            =   swap(A[start], A[end])
Reverse(A, start, end)          Reverse(A, start+1, end-1)  ... if start < end 

                            =   Nothing                     ... if start >= end 
*/ 

void array_reverse_in_place_r(int* pa, int start_index, int end_index)
{
    int tmp; 
    if(start_index >= end_index)
        return; 
    tmp = pa[start_index]; 
    pa[start_index] = pa[end_index]; 
    pa[end_index] = tmp; 
    array_reverse_in_place_r(pa, start_index+1, end_index-1); 
}

////////////////////////////////////////////////////////////////////////

// DOUBLE LEVEL RECURSION 

//  find_max from array of size N. 
//  DEVELOP A RECURSIVE VERSION! 
/* 
                    =   max(
                                max(A, i, (i+j)/2), 
                                max(A, ((i+j)/2) + 1, j)
                            )    .... if i < j
    max(A, i, j)

                    =   A[i] ... if i == j 
*/ 

int find_max(int* pa, int start_index, int end_index)
{
    int mid_index; 
    int max_L; 
    int max_R; 
    if(start_index == end_index)
        return pa[start_index]; 
    mid_index = (start_index + end_index) / 2; 
    max_L = find_max(pa, start_index, mid_index); 
    max_R = find_max(pa, mid_index + 1, end_index); 
    if(max_L > max_R)
        return max_L; 
    return max_R;  
}

//  Let A be a sorted array
//  and let search_element be an element to be searched in an A. 
//  Develop a RECURSIVE SEARCH ALGORITHM FOR THE SAME 
//  Step 1: Develop mathematical recursive function 
//  Step 2: Convert into a program source 

/*                  
                                =  Search(  A, search_element, 
                                            start_index, (start_index + end_index)/2 - 1 )                                   
                                        ... if  si <= ei
                                                and 
                                                search_element < A[(si+ei)/2]
Search( 
        A, 
        search_element,         
                                =   Search( A,  search_element, 
        start_index,                       ((start_index+end_index)/2) + 1,  end_index)  
        end_index                            .....if 
        )                                               start_index <= end_index 
                                                        and 
                                                        search_element > A[(si+ei)/2]
                                           
                                =   (si+ei)/2    	if start_index <= end_index 
                                                        and 
                                                        A[(si+ei)/2] == search_element 
                                
                                =   -1              if start_index > end_index      
*/                                          

int search(int* pa, int search_element, int start_index, int end_index)
{
    int mid_index; 

    if(start_index <= end_index)
    {
        mid_index = (start_index + end_index) / 2; 
        if(search_element == pa[mid_index])
            return (mid_index); 
        else if(search_element < pa[mid_index])
            return search(pa, search_element, start_index, mid_index-1); 
        else if(search_element > pa[mid_index])
            return search(pa, search_element, mid_index+1, end_index); 
    }

    return (-1); 
}
                                
void insertion_sort(int* pa, int size)
{
    int i, j, key; 

    for(j = 1; j < size; ++j)
    {
        key = pa[j]; 
        i = j - 1; 
        while(i > -1 && pa[i] > key)
        {
            pa[i+1] = pa[i]; 
            i = i - 1; 
        }
        pa[i+1] = key; 
    }
}