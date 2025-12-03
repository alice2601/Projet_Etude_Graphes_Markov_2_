#ifndef UNTITLED10_TARJAN_H
#define UNTITLED10_TARJAN_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct t_tarjan_vertex {
    int id;             // numéro du sommet dans le graphe
    int number;         // numérotation temporaire
    int numberacces;    // regrouper les sommets
    bool indic;         // sommet dans la pile ou pas
} t_tarjan_vertex;

typedef struct {
    char name[16];
    t_tarjan_vertex *head;
    int nb_sommets;
} t_classe;

typedef struct {
    t_classe *classes;
    int nb_classes;
} t_partition;

typedef struct {
    t_partition* partition;
    int** adj;
    int* nb_voisins;
} t_infos;

// fonctions
t_tarjan_vertex* creertableau(int taille);
void parcours(int a, t_tarjan_vertex* sommets, t_stack* pile, int* compteur, t_infos* infos);
t_partition* tarjan(int nb_sommets, int** adj, int* nb_voisins);

#endif //UNTITLED10_TARJAN_H