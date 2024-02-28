#include "graph_management.hpp" 

void hlist::generic_insert(hnode* beg, hnode* mid, hnode* end)
{
    mid->next = end; 
    mid->prev = beg; 
    beg->next = mid; 
    end->prev = mid; 
}

void hlist::generic_delete(hnode* delete_node)
{
    delete_node->prev->next = delete_node->next; 
    delete_node->next->prev = delete_node->prev; 
    delete delete_node; 
}

hnode* hlist::search_node(vertex_t v)
{
    for(hnode* ph_run = ph_head_node->next; 
        ph_run != ph_head_node; 
        ph_run = ph_run->next)
        if(ph_run->v == v)
            return (ph_run); 
    return 0; 
}

hlist::hlist()
{
    ph_head_node = new hnode(0); 
    ph_head_node->prev = ph_head_node; 
    ph_head_node->next = ph_head_node; 
}

void hlist::insert_end(vertex_t v)
{
    hlist::generic_insert(ph_head_node, new hnode(v), ph_head_node->next); 
}


void vlist::generic_insert(vnode* beg, vnode* mid, vnode* end)
{
    mid->next = end; 
    mid->prev = beg; 
    beg->next = mid; 
    end->prev = mid; 
}

void vlist::generic_delete(vnode* delete_node)
{
    delete_node->prev->next = delete_node->next; 
    delete_node->next->prev = delete_node->prev; 
    delete delete_node; 
}

vnode* vlist::search_node(vertex_t v)
{

}

vlist::vlist()
{

}

void vlist::insert_end(vertex_t t)
{

}

graph::graph()
{

} 

graph::~graph()
{

}

void graph::add_vertex(vertex_t v)
{

}

void graph::add_edge(vertex_t u, vertex_t v)
{

}

void graph::remove_vertex(vertex_t v)
{

}

void graph::remove_edge(vertex_t u, vertex_t v)
{

}

std::ostream& operator<<(std::ostream& os, const graph& g)
{

}