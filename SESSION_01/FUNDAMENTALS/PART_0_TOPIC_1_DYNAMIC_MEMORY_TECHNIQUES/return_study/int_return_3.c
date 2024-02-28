#include <stdio.h> 
#include <stdlib.h> 

void create_int_1(int** pp, int init_n); 
void create_int_2(int** pp, int init_n); 

int main(void)
{
    int* ptr1 = 0; 
    int* ptr2 = 0; 

    create_int_1(&ptr1, 100); 
    create_int_2(&ptr2, 200); 

    printf("*ptr1 = %d, *ptr2 = %d\n", *ptr1, *ptr2); 

    free(ptr1); 
    ptr1 = 0; 

    free(ptr2); 
    ptr2 = 0; 

    exit(0); 
}

void create_int_1(int** pp, int init_n)
{
    *pp = malloc(sizeof(int)); 
    if(*pp == 0) 
    {
        puts("Error in allocating memory"); 
        exit(-1); 
    }

    **pp = init_n; 
}

void create_int_2(int** pp, int init_n)
{
    int* p = 0; 

    p = malloc(sizeof(int)); 
    if(p == 0)
    {
        puts("Error in allocating memory"); 
        exit(-1); 
    }

    *p = init_n; 
    *pp = p; 
}

/* 
    T* create_T(init_data); // allocate: server, free: client 
    void create_T(T* pT, init_data); // allocate: client, free: client
    void create_T(T** pp_T, init_data); // allocate:server, free: client

*/ 

struct Date
{ 
    int day; 
    int month; 
    int year; 
}; 

struct Date* create_date_1(int init_day, int init_month, int init_year)
{
    static struct Date single_date; 

    single_date.day = init_day; 
    single_date.month = init_month; 
    single_date.year = init_year; 

    return (&single_date); 
}

void test_create_date_1(void)
{
    struct Date* p_date = NULL; 

    p_date = create_date_1(5, 6, 2022); 

    free(p_date); // segfault
}

void create_date_3(struct Date** pp_date, int init_day, int init_month, int init_year)
{
    static struct Date single_date; 

    single_date.day = init_day; 
    single_date.month = init_month; 
    single_date.year = init_year; 

    *pp_date = &single_date; 
}

void test_create_date_3(void)
{
    struct Date* p_date = NULL; 

    create_date_3(&p_date, 5, 6, 2022); 

    free(p_date); // segfault 
}