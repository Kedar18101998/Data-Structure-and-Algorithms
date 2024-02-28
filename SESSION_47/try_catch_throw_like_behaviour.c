#include <stdio.h> 
#include <stdlib.h> 
#include <setjmp.h> 

#define SETJMP_SUCCESS              0 
#define NEGATIVE_NUMBER_EXCEPTION   1

void f1(int n); 
void f2(int n); 
void f3(int n); 

jmp_buf main_buffer; 

int main(void){
    static int a[10] = {10, 20, -1, 30, 40, -2, 50, 60, -3, 70}; 
    int i; 
    int ret; 

    ret = setjmp(main_buffer); 
    if(ret == SETJMP_SUCCESS)
        puts("Jump position is successfully set in main"); 
    else if(ret == NEGATIVE_NUMBER_EXCEPTION){
        puts("Negative number not allowed"); 
        goto next_iteration; 
    }

    i = 0; 
    while(i < 10){
        f1(a[i]); 
    next_iteration: 
        ++i; 
    }

    exit(EXIT_SUCCESS);
}   

void f1(int n){
    f2(n); 
}

void f2(int n){
    f3(n); 
}

void f3(int n){
    if(n < 0)
        longjmp(main_buffer, NEGATIVE_NUMBER_EXCEPTION); 
    printf("n = %d\n", n); 
}