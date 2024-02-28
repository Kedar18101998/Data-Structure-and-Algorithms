#include <stdio.h> 
#include <stdlib.h> 

struct Date
{
    int day; 
    int month; 
    int year; 
}; 

struct Date* create_date(int init_day, int init_month, int init_year); 

int main(void)
{
    struct Date* p_date = 0; 
    p_date = create_date(10, 2, 2020); 
    printf("%d-%d-%d\n", p_date->day, p_date->month, p_date->year); 
    free(p_date); 
    p_date = 0; 
}

struct Date* create_date(int init_day, int init_month, int init_year)
{
    struct Date* p_new_date = 0; 
    p_new_date = malloc(sizeof(struct Date)); 
    p_new_date->day = init_day; 
    p_new_date->month = init_month; 
    p_new_date->year = init_year; 

    return (p_new_date); 
}