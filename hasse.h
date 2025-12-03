
#ifndef __HASSE_H__
#define __HASSE_H__

#include "mermaid_partie2.h"
#include "tarjan.h"
#include "fonction.h"
//void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

void removeTransitiveLinks(t_link_array *p_link_array);
void generateMermaidSimplified(t_partition* partition, t_list_adjacente* graphe, const char* output_filename);
#endif
