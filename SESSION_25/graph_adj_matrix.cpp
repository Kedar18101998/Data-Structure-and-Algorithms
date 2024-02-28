#include <iostream> 

class graph
{
    private: 
        int* pg; 
        int nr_V; 
        int nr_E; 

    public: 
        graph(int V)
        {
            // create_graph(); 
        }

        ~graph()
        {
            // release graph
        }

        int add_edge(int v_start, int v_end)
        {
            // add_edge()
        }

        int remove_edge(int v_start, int v_end)
        {
            // remove_edge()
        }

        friend std::ostream& operator<<(std::ostream& os, const graph& g); 
}; 

std::ostream& operator<<(std::ostream& os, const graph& g)
{
    // show_graph() 
}

void test_1(void); 
void test_2(void); 

int main(void)
{
    test_1(); 
    test_2(); 

    return (0); 
}

void test_1(void)
{
    graph g(5); 

    g.add_edge(1, 4); 
    g.add_edge(0, 1); 
    g.add_edge(1, 2); 
    g.add_edge(2, 3); 
    g.add_edge(3, 4); 

    std::cout << g; 
}

void test_2(void)
{
    graph* pg = new graph(5); 

    pg->add_edge(0, 1); 
    pg->add_edge(1, 2);
    pg->add_edge(2, 3);
    pg->add_edge(3, 4);
    
    std::cout << *pg; 

    delete pg; 
    pg = 0; 
}
