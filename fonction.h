//
// Created by khela on 27/10/2025.
//

#ifndef PROJET_S3_FONCTION_H
#define PROJET_S3_FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//type cellule
typedef struct s_cell {
    int sommet_arrive;
    float proba;
    struct s_cell* next;
} t_cell;


//type liste
typedef struct s_list {
    t_cell* head;
} t_list;


//type liste d'adjacente
typedef struct s_list_adjacente {
    int taille;
    t_list *tab;
}t_list_adjacente;



//créer une cellule

t_cell *createCell(int sommet_arrive, float proba);


//créer une liste vide
t_list* createEmptyList();


//ajoute une cellule à la liste
t_list* addCell(t_list *ptr_list, int sommet_arrive, float proba);


//Affiche une liste
void displayList(t_list* l);


//Créer une liste adjacente vide
t_list_adjacente* create_Adj_Empty_List(int taille);


//Affiche une liste d'adjacense
void displayAdjacente(t_list_adjacente* myListeAdja);



t_list_adjacente* readGraph(const char *filename);



//vérifier si on a bien un graphe de Markov
void verifiersigraphMarkov(t_list_adjacente* mongraphe);


//Transforme les sommets (des nombres) en chiffres
char* getId(int num);


//Génère un fichier mermaid
void generateMermaidFile(t_list_adjacente* graphe, const char* output_filename);


#endif //PROJET_S3_FONCTION_H