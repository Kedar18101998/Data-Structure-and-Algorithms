int* get_int(int init_n)
{
    int n = init_n; 

    return (&n);    // dangling pointer. very dangerous 
}
//////////////////////////////////////
int* get_int(int init_n)
{
    static int n;  
    n = init_n; 
    return (&n); 
}
//////////////////////////////////////
//1 
int* get_int(int init_n)
{
    int* p = malloc(sizeof(int)); 
    assert(p); 
    *p = init_n; 
    return (p); 
}
/////////////////////////////////////
//2 
void get_int(int* p, int init_n)
{
    *p = init_n; 
}

void test(void)
{
    int n; 
    int* p = NULL; 

    get_int(&n, 400); 
    p = malloc(sizeof(int)); 
    assert(p); 
    get_int(p, 6500); 
    free(p); 
    p = NULL; 
}
/////////////////////////////////////
// 3 
void get_int(int** pp_int, int init_data)
{
    *pp_int = malloc(sizeof(int)); 
    assert(*pp_int != NULL);
    **pp_int = init_data; 
}

void test(void)
{
    int* p = NULL; 
    get_int(&p, 100); 
    *p = 200; 
    free(p); 
    p = NULL; 
}
/////////////////////////////

// dynamic memory management 
// CALLBACK function technique -> event driven programming 
// re-entrant functions 
// reentrancy of kind 1 
    // one function simultaneously opened in more than one stacks 
    // belonging to same process (aka multi-threading)

//  reentrancy of kind 2 
    //  one function is simultaneously opened in same stack 
    //      (i) recursion (trivial case)
    //      (ii) callback function 
    //              when an event occurs, one instance of callback function 
    //              is opened and while that instance returns, event reoccurs 
    //              (it is not masked), and the current instance of callback 
    //              is then suspended and new instance is opened 
    //              (MOST NOTORIOUS CASE TO HANDLE)