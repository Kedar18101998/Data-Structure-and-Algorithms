#include <stdio.h> 
#include <stdlib.h> 

#define OFFSET_OF(T, mem)  ((unsigned long long int)&((T*)0)->mem)


struct A 
{
    int a;      // 0 
    char b;     // 4 
    float c;    // 5 
}; 

void print_instance(float *pf); 

int main(void)
{
    struct A a1 = {10, 'A', 1.1}, a2 = {20, 'B', 2.2}, a3 = {30, 'C', 3.3}; 

    printf("OFFSET_OF(struct A, a)=%llu\n", OFFSET_OF(struct A, a)); 
    printf("OFFSET_OF(struct A, b)=%llu\n", OFFSET_OF(struct A, b)); 
    printf("OFFSET_OF(struct A, c)=%llu\n", OFFSET_OF(struct A, c)); 

    print_instance(&a1.c); 
    print_instance(&a2.c); 
    print_instance(&a3.c); 

    return (0); 
}

/* 
    Pre-condition: 
        the actual paramter in pf must an address of float member named 'c' 
        in one of the instances of struct A. 
    Post-condition: 
        To print all members of struct A instance whose 'c' member address 
        is in pf. 
*/
void print_instance(float* pf)
{

}

/* 
    Offset of struct member. 
        Distance of member in bytes from starting address of structure instance 
        is called as byte-offset or simply offset of a structure member 

    offset of first member = 0 
    offset of kth member = sum of sizes of member 1 to member k-1 (if k > 1)

    ALIGNMENT PURPOSE -> PADDING 
                 [   ]
    [          c][   ]b
    [                ]a 
------------------------------------------------------   
    [                ]c 
    [------------[   ]b 
    [                ]
--------------------------------------------------------
Compiler computes the offsets based on structure definition 
struct definition source code -> INPUT 

Lexical analysis 
Parsing 

Data type sizes = Compiler decision 
Padding for alignment = Underlying processor architecture 
(Padding requirement = ABI = Application binary interface )

As an application developer in C(!= not as compiler writer of C)
can you write a C code to compute an offset of any member of any 
structure provided its definition is given to you? 

Yes. 

Offset: Def 2: Offset of member of a structure = address that member 
would have got if compiler had aligned base address of structure with 
address 0. 

struct T* pT = 0; 

struct T* pT = (void*)0; 

    &(pT->mem) == offset of mem within struct T. 

     &((struct T*)0 -> mem)

    (unsigned long long int)&((struct T*)0)->mem)

#define OFFSET_OF(T, mem)  ((unsigned long long int)&((T*)0)->mem)
*/