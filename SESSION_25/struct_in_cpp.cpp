struct Test 
{
    private: 
        int n; 
    public: 
        int get_n() { return n; }
}; 

int main(void)
{
    struct Test t; 
    t.n = 500; 
    return 0; 
}