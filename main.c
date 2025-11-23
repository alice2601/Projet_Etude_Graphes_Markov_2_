#include "cmake-build-debug/tarjan.h"
#include "cmake-build-debug/mermaid_partie2.h"
#include "cmake-build-debug/hasse.h"
#include <stdio.h>

#include "cmake-build-debug/fonction.h"
#include "cmake-build-debug/stack.h"
#include "cmake-build-debug/matrice.h"





int main() {
    /*printf("Creation manuelle d un graphe : \n");

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

    printf("Verifions si le graphique est un graphique Markov : \n");
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




printf("\n\n PARTIE 2 : ALGORITHME DE TARJAN \n\n");

    // Préparer les données pour Tarjan
    // On a besoin de créer un tableau d'adjacence (int**) et un tableau nb_voisins (int*)

    // 1) Compter le nombre de voisins pour chaque sommet
    int* nb_voisins = malloc(sizeof(int) * monGraphe->taille);
    for (int i = 0; i < monGraphe->taille; i++) {
        int count = 0;
        t_cell* current = monGraphe->tab[i].head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        nb_voisins[i] = count;
    }

    // 2) Créer le tableau d'adjacence (int**)
    int** adj = malloc(sizeof(int*) * monGraphe->taille);
    for (int i = 0; i < monGraphe->taille; i++) {
        adj[i] = malloc(sizeof(int) * nb_voisins[i]);

        t_cell* current = monGraphe->tab[i].head;
        int index = 0;
        while (current != NULL) {
            adj[i][index] = current->sommet_arrive - 1; // -1 car Tarjan utilise des indices 0..n-1
            index++;
            current = current->next;
        }
    }

    // 3) Exécuter l'algorithme de Tarjan
    printf("Execution de l'algorithme de Tarjan...\n\n");
    t_partition* partition = tarjan(monGraphe->taille, adj, nb_voisins);

    if (partition == NULL) {
        printf("Erreur lors de l'execution de Tarjan\n");
        return 1;
    }

    // 4) Afficher les composantes trouvées
    printf("Composantes fortement connexes trouvees :\n");
    printf("Nombre total de classes : %d\n", partition->nb_classes);
    for (int i = 0; i < partition->nb_classes; i++) {
        printf("Composante %s: {", partition->classes[i].name);
        for (int j = 0; j < partition->classes[i].nb_sommets; j++) {
            printf("%d", partition->classes[i].head[j].id);
            if (j < partition->classes[i].nb_sommets - 1) {
                printf(",");
            }
        }
        printf("} (nb_sommets=%d)\n", partition->classes[i].nb_sommets);
    }

    // DEBUG: Afficher le mapping sommet -> classe
    printf("\nDEBUG - Verification du mapping sommet -> classe :\n");
    for (int i = 0; i < monGraphe->taille; i++) {
        printf("Sommet %d -> ", i+1);
        bool found = false;
        for (int c = 0; c < partition->nb_classes; c++) {
            for (int s = 0; s < partition->classes[c].nb_sommets; s++) {
                if (partition->classes[c].head[s].id == i+1) {
                    printf("Classe %s\n", partition->classes[c].name);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) printf("AUCUNE CLASSE !!!\n");
    }











    printf("\n DIAGRAMME DE HASSE \n\n");

    // 5) Générer le diagramme de Hasse au format Mermaid
    generateHasseMermaidFile(partition, monGraphe, "hasse_diagram.txt");

    printf("\n CARACTERISTIQUES DU GRAPHE \n");

    // 6) Afficher les caractéristiques du graphe
    displayGraphCharacteristics(partition, monGraphe);

    // 7) Libération de la mémoire
    for (int i = 0; i < monGraphe->taille; i++) {
        free(adj[i]);
    }
    free(adj);
    free(nb_voisins);

    for (int i = 0; i < partition->nb_classes; i++) {
        free(partition->classes[i].head);
    }
    free(partition->classes);
    free(partition);







    printf("\n DIAGRAMME DE HASSE SIMPLIFIE \n");

    // Générer le diagramme de Hasse SIMPLIFIE (sans redondances)
    generateMermaidSimplified(partition, monGraphe, "mermaid_simplifie.txt");
**/









//PARTIE 3

    // Verification N°1 :
    // // 1) Affichage de la matrice associé à élément

    // Nom du fichier en dur

    char* filename = "graph.txt";

    //Lecture du graphe depuis le fichier
    t_list_adjacente* adj = readGraph(filename);
    if(adj == NULL){
        printf("Erreur lecture du graphe\n");
        return 1;
    }
    int n = adj->taille;



    // === UNE SEULE DÉCLARATION DE M ===
    double** M = createtransitionmatrice(adj);




    // Création de la matrice de transition

    printf("Matrice de transition M :\n");
    printmatrice(M, n);

    // 2) Calcul de M^3
    double** M2 = multiplymatrice(M, M, n);
    double** M3 = multiplymatrice(M2, M, n);
    printf("M^3 :\n");
    printmatrice(M3, n);

    // 3) Calcul de M^7
    double** temp = creatematricezero(n);
    copymatrice(M, temp, n);
    for(int i=1;i<7;i++){
        double** newtemp = multiplymatrice(temp, M, n);
        // libération de l'ancienne matrice
        for(int r=0;r<n;r++) free(temp[r]);
        free(temp);
        temp = newtemp;
    }
    printf("M^7 :\n");
    printmatrice(temp, n);

    // 4) Différence pour convergence
    double epsilon = 0.01;
    double diff = diffmatrice(M3, temp, n);
    printf("Difference entre M^3 et M^7 = %.5f\n", diff);
    if(diff < epsilon)
        printf("Convergence possible vers une distribution stationnaire\n");
    else
        printf("Pas encore converge\n");








    int* nb_voisins = malloc(sizeof(int) * adj->taille);
    for (int i = 0; i < adj->taille; i++) {
        int count = 0;
        t_cell* current = adj->tab[i].head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        nb_voisins[i] = count;
    }

    int** adj_tarjan = malloc(sizeof(int*) * adj->taille);
    for (int i = 0; i < adj->taille; i++) {
        adj_tarjan[i] = malloc(sizeof(int) * nb_voisins[i]);
        t_cell* current = adj->tab[i].head;
        int index = 0;
        while (current != NULL) {
            adj_tarjan[i][index] = current->sommet_arrive - 1;
            index++;
            current = current->next;
        }
    }


    t_partition* partition = tarjan(adj->taille, adj_tarjan, nb_voisins);






    // Puis l'analyse étape 2
    analyserComposantesMarkov(M, adj->taille, partition);



    // analyse étape 2
    analyserComposantesMarkov(M, adj->taille, partition);


    for (int i = 0; i < adj->taille; i++) {
        free(adj_tarjan[i]);
    }
    free(adj_tarjan);
    free(nb_voisins);

    for (int i = 0; i < partition->nb_classes; i++) {
        free(partition->classes[i].head);
    }
    free(partition->classes);
    free(partition);





        // ÉTAPE 3 : Analyse AVEC périodicité
    printf("\n");
    printf("  ETAPE 3 : ANALYSE AVEC PERIODICITE\n");
    analyser_composantes_periodicite(M, adj->taille, partition);

    // LIBÉRATION DE LA MÉMOIRE
    for (int i = 0; i < adj->taille; i++) {
        free(adj_tarjan[i]);
    }
    free(adj_tarjan);
    free(nb_voisins);

    for (int i = 0; i < partition->nb_classes; i++) {
        free(partition->classes[i].head);
    }
    free(partition->classes);
    free(partition);

    // Libération de M
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);




    return 0;

}




