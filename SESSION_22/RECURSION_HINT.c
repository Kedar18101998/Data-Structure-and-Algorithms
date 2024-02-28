void f(void)
{
    static int i=0; 
    printf("Stack frame #%dd\n", ++i); 
    f(); 
}

void f(void)
{
    static int i=0; 
    f(); 
    printf("Stack frame #%d\n", ++i); 
}

//////////////////////////////////////////////

void f(int N)
{
    printf("N = %d\n", N); 
    f(N-1); 
}

void f(int N)
{
    printf("N = %d\n", N); 
    f(N+1); 
}

void f(int N)
{
    if(N == 0)
        return; 
    printf("N = %d\n", N); 
    f(N-1); 
}

void f(int N)
{
    if(N == INT_MAX)
        return; 
    printf("N = %d\n", N); 
    f(N+1); 
}