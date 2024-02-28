#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

struct Date
{
    int day; 
    int month; 
    int year; 
}; 

void create_date(struct Date** pp_date, int init_day, int init_month, int init_year); 

int main(void)
{
    struct Date* p_date = 0; 

    printf("Before create_date() the address in p_date = %llu\n", (unsigned long long int)p_date); 
    create_date(&p_date, 10, 4, 2021); 
    printf("After create_date() the address in p_date = %llu\n", (unsigned long long int)p_date); 
    printf("%d-%d-%d\n", p_date->day, p_date->month, p_date->year); 
    free(p_date); 
    p_date = 0; 

    return (0); 
}

void create_date(struct Date** pp_date, int init_day, int init_month, int init_year)
{
    *pp_date = malloc(sizeof(struct Date)); 
    assert(*pp_date != 0); 
    (*pp_date)->day = init_day; 
    (*pp_date)->month = init_month; 
    (*pp_date)->year = init_year; 
}

void create_date_alternate(struct Date** pp_date, int init_day, int init_month, int init_year)
{
    struct Date* p = 0; 

    p = malloc(sizeof(struct Date)); 
    assert(p != 0); 
    p->day = init_day; 
    p->month = init_month; 
    p->year = init_year; 

    *pp_date = p; 
}
