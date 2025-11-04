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




t_cell *createCell(int sommet_arrive, float proba);

t_list* createEmptyList();

t_list* addCell(t_list *ptr_list, int sommet_arrive, float proba);

void displayList(t_list* l);

t_list_adjacente* create_Adj_Empty_List(int taille);

void displayAdjacente(t_list_adjacente* myListeAdja);

t_list_adjacente* readGraph(const char *filename);

void verifiersigraphMarkov(t_list_adjacente* mongraphe);

char* getId(int num);

void generateMermaidFile(t_list_adjacente* graphe, const char* output_filename);


#endif //PROJET_S3_FONCTION_H
