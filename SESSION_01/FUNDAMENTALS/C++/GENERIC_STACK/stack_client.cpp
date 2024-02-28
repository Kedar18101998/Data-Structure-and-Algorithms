#include <iostream>
#include <cassert>
#include "stack.h"

const int TRUE = 1; 

int main(){
	int i_data; 
	char c_data; 
	int ret; 
	int i_top_element, i_pop_element; 
	char c_top_element, c_pop_element; 
	
	stack<int> i_stack(15); 
	stack<char> c_stack(5); 

	assert(i_stack.is_empty() == true); 
	assert(c_stack.is_empty() == true); 

	i_data = 0; 
	while(TRUE){
		ret = i_stack.push(i_data++); 
		if(ret == STACK_FULL)
			break; 
	}

	c_data = 'A'; 
	while(TRUE){
		ret = c_stack.push(c_data++); 
		if(ret == STACK_FULL)
			break;
	}

	ret = i_stack.top(&i_top_element); 
	assert(ret == SUCCESS); 
	ret = c_stack.top(&c_top_element); 
	assert(ret == SUCCESS); 

	std::cout << "i_top_element:" << i_top_element << std::endl
				<< "c_top_element:" << c_top_element << std::endl; 

	while(i_stack.pop(&i_pop_element) != STACK_EMPTY)
		std::cout << "i_poped_element:" << i_pop_element << std::endl; 

	while(c_stack.pop(&c_pop_element) != STACK_EMPTY)
		std::cout << "c_pop_element:" << c_pop_element << std::endl; 

	return 0; 
}