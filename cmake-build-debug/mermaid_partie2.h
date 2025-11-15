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

/**
 * Crée un tableau vide de liens
 */
t_link_array* createLinkArray();

/**
 * Vérifie si un lien existe déjà dans le tableau
 */
bool linkExists(t_link_array* array, int depart, int arrivee);

/**
 * Ajoute un lien au tableau s'il n'existe pas déjà
 */
void addLink(t_link_array* array, int depart, int arrivee);

/**
 * Crée un tableau qui indique pour chaque sommet du graphe
 * la classe à laquelle il appartient
 */
int* createSommetToClasseMapping(t_partition* partition, int nb_sommets);

/**
 * Recense tous les liens entre classes selon l'algorithme du sujet
 */
t_link_array* findClassLinks(t_partition* partition, t_list_adjacente* graphe);

/**
 * Génère le diagramme de Hasse au format Mermaid
 * à partir d'une partition et du graphe original
 */
void generateHasseMermaidFile(t_partition* partition, t_list_adjacente* graphe, const char* output_filename);

/**
 * Affiche les caractéristiques du graphe (Étape 3)
 * - Classes transitoires/persistantes
 * - États absorbants
 * - Irréductibilité
 */
void displayGraphCharacteristics(t_partition* partition, t_list_adjacente* graphe);

#endif //UNTITLED10_MERMAID_PARTIE2_H