#ifndef _LIST_H 
#define _LIST_H 

const int SUCCESS = 1; 
const int LIST_DATA_NOT_FOUND = 2; 
const int LIST_EMPTY = 3; 

typedef int ret_t; 
typedef int len_t; 

template <typename T>
class list; 

template <typename T>
class node{
	friend std::ostream& operator<<(std::ostream& os, list<T>& list_object); 
	friend class list<T>; 
	friend class list<T>::iterator; 
private: 
	T data; 
	node* prev; 
	node* next; 
	node(T new_data) : data(new_data), prev(0), next(0) {} 
	node() : prev(0), next(0) {} 
};  

template <typename T> 
class list{
private: 
	node<T>* p_head_node; 

	static void generic_insert(node<T>* p_beg, node<T>* p_mid, node<T>* p_end){
		p_mid->next = p_end; 
		p_mid->prev = p_beg; 
		p_beg->next = p_mid; 
		p_end->prev = p_mid; 
	}

	static void genreic_delete(node<T>* p_delete_node){
		p_delete_node->prev->next = p_delete_node->next; 
		p_delete_node->next->prev = p_delete_node->prev; 
		delete p_delete_node; 
	}

	node<T>* search_node(T s_data){
		for(node<T>* p_run = p_head_node->next; p_run != p_head_node; p_run = p_run->next)
			if(p_run->data == s_data)
				return p_run; 
		return (0); 
	}

public: 

	class iterator{
		private: 
			node<T>* p_node; 
		public: 
			iterator(node<T>* p_init_node = 0) : p_node(p_init_node) {} 

			iterator& operator++(){
				p_node = p_node->next; 
				return *this; 
			}

			iterator& operator--(){
				p_node = p_node->prev; 
				return *this; 
			}

			iterator& operator++(int){
				p_node = p_node->next; 
				return *this; 
			}

			iterator& operator--(int){
				p_node = p_node->prev; 
				return *this; 
			}

			T operator*(){
				return p_node->data; 
			}

			bool operator==(iterator& other){
				return p_node == other.p_node; 
			}

			bool operator!=(iterator& other){
				return p_node != other.p_node; 
			}
	}; 
	
	// constructor
	list(){
		p_head_node = new node<T>; 
		p_head_node->prev = p_head_node; 
		p_head_node->next = p_head_node; 
	}

	// destructor 
	~list(){
		node<T>* p_run; 
		node<T>* p_run_next; 
		for(p_run = p_head_node->next; p_run != p_head_node; p_run = p_run_next){
			p_run_next = p_run->next; 
			delete p_run; 
		}
	}

	ret_t insert_beg(T new_data){
		generic_insert(p_head_node, new node<T>(new_data), p_head_node->next);
		return SUCCESS; 
	}

	ret_t insert_end(T new_data){
		generic_insert(p_head_node->prev, new node<T>(new_data), p_head_node); 
		return SUCCESS; 
	}

	ret_t insert_after(T e_data, T new_data){
		node<T>* e_node = search_node(e_data); 
		if(e_node == 0)
			return LIST_DATA_NOT_FOUND; 
		generic_insert(e_node, new node<T>(new_data), e_node->next); 
		return SUCCESS; 
	}

	ret_t insert_before(T e_data, T new_data){
		node<T>* e_node = search_node(e_data); 
		if(e_node == 0)
			return LIST_DATA_NOT_FOUND; 
		generic_insert(e_node->prev, new node<T>(new_data), e_node); 
		return SUCCESS; 
	}

	ret_t remove_beg(){
		if(p_head_node == p_head_node->next && p_head_node == p_head_node->prev)
			return LIST_EMPTY; 
		genreic_delete(p_head_node->next); 
		return SUCCESS; 
	}

	ret_t remove_end(){
		if(p_head_node == p_head_node->next && p_head_node == p_head_node->prev)
			return LIST_EMPTY; 
		genreic_delete(p_head_node->prev); 
		return SUCCESS; 
	}

	ret_t remove_data(T d_data){
		node<T>* d_node = search_node(d_data); 
		if(d_node == 0)
			return LIST_DATA_NOT_FOUND; 
		genreic_delete(d_node); 
		return SUCCESS; 
	}

	bool find(T f_data)const{
		node<T>* f_node = search_node(f_data); 
		if(f_node == 0)
			return false; 
		return true; 
	}

	bool is_empty()const{
		return (p_head_node == p_head_node->prev && p_head_node == p_head_node->next); 
	}

	len_t length()const{
		len_t len = 0; 
		node<T>* p_run = 0; 
		for(p_run = p_head_node->next; p_run != p_head_node; p_run = p_run->next)
			++len; 
		return len; 
	}

	friend std::ostream& operator<<(std::ostream& os, list<T>& list_object){
		node<T>* p_run; 
		std::cout << "[BEG]<->"; 
		for(p_run = list_object.p_head_node->next; p_run != list_object.p_head_node; p_run = p_run->next){
			std::cout << "[" << p_run->data << "]<->"; 
		}
		std::cout << "[END]" << std::endl; 
		return os; 
	}

	iterator begin(){
		return iterator(p_head_node->next); 
	}

	iterator end(){
		return iterator(p_head_node); 
	}
}; 


#endif 