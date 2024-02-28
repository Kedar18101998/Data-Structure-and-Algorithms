/* Approach 1 */

/* 
    Keep adjecency list structure as it is with only one change 
    add is_visited flag in hnode 
*/

u -> v 
v -> u 

struct edge 
{
    int u, v; 
    double w; 
}; 

struct vector_edge
{
    struct edge** pp_edges; 
    size_t N; 
}; 

struct graph 
{
    vlist_t* pv_list; 
    vector_edge* p_edge_vector; 
    int nr_v; 
    int nr_e; 
}; 

