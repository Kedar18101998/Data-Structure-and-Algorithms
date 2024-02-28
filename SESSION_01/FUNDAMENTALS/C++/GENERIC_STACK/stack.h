#ifndef _STACK_H 
#define _STACK_H 

const int SUCCESS = 1; 
const int STACK_FULL = 2; 
const int STACK_EMPTY = 3; 

template <typename T> 
class stack{
private: 
	T* p_arr; 
	int top_index; 
	int max_size; 

public: 
	stack(int max_size){
		p_arr = new T[max_size]; 
		top_index = -1; 
		this->max_size = max_size; 
	}

	int push(T new_element){
		if(top_index + 1 == max_size)
			return STACK_FULL; 
		p_arr[++top_index] = new_element; 
		return SUCCESS; 
	}
	
	int pop(T* p_poped_element){
		if(top_index == -1)
			return STACK_EMPTY; 
		*p_poped_element = p_arr[top_index--]; 
		return SUCCESS; 
	} 
	
	int top(T* p_top_element){
		if(top_index == -1)
			return STACK_EMPTY; 
		*p_top_element = p_arr[top_index]; 
		return SUCCESS; 
	}
	
	bool is_empty()const{
		return (top_index == -1); 
	}
	
	~stack(){
		delete[] p_arr; 
	}
}; 

#endif 
