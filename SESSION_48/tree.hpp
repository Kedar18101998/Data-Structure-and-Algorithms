#pragma once 

#include <iostream> 

class bst_node{
    friend class bst; 
    protected: 
        int data; 
        bst_node* left; 
        bst_node* right; 
        bst_node* parent;
        bst_node(int data): data(data), left(0), right(0), parent(0){
        } 
}; 

class bst{
    private: 
        bst_node* root; 
        std::size_t nr_elements; 
    public: 
        // create_bst()
        bst(){}
        // destroy_bst() 
        ~bst(){} 

        virtual void insert(int new_data); 
        virtual void remove(int r_data); 
        virtual void preorder() const; 
        virtual void postorder() const; 
        virtual void inorder() const; 
        virtual void find(int data) const; 
        virtual int max() const; 
        virtual int min() const; 
        virtual void inorder_successor(int* p_data); 
        virtual void inorder_predecessor(int* p_data); 
}; 

class rb_node : public bst_node{
    friend class rb_tree; 
    protected: 
        typedef enum color { RED = 0, BLACK=1} color_t; 
        color_t color; 
        rb_node() : bst_node(data) {
            color = BLACK; 
        } 

        rb_node(int data, rb_node* nil) : bst_node(data), color(RED){
            this->left = nil; 
            this->right = nil; 
            this->parent = nil; 
        }
}; 

class rb_tree : public bst {
    static rb_node* nil; 
    private: 
        rb_node* root; 
        std::size_t nr_elements; 
    public: 
        void insert(int new_data) override{

        }

        void remove(int r_data) override {

        }
}; 

rb_node* rb_tree::nil = new rb_node; 

class avl_node : public bst_node{
    friend class avl_tree; 
    protected: 
        avl_node(int data) : bst_node(data){} 
}; 

class avl_tree : public bst{
    private: 
        avl_node* root_node; 
        std::size_t nr_elements; 

    public: 
        void insert(int new_data) override{

        }

        void remove(int r_data) override{

        } 
}; 