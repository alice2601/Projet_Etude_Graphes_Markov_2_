//
// Created by khela on 14/11/2025.
//

#ifndef UNTITLED10_TARJAN_H
#define UNTITLED10_TARJAN_H



//
// Created by alice on 12/11/2025.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"  // inclut t_stack et les fonctions de pile

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

typedef struct { //pour avoir que les 5 ou 6 paramètres dans le parcours et donc simplifier
    t_partition* partition; // la partition
    int** adj;              // voisins de chaque sommet
    int* nb_voisins;        // nombre de voisins pour chaque sommet
} t_infos;

// fonctions
t_tarjan_vertex* tableau(int taille);
void parcours(int a, t_tarjan_vertex* sommets, t_stack* pile, int* compteur, t_infos* infos);





#endif //UNTITLED10_TARJAN_H