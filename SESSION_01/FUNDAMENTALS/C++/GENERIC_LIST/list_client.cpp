#include <iostream>
#include <cassert>
#include "list.h"

int main(){
	list<int> iList; 
	int data; 

	list<char> cList; 
	char c_data; 

	for(data = 0; data < 5; ++data)
		assert(iList.insert_beg(data) == SUCCESS); 

	std::cout << iList; 

	for(c_data = 'A'; c_data != 'F'; ++c_data)
		assert(cList.insert_beg(c_data) == SUCCESS); 

	std::cout << cList; 

	std::cout << "Iterating over iList:" << std::endl; 
	for(list<int>::iterator iter = iList.begin(); iter != iList.end(); ++iter)
		std::cout << "*iter:" << *iter << std::endl; 

	std::cout << "Iterating over cList:" << std::endl; 
	for(list<char>::iterator iter = cList.begin(); iter != cList.end(); ++iter)
		std::cout << "*iter:" << *iter << std::endl; 

	return 0; 
}