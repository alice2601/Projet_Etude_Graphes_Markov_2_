#include "tarjan.h"
#include "mermaid_partie2.h"
#include "hasse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <math.h>


#include "fonction.h"
#include "stack.h"
#include "matrice.h"





/*
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







    /*

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
    **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <direct.h>  // pour _mkdir sous Windows
#include "tarjan.h"  // ou autre header nécessaire pour readGraph, etc.

// Fonction utilitaire pour créer un dossier si nécessaire
void make_dir(const char* dirname) {
    _mkdir(dirname); // Windows
}

int main() {
    // 1) Lecture du graphe depuis fichier
    char* filename = "matrix27.txt";
    t_list_adjacente* adj = readGraph(filename);
    if (adj == NULL) {
        printf("\nErreur lecture graphe\n");
        return 1;
    }

    int n = adj->taille; // nombre de sommets
    printf("\nNombre d'états : %d\n", n);

    // 2) Création de la matrice de transition
    double** M = createtransitionmatrice(adj);
    printf("\nMatrice de transition M :\n");
    printmatrice(M, n);

    // 3) Initialisation du vecteur de départ (état 2 à 1)
    double* dist = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist[i] = 0.0;
    dist[1] = 1.0; // état 2

    // 4) Calcul des distributions pour n = 1,2,10,50
    int pas[] = {1, 2, 10, 50};

    make_dir("csv"); // créer le dossier parent pour CSV

    for (int k = 0; k < 4; k++) {
        int n_pas = pas[k];

        // Création du dossier pour ce nombre de pas
        char dir_name[64];
        sprintf(dir_name, "csv/n=%d", n_pas);
        make_dir(dir_name);

        // Copie de la distribution initiale
        double* dist_n = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist[i];

        // Multiplication matrice × vecteur
        for (int step = 0; step < n_pas; step++) {
            double* next = (double*)malloc(n * sizeof(double));
            for (int i = 0; i < n; i++) {
                next[i] = 0.0;
                for (int j = 0; j < n; j++) {
                    next[i] += dist_n[j] * M[j][i]; // CORRECTION ici
                }
            }
            free(dist_n);
            dist_n = next;
        }

        // Affichage
        printf("\nDistribution apres n=%d pas :\n", n_pas);
        for (int i = 0; i < n; i++) {
            printf("Etat %d : %.5f\n", i+1, dist_n[i]);
        }

        // Export CSV
        char file_name[128];
        sprintf(file_name, "%s/distributions.csv", dir_name);
        FILE* f = fopen(file_name, "w");
        if (!f) {
            printf("\nErreur création fichier %s\n", file_name);
        } else {
            fprintf(f, "Etat;Probabilite\n");
            for (int i = 0; i < n; i++) {
                fprintf(f, "Etat%d;%.5f\n", i+1, dist_n[i]);
            }
            fclose(f);
            printf("Distribution exportee dans %s\n", file_name);
        }

        free(dist_n);
    }

    // 5) Vérification de la distribution limite
    double* dist_limite = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist_limite[i] = dist[i];

    int convergent = 0;
    for (int step = 1; step <= 1000; step++) {
        double* next = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            next[i] = 0.0;
            for (int j = 0; j < n; j++) {
                next[i] += dist_limite[j] * M[j][i];
            }
        }

        double diff = 0.0;
        for (int i = 0; i < n; i++) {
            diff += fabs(next[i] - dist_limite[i]);
            dist_limite[i] = next[i];
        }
        free(next);

        if (diff < 1e-6) {
            convergent = 1;
            break;
        }
    }

    if (convergent) {
        printf("\nDistribution limite :\n");
        for (int i = 0; i < n; i++) {
            printf("Etat %d : %.5f\n", i+1, dist_limite[i]);
        }
    } else {
        printf("\nPas de distribution limite detectee\n");
    }

    // 6) Libération mémoire
    free(dist);
    free(dist_limite);

    for (int i = 0; i < n; i++) free(M[i]);
    free(M);


    // Q 2:



printf("\n\nQUESTION 2 \n");

// 1) Initialisation du vecteur uniformément réparti
double* dist_q2 = (double*)malloc(n * sizeof(double));
if (dist_q2 == NULL) {
    printf("Erreur allocation mémoire dist_q2\n");
    // Libérer la mémoire déjà allouée avant de quitter à chque fois
    for (int i = 0; i < n; i++) free(M[i]);
    free(M);
    return 1;
}

for (int i = 0; i < n; i++) dist_q2[i] = 0.0;

// États 2, 5, 12, 21, 25 → indices 1, 4, 11, 20, 24
dist_q2[1] = 0.2;   // État 2
dist_q2[4] = 0.2;   // État 5
dist_q2[11] = 0.2;  // État 12
dist_q2[20] = 0.2;  // État 21
dist_q2[24] = 0.2;  // État 25

printf("Distribution initiale (uniforme sur 2, 5, 12, 21, 25) :\n");
for (int i = 0; i < n; i++) {
    if (dist_q2[i] > 0) printf("  État %d : %.5f\n", i+1, dist_q2[i]);
}

// 2) Calcul des distributions après n pas
int pas_q2[] = {1, 2, 10, 50};
for (int k = 0; k < 4; k++) {
    double* dist_n = (double*)malloc(n * sizeof(double));
    if (dist_n == NULL) {
        printf("Erreur allocation dist_n\n");
        free(dist_q2);
        for (int i = 0; i < n; i++) free(M[i]);
        free(M);
        return 1;
    }

    for (int i = 0; i < n; i++) dist_n[i] = dist_q2[i];

    for (int step = 0; step < pas_q2[k]; step++) {
        double* next = (double*)malloc(n * sizeof(double));
        if (next == NULL) {
            printf("Erreur allocation next\n");
            free(dist_n);
            free(dist_q2);
            for (int i = 0; i < n; i++) free(M[i]);
            free(M);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            next[i] = 0.0;
            for (int j = 0; j < n; j++) {
                next[i] += dist_n[j] * M[i][j];
            }
        }
        free(dist_n);
        dist_n = next;
    }

    printf("\nDistribution après n = %d pas :\n", pas_q2[k]);
    for (int i = 0; i < n; i++) {
        if (dist_n[i] > 0.0001)
            printf("  État %d : %.5f\n", i+1, dist_n[i]);
    }
    free(dist_n);
}

// 3) Vérification distribution limite
double* dist_limite_q2 = (double*)malloc(n * sizeof(double));
if (dist_limite_q2 == NULL) {
    printf("Erreur allocation dist_limite_q2\n");
    free(dist_q2);
    for (int i = 0; i < n; i++) free(M[i]);
    free(M);
    return 1;
}

for (int i = 0; i < n; i++) dist_limite_q2[i] = dist_q2[i];

int convergent_q2 = 0;
for (int step = 1; step <= 1000; step++) {
    double* next = (double*)malloc(n * sizeof(double));
    if (next == NULL) {
        printf("Erreur allocation next dans convergence\n");
        free(dist_limite_q2);
        free(dist_q2);
        for (int i = 0; i < n; i++) free(M[i]);
        free(M);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        next[i] = 0.0;
        for (int j = 0; j < n; j++) {
            next[i] += dist_limite_q2[j] * M[i][j];
        }
    }

    double diff = 0.0;
    for (int i = 0; i < n; i++) {
        diff += fabs(next[i] - dist_limite_q2[i]);
        dist_limite_q2[i] = next[i];
    }
    free(next);

    if (diff < 1e-6) {
        convergent_q2 = 1;
        printf("\nConvergence atteinte après %d itérations\n", step);
        break;
    }
}

if (convergent_q2) {
    printf("\n✓ Distribution limite existe (Question 2) :\n");
    for (int i = 0; i < n; i++) {
        if (dist_limite_q2[i] > 0.0001)
            printf("  État %d : %.5f\n", i+1, dist_limite_q2[i]);
    }
} else {
    printf("\n✗ Pas de distribution limite détectée (Question 2)\n");
}

// Libération mémoire Question 2
free(dist_q2);
free(dist_limite_q2);

    // Q3:

    printf("\n\nQUESTION 3\n");

    // Tester plusieurs combinaisons de (a, b, c, d, e) -- proba différentes
    double parametres[][5] = {
        {0.5, 0.2, 0.1, 0.1, 0.1},  // Test 1
        {0.1, 0.1, 0.6, 0.1, 0.1},  // Test 2
        {0.3, 0.3, 0.1, 0.2, 0.1},  // Test 3
        {0.0, 0.0, 0.0, 0.5, 0.5},  // Test 4
    };

    int nb_tests = 4;

    for (int test = 0; test < nb_tests; test++) {
        double a = parametres[test][0];
        double b = parametres[test][1];
        double c = parametres[test][2];
        double d = parametres[test][3];
        double e = parametres[test][4];

        printf("\n Test %d : a=%.2f, b=%.2f, c=%.2f, d=%.2f, e=%.2f \n",
               test+1, a, b, c, d, e);

        // Initialisation
        double* dist_q3 = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_q3[i] = 0.0;
        dist_q3[1] = a;   // État 2
        dist_q3[4] = b;   // État 5
        dist_q3[11] = c;  // État 12
        dist_q3[20] = d;  // État 21
        dist_q3[24] = e;  // État 25

        // Calcul distribution limite
        double* dist_limite_q3 = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_limite_q3[i] = dist_q3[i];

        for (int step = 1; step <= 1000; step++) {
            double* next = (double*)malloc(n * sizeof(double));
            for (int i = 0; i < n; i++) {
                next[i] = 0.0;
                for (int j = 0; j < n; j++) {
                    next[i] += dist_limite_q3[j] * M[i][j];
                }
            }

            double diff = 0.0;
            for (int i = 0; i < n; i++) {
                diff += fabs(next[i] - dist_limite_q3[i]);
                dist_limite_q3[i] = next[i];
            }
            free(next);

            if (diff < 1e-6) break;
        }

        printf("Distribution limite :\n");
        for (int i = 0; i < n; i++) {
            if (dist_limite_q3[i] > 0.0001)
                printf("État %d : %.5f\n", i+1, dist_limite_q3[i]);
        }

        free(dist_q3);
        free(dist_limite_q3);
    }


// Libération de la matrice M et du graphe (UNE SEULE FOIS à la toute fin) donc si rajout de code utilisant matrice M (mettre avant ces deux lignes)

for (int i = 0; i < n; i++) free(M[i]);
free(M);


return 0;
}