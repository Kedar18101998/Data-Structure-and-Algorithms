#include <stdio.h> 
#include <stdlib.h> 

typedef long long int ssize_t; 

struct vector
{
    int* p_arr; 
    ssize_t N; 
};

/*  
    @input:     None

    @output:    Address of newly allocated instance of 
                struct vector 

    To allocate an instance of struct vector
*/
struct vector* create_vector(void); 

/* 
    @input-1: Pointer to a vector object to which 
              new element (@input-2) must be added 

    @input-2: An element to be added 

    @output: None

    Add new_element(@input-2) to a given vector(@input-1) 
*/
void push_back(struct vector* p_vector, int new_element); 

/* 
    @input-1: Pointer to a vetor to be shown. 
    
    @output: None 

    Show the elements in the array inside the given 
    vector(@input-1)
*/
void show(struct vector* p_vector); 

/* 
    @input-1: Pointer to a vector to be released 
    
    @output: None   
    
    Frees the array inside the given vector(@input-1) and 
    free the vector itself.  
*/
void release_vector(struct vector* p_vector); 