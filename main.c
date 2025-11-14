#include <stdio.h>

#include "cmake-build-debug/fonction.h"
#include "cmake-build-debug/stack.h"
#include "cmake-build-debug/tarjan.h"



int main() {
    printf("Creation manuelle d un graphe : \n");

    t_list_adjacente* myListADJ=create_Adj_Empty_List(2);

    addCell(&myListADJ->tab[0], 4, 0.8f);
    addCell(&myListADJ->tab[1], 1, 0.2f);

    displayAdjacente((myListADJ));

    printf("Voici le graphe depuis le fichier 'graph.txt' : \n");

    t_list_adjacente* monGraphe = readGraph("graph.txt");

    // On affiche le contenu du graphe pour vérifier
    printf("Voici le graphe lu depuis le fichier :\n");
    displayAdjacente(monGraphe);

    displayAdjacente(monGraphe);

    printf("Vérifions si le graphique est un graphique Markov : \n");
    verifiersigraphMarkov(monGraphe);

    printf("Generation du fichier Mermaid : \n");
    generateMermaidFile(monGraphe, "graphe_visualisation.mmd");

    if (monGraphe != NULL) {
        printf("Fichier 'graphe_visualisation.mmd' genere avec succes !\n");
        printf("Vous pouvez maintenant :\n");
        printf("1. Copier le contenu de ce fichier\n");
        printf("2. Aller sur https://www.mermaidchart.com/\n");
        printf("3. Coller le contenu dans l'editeur\n");
        printf("4. Visualiser votre graphe de Markov !\n");
    }
    printf("\n");










    return 0;


}