#include <stdexcept>

namespace dsa 
{
    typedef int data_t; 
    namespace trees
    {
        class bst_node
        {
            friend class bst; 
            private: 
                data_t data; 
                bst_node* left; 
                bst_node* right; 
                bst_node* parent; 
        }; 

        class bst 
        {
            private: 
                bst_node* root_node; 
                

            public: 
                // create_bst()
                bst(); 
                // destroy_bst() 
                ~bst(); 
                // no copy constuctor 
                bst(const bst& other) = delete; 
                // no move semantic 
                bst(const bst&& other) = delete; 
                // no copy assignment 
                bst& operator=(const bst& other) = delete; 
                // no move assignment 
                bst& operator=(const bst&& other) = delete; 

                void insert(data_t new_data); 
                void preoder(); 
                void inorder(); 
                void postorder(); 
                void preorder_nrc(); 
                void inorder_nrc(); 
                void postorder_nrc(); 
                bool search(data_t e_data); 
                void max(data_t* p_max_data); 
                void min(data_t* p_min_data); 
                void inorder_successor(data_t e_data, data_t* p_succ_data); 
                void inorder_predecessor(data_t e_data, data_t* p_pred_data); 
                void remove(data_t r_data); 

                class preorder_iterator 
                {

                }; 

                class inorder_iterator 
                {

                }; 

                class postorder_iterator
                {

                }; 
        }; 

        class bst_data_not_found : public std::runtime_error
        {

        }; 

        class bst_empty : public std::runtime_error 
        {

        }; 

        class bst_no_successor : public std::runtime_error 
        { 

        }; 

        class bst_no_predecessor : public std::runtime_error 
        {

        };
    }
}