/* Headers */ 
#include <stdio.h>
#include <stdlib.h> 

/* Symbolic constants */ 
#define SUCCESS 1 

/* Information structure layout */ 
struct vector{
	int* p_arr; 
	size_t size; 
}; 

/* Interface functions declaration */ 
struct vector* create_vector(void); 
int push_back(struct vector* p_vec, int new_element); 
void destroy_vector(struct vector* p_vec);

/* Auxillary function declaration */  
void* xcalloc(size_t nmem, size_t size_per_mem); 

int main(void){
	struct vector* p_vec = NULL; 
	int i; 
	int ret; 

	p_vec = create_vector(); 
	for(i = 0; i < 10; ++i){
		ret = push_back(p_vec, (i+1) * 10); 
		if(ret != SUCCESS){
			fprintf(stderr, "Unexpected error\n"); 
			exit(EXIT_FAILURE); 
		}
	} 

	for(i = 0; i < p_vec->size; ++i)
		printf("p_vec->p_arr[%d]:%d\n", i, p_vec->p_arr[i]); 

	destroy_vector(p_vec); 
	p_vec = NULL; 

	return (EXIT_SUCCESS); 
}

/* Interface function definition */ 
struct vector* create_vector(void){
	struct vector* p_vec = NULL; 
	p_vec = xcalloc(1, sizeof(struct vector)); 
	p_vec->p_arr = NULL; 
	p_vec->size = 0; 
	return (p_vec); 
} 

int push_back(struct vector* p_vec, int new_element){
	p_vec->size = p_vec->size + 1; 
	p_vec->p_arr = realloc(p_vec->p_arr, p_vec->size * sizeof(int)); 
	p_vec->p_arr[p_vec->size - 1] = new_element; 
	return (SUCCESS); 
}

void destroy_vector(struct vector* p_vec){
	free(p_vec->p_arr); 
	free(p_vec); 
}

/* Auxillary function definition */ 
void* xcalloc(size_t nmem, size_t size_per_mem){
	void* p = NULL; 

	p = calloc(nmem, size_per_mem);
	if(p == NULL){
		fprintf(stderr, "calloc:fatal:out of memory\n"); 
		exit(EXIT_FAILURE); 
	}

	return (p); 
} 
