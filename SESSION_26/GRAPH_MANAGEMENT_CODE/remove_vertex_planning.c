int remove_vertex(graph_t* g, vertex_t vd)
{
    vnode_t* pv_node = NULL; 
    hnode_t* ph_run = NULL; 

    pv_node = v_search_node(g->pv_list, vd); 
    if(pv_node == NULL)
        return (G_INVALID_VERTEX); 

    /* Usual traversal loop */
    for(ph_run = pv_run->ph_list; ph_run != pv_run; ph_run = ph_run->next)
    {
        /* Will not work if ph_run is invalidated in the body */
    }

    /* Alternative */

    hnode_t* ph_run = NULL; 
    hnode_t* ph_run_next = NULL; 

    for(ph_run = pv_run->ph_list; ph_run != pv_run; ph_run = ph_run_next)
    {
        ph_run_next = ph_run->next; 
        
        1) ph_run->v -> Locate in g->pv_list
        2) Delete the entry of vd in hlist of ph_run->v 
        3) free(ph_run)
        4) g->nr_elements--
    }

    free(pv_node->ph_list); 
    v_generic_delete(pv_node); 
    g->nr_vertices--; 

    return (SUCCESS); 
}

