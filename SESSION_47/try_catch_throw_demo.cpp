#include <iostream> 
#include <stdexcept> 

void f1(int n); 
void f2(int n); 
void f3(int n); 

int main(void){
    static int a[10] = {10, 20, -1, 30, 40, -2, 50, 60, -3, 70}; 

    for(int i = 0; i != 10; ++i){
        try{
            f1(a[i]); 
        }catch(std::runtime_error& e){
            std::cout << e.what() << std::endl; 
        }
    }

    return (0); 
}; 

void f1(int n){
    f2(n); 
}

void f2(int n){
    f3(n); 
}

void f3(int n){
    if(n < 0)
        throw std::runtime_error("Negative number not allowed"); 
    std::cout << "n=" << n << std::endl; 
}
