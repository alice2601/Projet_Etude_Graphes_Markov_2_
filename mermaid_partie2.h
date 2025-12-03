//
// Created by khela on 15/11/2025.
//

#ifndef UNTITLED10_MERMAID_PARTIE2_H
#define UNTITLED10_MERMAID_PARTIE2_H


#include <stdbool.h>
#include "tarjan.h"
#include "fonction.h"

// Structure pour stocker un lien entre deux classes
typedef struct {
    int classe_depart;
    int classe_arrivee;
} t_link;

// Structure pour stocker tous les liens
typedef struct {
    t_link* links;
    int nb_links;
} t_link_array;



//Création d'un tableau vide
t_link_array* createLinkArray();


//Permet de vérifier si un lien est délà existant dans le tableau
bool linkExists(t_link_array* array, int depart, int arrivee);


//création d'un lien s'il n'existe pas
void addLink(t_link_array* array, int depart, int arrivee);


// Permet de créer un tableau indiquet la classe de chaque sommet du graphe
int* createSommetToClasseMapping(t_partition* partition, int nb_sommets);


//Permet de faire l'inventaire de tous les liens entre les classes
t_link_array* findClassLinks(t_partition* partition, t_list_adjacente* graphe);


//Permet de génerer le diagramme grâce aux partitions
void generateHasseMermaidFile(t_partition* partition, t_list_adjacente* graphe, const char* output_filename);


//Permet d'afficher les caractéristiques du graphe (transitoires/persistantes, états absorbants, irréductibilité)
void displayGraphCharacteristics(t_partition* partition, t_list_adjacente* graphe);

#endif //UNTITLED10_MERMAID_PARTIE2_H