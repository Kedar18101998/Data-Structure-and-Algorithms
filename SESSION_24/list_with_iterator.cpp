#include <iostream> 

class node 
{
    friend class list; 
    friend std::ostream& operator<<(std::ostream& os, const list& L); 
    private: 
        int data; 
        node* prev; 
        node* next; 
        node(int new_data=0) : data(new_data), prev(0), next(0)
        {

        }
}; 

class list 
{
    private: 
        node* head_node; 

        static void g_insert(node* beg, node* mid, node* end)
        {
            mid->next = end; 
            mid->prev = beg; 
            beg->next = mid; 
            end->prev = mid; 
        }

        static void g_delete(node* p_node)
        {
            p_node->prev->next = p_node->next; 
            p_node->next->prev = p_node->prev; 
            delete p_node; 
        }

        node* search_node(int data)
        {
            for(node* p_run = this->head_node->next; 
                p_run != this->head_node; 
                p_run = p_run->next)
                if(p_run->data == data)
                    return p_run; 

            return 0; 
        }

    public: 

        list() : head_node(new node(-1))
        {
            head_node->prev = head_node; 
            head_node->next = head_node; 
        }

        ~list()
        {
            node* run, *run_next; 
            for(run = this->head_node->next; 
                run != this->head_node; 
                run = run_next)
            {
                run_next = run->next; 
                delete run; 
            }

            delete head_node; 
            head_node = 0; 
        }

        void insert_start(int new_data)
        {
            g_insert(head_node, new node(new_data), head_node->next); 
        }

        void insert_end(int new_data)
        {
            g_insert(head_node->prev, new node(new_data), head_node); 
        }

        friend std::ostream& operator<<(std::ostream& os, const list& L); 

        class iterator 
        {
            private: 
                node* p_node; 
            
            public: 
                iterator(node* _p_node=0) : p_node(_p_node) {}

                iterator operator++()
                {
                    p_node = p_node->next; 
                    return *this; 
                }

                iterator operator--()
                {
                    p_node = p_node->prev; 
                    return *this; 
                }

                iterator operator++(int)
                {
                    iterator tmp_iter(this->p_node); 
                    p_node = p_node->next; 
                    return tmp_iter; 
                }

                iterator operator--(int)
                {
                    iterator tmp_iter(this->p_node); 
                    p_node = p_node->prev; 
                    return tmp_iter; 
                }

                int operator*()
                {
                    return this->p_node->data; 
                }

                bool operator==(const iterator& other)
                {
                    return this->p_node == other.p_node; 
                }

                bool operator!=(const iterator& other)
                {
                    return this->p_node != other.p_node; 
                }
        }; 

        iterator begin() 
        {
            return iterator(this->head_node->next); 
        }

        iterator end()
        {
            return iterator(this->head_node); 
        }
}; 

std::ostream& operator<<(std::ostream& os, const list& L)
{
    os << "[START]<->"; 
    for(node* run = L.head_node->next; 
        run != L.head_node; 
        run = run->next)
        os << "[" << run->data << "]<->"; 
    os << "[END]" << std::endl; 

    return os; 
}

int main(void)
{
    list L1; 

    for(int data = 0; data <= 100; data += 10)
        L1.insert_end(data); 

    std::cout << "L1:" << L1; 

    // forward r/w iterator 
    for(
        list::iterator iter = L1.begin(); 
        iter != L1.end(); 
        ++iter
    )
        std::cout << "*iter=" << *iter << std::endl; 

    return 0; 
}

/* 
    // forward read only 
    // reverse read write 
    // reverse read only 

    std::list<T>::iterator 
    std::list<T>::reverse_iterator (rbegin(), rend())
    std::list<T>::const_iterator (cbegin(), cend())
    std::list<T>::const_reverse_iterator (crbegin(), crend())
*/

/* 
    f_handle = open("abc.txt", "r") #_io.TextIOWrapper

    for line in f_handle: 
        # do something with line 

    class FileIterator 
    {
        class line; 

    public: 
        line begin(); 
        line end(); 
    }; 

    class line 
    {
        private: 
            std::string s; 
        public: 
            int get_word_count(); 

    }; 

    void test(void)
    {
        FileIterator f_iter("abc.txt"); 
        for(line L = f_iter.begin(); 
            L != f_iter.end(); 
            ++L)
            L.get_word_count(); 
    } 
*/

