#include <stdio.h>
#include <stdlib.h> 

void* xmalloc(size_t size)
{
    void* p = NULL; 
    p = malloc(size); 
    if(p == NULL)
    {
        fprintf(stderr, "out of memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 
    p = calloc(nr_elements, size_per_element); 
    if(p == NULL)
    {
        fprintf(stderr, "out of memory\n"); 
        exit(EXIT_FAILURE); 
    }
    return (p); 
}

void* xrealloc(void* p_existing, size_t new_size_in_bytes)
{
    void* p = NULL; 
    p = realloc(p_existing, new_size_in_bytes); 
    if(p == NULL)
    {
        fprintf(stderr, "out of memory\n"); 
        exit(EXIT_FAILURE); 
    }
    return (p); 
}