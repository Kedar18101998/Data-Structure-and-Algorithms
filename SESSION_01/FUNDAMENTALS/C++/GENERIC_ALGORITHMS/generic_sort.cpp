#include <iostream>

void insertion_sort_ng(int* p_arr, size_t n){
	int i, j; 
	int key; 
	for(j = 1; i < n; ++j){
		key = p_arr[j]; 
		i = j - 1; 

		while(i > -1 && p_arr[i] > key){
			p_arr[i+1] = p_arr[i]; 
			i = i - 1; 
		}

		p_arr[i+1] = key; 
	}
}

// T is type variable, template parameter
// This should be followed by function definition OR 
// class definition. If followed by function definition then 
// function template is being used OR if followed by class definition 
// then class template is being used.

// scope (effect or influence) of this lasts upto the next function 
// or class block  
template <typename T> 
void insertion_sort(T* p_arr, size_t n){
	int i, j; 
	T key; 

	for(j = 1; j < n; ++j){
		key = p_arr[j]; // C1: overload assignment operator of type T will come into picture of 
						// T is a user defined data type, otherwise should T be a builtin data 
						// type, compiler would know how to interpret this assignment 
		i = j - 1; 
		while(i > -1 && p_arr[i] > key){ 	// C2: if T is a user defined data type then it must 
											// container overload function of '>' operator 
											// should T be a built in data type, language would know 
											// how to make that comparison
			p_arr[i+1] = p_arr[i]; 			// C1 is applicable here as well 
			i = i - 1; 
		}

		p_arr[i+1] = key;					// C2 is applicable here as well
	}
}

// 1. insertion_sort is NOT A FUNCTION. 
// 2. insertion_sort is a FUNCTION TEMPLATE. 

#define SIZE 5

int main(){
	int A[SIZE] = {10, 4, 100, 25, 3}; 
	float B[SIZE] = {4.3, 12.34, 54.32, 1.1, 0.5}; 

	std::cout << "Before sort:Showing A:" << std::endl; 
	for(int i = 0; i != SIZE; ++i)
		std::cout << "A[" << i << "]:" << A[i] << std::endl; 

	std::cout << "Before sort:Showing B:" << std::endl; 
	for(int i = 0; i != SIZE; ++i)
		std::cout << "B[" << i << "]:" << B[i] << std::endl; 

	insertion_sort<int>(A, SIZE); 
	insertion_sort<float>(B, SIZE); 

	insertion_sort(A, SIZE); 
	insertion_sort(B, SIZE); 

	std::cout << "After sort:Showing A:" << std::endl; 
	for(int i = 0; i != SIZE; ++i)
		std::cout << "A[" << i << "]:" << A[i] << std::endl; 

	std::cout << "After sort:Showing B:" << std::endl; 
	for(int i = 0; i != SIZE; ++i)
		std::cout << "B[" << i << "]:" << B[i] << std::endl; 

	return 0; 
}

// template <typename T> ---> Template parameter list 
// void insertion_sort(T* p_arr, size_t n) { ..... }

// insertion_sort<int>
// 					^
// 					|
// 					| 
//					_______ TEMPLATE ARGUMENT

// insertion_sort<int> -- When function template is used by supplying 
// a template argument then an actual (eligible for compilation)
// function is created using it. This act of C++ compiler of generating 
// a function from function template definition and template argument 
// is known as TEMPLATE INSTANTIATION. 

// On Line 70, 71, function template is used AS IF IT WERE AN ACTUAL FUNCTION 
// But it is not the case. C++ compiler is aware that insertion_sort is not 
// a callable function but is a function template. By examining the types of 
// actual parameter, C++ compiler deduces the type WHICH SHOULD REPLACE T 
// in template definition. Compiler will instantiate template based on this 
// deduced type and then generate an actual call to function. 

// This act of C++ compiler to deduce the a type of template parameter 
// BASED actual parameters (i.e. to deduce the type of template argument)
// is known as 'TEMPLATE ARGUMENT DEDUCTION'

// After TEMPLATE ARGUMENT DEDUCTION, FUNCTION TEMPLATE IS READY FOR 
// TEMPLATE INSTANTIATION and AFTER INSTANTIATION the generated function 
// IS READY FOR CALL. 