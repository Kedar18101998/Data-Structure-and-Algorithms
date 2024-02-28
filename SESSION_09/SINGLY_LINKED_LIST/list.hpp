class node 
{
    friend class list; 
    private: 
        int data; 
        node* prev; 
        node* next; 
        node(int _data) : data(_data), prev(0), next(0)
        {

        }
}; 

class list 
{
    private: 
        node* p_head_node; 
        node* search_node(int s_data); 
        void search_node(int s_data, node** pp_node, 
                                node** pp_prev_node); 
    public: 
        list() : p_head_node(new node(-1)) {} 
        ~list() { /* logic of destroy node */ }

        void insert_end(int new_data); 
}; 

int main(void)
{
    list L; 

    L.insert_end(100); 

    return (0); 
}