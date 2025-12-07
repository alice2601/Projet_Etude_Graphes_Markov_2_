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
int main() {
// Question 1a:
// __________________

    // 1) Lecture du graphe depuis fichier

    char* filename = "matrix27.txt"; // nom du fichier contenant le graphe pondéré

    // Lecture du graphe dans une liste d'adjacence
    t_list_adjacente* adj = readGraph(filename);
    if (adj == NULL) { // vérifier si le fichier est bien lu
        printf("Erreur lecture graphe\n");
        return 1;
    }

    int n = adj->taille; // nombre de sommets
// Explication : readGraph retourne une t_list_adjacente* qui contient le grpahe lu depuis le fichier
                // Et adj-> taille donne le nombre de sommets

    // 2) Création de la matrice de transition

    // On transforme la liste d'adjacence en matrice de transition M[n][n]
    double** M = createtransitionmatrice(adj);

    printf("Matrice de transition M :\n");
    printmatrice(M, n); // affichage de la matrice pour vérifier
// Explications : createtransitionmatrice transforme la liste d'adjacence en matrice nxn de probabilités

    // 3) Initialisation du vecteur de départ

    // On commence dans l'état 2
    double* dist = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist[i] = 0.0; // tout à 0
    dist[1] = 1.0; // état 2 = probabilité 1
// Explications : On initialise le vecteur de dostribution avec 1.0 à l'état 2
    // Pourquoi ? Car les indices en C commencent à 0, donc l'état 2 -> index 1

    // 4) Calcul des distributions après n pas

    int pas[] = {1, 2, 10, 50}; // nombres de pas à calculer

    for (int k = 0; k < 4; k++) {
        // On copie la distribution initiale
        double* dist_n = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist[i];

        // On multiplie dist_n par la matrice M pour chaque pas
        for (int step = 0; step < pas[k]; step++) {
            double* next = (double*)malloc(n * sizeof(double));
            for (int i = 0; i < n; i++) {
                next[i] = 0.0;
                // produit matrice × vecteur
                for (int j = 0; j < n; j++) {
                    next[i] += dist_n[j] * M[j][i];
                }
            }
            free(dist_n); // libérer l'ancienne distribution
            dist_n = next; // passer à la distribution suivante
        }

        // Affichage de la distribution après n pas
        printf("\nDistribution apres n = %d pas :\n", pas[k]);
        for (int i = 0; i < n; i++) {
            printf("État %d : %.5f\n", i+1, dist_n[i]);
        }

        free(dist_n); // libération mémoire pour ce calcul
    }
    // Explication : Pour chaque nombre de pas n, on multiplie le vecteur par la matrice M n fois
    // Chaque multiplication représente un pas de Markov


    // 5) Vérification de la distribution limite

    // On réinitialise la distribution
    double* dist_limite = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist_limite[i] = dist[i];

    int convergent = 0; // drapeau de convergence

    for (int step = 1; step <= 1000; step++) { // on itère jusqu'à 1000 pas max
        double* next = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            next[i] = 0.0;
            for (int j = 0; j < n; j++) {
                next[i] += dist_limite[j] * M[j][i]; // multiplication vecteur × matrice
            }
        }

        // Calcul de la différence pour tester la convergence
        double diff = 0.0;
        for (int i = 0; i < n; i++) {
            diff += fabs((double)(next[i] - dist_limite[i]));
            dist_limite[i] = next[i]; // mise à jour
        }

        free(next);

        // Si la différence est très petite, on considère que c'est la distribution limite
        if (diff < 1e-6) {
            convergent = 1;
            break;
        }
    }

    // Affichage de la distribution limite si convergence
    if (convergent) {
        printf("\nDistribution limite :\n");
        for (int i = 0; i < n; i++) {
            printf("État %d : %.5f\n", i+1, dist_limite[i]);
        }
    } else {
        printf("\nPas de distribution limite detectee\n");
    }
    // Explication : On itère jusqu'à convergence (diff < 1e-6) ou un nombre max d'iterantions
    // Si convergé, on affiche la distribution limite





    // Question 1b :
    // Tracer la matrice
    // Pour ça je vais devoir créer un graph qu'on va devoir exporter sur excel pour le tracer car sur CLION on ne peut pas


    // Etape 1 : Export des distributions pour tracer ΠA(n) en fonction de n
    FILE* f = fopen("distributions.csv", "w");
    if (!f) {
        printf("Erreur création fichier distributions.csv\n");
    } else {
        // En-tête CSV : états
        fprintf(f, "n");
        for (int i = 0; i < n; i++) {
            fprintf(f, ";Etat%d", i+1);
        }
        fprintf(f, "\n");

        // Etape 2 : On parcourt les mêmes pas que pour la question 1a
        int max_pas = 50; // pour avoir un graphe continu, on peut calculer tous les pas jusqu'à 50
        double* dist_n = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist[i]; // état initial

        for (int step = 0; step <= max_pas; step++) {
            // écrire la distribution pour ce pas
            fprintf(f, "%d", step);
            for (int i = 0; i < n; i++) {
                fprintf(f, ";%.5f", dist_n[i]);
            }
            fprintf(f, "\n");

            // calcul de la distribution suivante
            double* next = (double*)malloc(n * sizeof(double));
            for (int i = 0; i < n; i++) {
                next[i] = 0.0;
                for (int j = 0; j < n; j++) {
                    next[i] += dist_n[j] * M[i][j];
                }
            }
            free(dist_n);
            dist_n = next;
        }

        free(dist_n);
        fclose(f);
        printf("\nLes distributions ΠA(n) ont ete exportees dans distributions.csv pour trace.\n");
// Ne reste plus qu'à tout mettre sur excel

    }

    // 6) Libération mémoire

    free(dist);
    free(dist_limite);

    // POurquoi ? Car important pour éviter les fuites mémoire avec tts les allocation malloc


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
// ================================
// QUESTION 4
// ================================

printf("\n\nQUESTION 4\n");

double* dist_q4 = malloc(n * sizeof(double));
double* dist_limite_q4 = malloc(n * sizeof(double));

int pas_Q4[] = {1, 2, 10, 50};

for (int cas = 0; cas < 3; cas++) {

    // -------- INITIALISATION -----------------
    for (int i = 0; i < n; i++) dist_q4[i] = 0.0;

    if (cas == 0) {
        printf("\nCas 1 : état initial = 8\n");
        dist_q4[7] = 1.0;
    }
    else if (cas == 1) {
        printf("\nCas 2 : uniforme sur 8, 9, 16\n");
        dist_q4[7]  = 1.0/3;
        dist_q4[8]  = 1.0/3;
        dist_q4[15] = 1.0/3;
    }
    else {
        printf("\nCas 3 : répartition aléatoire sur 8, 9, 16\n");
        double r1 = rand()/(double)RAND_MAX;
        double r2 = rand()/(double)RAND_MAX;
        double r3 = rand()/(double)RAND_MAX;
        double somme = r1 + r2 + r3;
        dist_q4[7]  = r1/somme;
        dist_q4[8]  = r2/somme;
        dist_q4[15] = r3/somme;
    }

    // --------- DISTRIBUTIONS APRÈS n PAS -----------------
    for (int k = 0; k < 4; k++) {

        int npas = pas_Q4[k];

        double* dist_n = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist_q4[i];

        for (int step = 0; step < npas; step++) {

            double* next = malloc(n * sizeof(double));

            // next[j] = somme_i dist[i] * M[i][j]
            for (int j = 0; j < n; j++) {
                next[j] = 0.0;
                for (int i = 0; i < n; i++) {
                    next[j] += dist_n[i] * M[i][j];
                }
            }

            free(dist_n);
            dist_n = next;
        }

        printf("\nDistribution après n = %d pas :\n", npas);
        for (int i = 0; i < n; i++)
            if (dist_n[i] > 0.0001)
                printf("État %d : %.5f\n", i+1, dist_n[i]);

        free(dist_n);
    }

    // --------- DISTRIBUTION LIMITE -----------------
    for (int i = 0; i < n; i++) dist_limite_q4[i] = dist_q4[i];

    for (int iter = 1; iter <= 1000; iter++) {

        double* next = malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_limite_q4[i] * M[i][j];
        }

        double diff = 0.0;
        for (int i = 0; i < n; i++) {
            diff += fabs(next[i] - dist_limite_q4[i]);
            dist_limite_q4[i] = next[i];
        }

        free(next);
        if (diff < 1e-6) break;
    }

    printf("\nDistribution limite du cas %d :\n", cas+1);
    for (int i = 0; i < n; i++)
        if (dist_limite_q4[i] > 0.0001)
            printf("État %d : %.5f\n", i+1, dist_limite_q4[i]);
}

free(dist_q4);
free(dist_limite_q4);

// ================================
// QUESTION 5
// ================================

printf("\n\nQUESTION 5\n");

int etats_q5[] = {9, 13, 18, 21, 23};
int nb_etats_q5 = 5;

double* dist_q5 = malloc(n * sizeof(double));
double* dist_limite_q5 = malloc(n * sizeof(double));

int pas_Q5[] = {1, 2, 10, 50};

for (int cas = 0; cas < 3; cas++) {

    for (int i = 0; i < n; i++) dist_q5[i] = 0.0;

    if (cas == 0) {
        printf("\nCas 1 : état initial = 14\n");
        dist_q5[13] = 1.0;
    }
    else if (cas == 1) {
        printf("\nCas 2 : uniforme sur 10, 14, 19, 22, 24\n");
        for (int i = 0; i < nb_etats_q5; i++)
            dist_q5[etats_q5[i]] = 1.0 / nb_etats_q5;
    }
    else {
        printf("\nCas 3 : répartition aléatoire\n");
        double r[5], somme = 0;
        for (int i = 0; i < nb_etats_q5; i++) {
            r[i] = rand()/(double)RAND_MAX;
            somme += r[i];
        }
        for (int i = 0; i < nb_etats_q5; i++)
            dist_q5[etats_q5[i]] = r[i] / somme;
    }

    // ---------- DISTRIBUTION APRÈS n PAS ---------------
    for (int k = 0; k < 4; k++) {

        int npas = pas_Q5[k];

        double* dist_n = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist_q5[i];

        for (int step = 0; step < npas; step++) {

            double* next = malloc(n * sizeof(double));

            for (int j = 0; j < n; j++) {
                next[j] = 0.0;
                for (int i = 0; i < n; i++)
                    next[j] += dist_n[i] * M[i][j];
            }

            free(dist_n);
            dist_n = next;
        }

        printf("\nDistribution après n = %d pas :\n", npas);
        for (int i = 0; i < n; i++)
            if (dist_n[i] > 0.0001)
                printf("État %d : %.5f\n", i+1, dist_n[i]);

        free(dist_n);
    }

    // ---------- DISTRIBUTION LIMITE ---------------
    for (int i = 0; i < n; i++) dist_limite_q5[i] = dist_q5[i];

    for (int iter = 1; iter <= 1000; iter++) {

        double* next = malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_limite_q5[i] * M[i][j];
        }

        double diff = 0.0;
        for (int i = 0; i < n; i++) {
            diff += fabs(next[i] - dist_limite_q5[i]);
            dist_limite_q5[i] = next[i];
        }

        free(next);
        if (diff < 1e-6) break;
    }

    printf("\nDistribution limite du cas %d :\n", cas+1);
    for (int i = 0; i < n; i++)
        if (dist_limite_q5[i] > 0.0001)
            printf("État %d : %.5f\n", i+1, dist_limite_q5[i]);
}

free(dist_q5);
free(dist_limite_q5);

// Libération de la matrice M et du graphe (UNE SEULE FOIS à la toute fin) donc si rajout de code utilisant matrice M (mettre avant ces deux lignes)
// ================================
// QUESTION 6
// ================================

printf("\n\n========================================\n");
printf("           QUESTION 6\n");
printf("========================================\n");

// Etats concernes : 6, 17, 20 (indices : 5, 16, 19)
int etats_q6[] = {5, 16, 19}; // indices en C (etat-1)
int nb_etats_q6 = 3;

double* dist_q6 = malloc(n * sizeof(double));
double* dist_limite_q6 = malloc(n * sizeof(double));

int pas_Q6[] = {1, 2, 10, 50};

// ========================================
// PARTIE A : Depart depuis l'etat 6 uniquement
// ========================================

printf("\n--- PARTIE A : Etat initial = 6 ---\n");

// Initialisation : 100% dans l'etat 6
for (int i = 0; i < n; i++) dist_q6[i] = 0.0;
dist_q6[5] = 1.0; // Etat 6 = indice 5

printf("\nDistribution initiale :\n");
printf("  Etat 6 : 1.00000\n");

// Calcul pour n = 1, 2, 10, 50 pas
for (int k = 0; k < 4; k++) {
    int npas = pas_Q6[k];

    // Copie de la distribution initiale
    double* dist_n = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist_n[i] = dist_q6[i];

    // Application de n multiplications par M
    for (int step = 0; step < npas; step++) {
        double* next = malloc(n * sizeof(double));

        // Calcul : next = dist_n x M
        // next[j] = somme_i dist_n[i] x M[i][j]
        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++) {
                next[j] += dist_n[i] * M[i][j];
            }
        }

        free(dist_n);
        dist_n = next;
    }

    // Affichage
    printf("\nDistribution apres n = %d pas :\n", npas);
    for (int i = 0; i < n; i++) {
        if (dist_n[i] > 0.0001) // Afficher seulement si probabilite significative
            printf("  Etat %d : %.5f\n", i+1, dist_n[i]);
    }

    free(dist_n);
}

// Calcul de la distribution limite pour la partie A
for (int i = 0; i < n; i++) dist_limite_q6[i] = dist_q6[i];

int convergent_q6a = 0;
int iterations_q6a = 0;

for (int iter = 1; iter <= 1000; iter++) {
    double* next = malloc(n * sizeof(double));

    for (int j = 0; j < n; j++) {
        next[j] = 0.0;
        for (int i = 0; i < n; i++)
            next[j] += dist_limite_q6[i] * M[i][j];
    }

    // Calcul de la difference pour tester la convergence
    double diff = 0.0;
    for (int i = 0; i < n; i++) {
        diff += fabs(next[i] - dist_limite_q6[i]);
        dist_limite_q6[i] = next[i];
    }

    free(next);

    if (diff < 1e-6) {
        convergent_q6a = 1;
        iterations_q6a = iter;
        break;
    }
}

// Affichage du resultat
if (convergent_q6a) {
    printf("\n[OK] Distribution limite EXISTE (convergence apres %d iterations)\n", iterations_q6a);
    printf("\nValeurs de la distribution limite (Partie A) :\n");
    for (int i = 0; i < n; i++) {
        if (dist_limite_q6[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_limite_q6[i]);
    }
} else {
    printf("\n[ERREUR] PAS de distribution limite detectee (Partie A)\n");
}

// ========================================
// PARTIE B : Distribution uniforme sur {6, 17, 20}
// ========================================

printf("\n\n--- PARTIE B : Uniforme sur {6, 17, 20} ---\n");

// Initialisation : 1/3 pour chaque etat
for (int i = 0; i < n; i++) dist_q6[i] = 0.0;
dist_q6[5] = 1.0/3;   // Etat 6
dist_q6[16] = 1.0/3;  // Etat 17
dist_q6[19] = 1.0/3;  // Etat 20

printf("\nDistribution initiale :\n");
printf("  Etat 6  : %.5f\n", 1.0/3);
printf("  Etat 17 : %.5f\n", 1.0/3);
printf("  Etat 20 : %.5f\n", 1.0/3);

// Calcul pour n = 1, 2, 10, 50 pas
for (int k = 0; k < 4; k++) {
    int npas = pas_Q6[k];

    double* dist_n = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist_n[i] = dist_q6[i];

    for (int step = 0; step < npas; step++) {
        double* next = malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_n[i] * M[i][j];
        }

        free(dist_n);
        dist_n = next;
    }

    printf("\nDistribution apres n = %d pas :\n", npas);
    for (int i = 0; i < n; i++) {
        if (dist_n[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_n[i]);
    }

    free(dist_n);
}

// Distribution limite Partie B
for (int i = 0; i < n; i++) dist_limite_q6[i] = dist_q6[i];

int convergent_q6b = 0;
int iterations_q6b = 0;

for (int iter = 1; iter <= 1000; iter++) {
    double* next = malloc(n * sizeof(double));

    for (int j = 0; j < n; j++) {
        next[j] = 0.0;
        for (int i = 0; i < n; i++)
            next[j] += dist_limite_q6[i] * M[i][j];
    }

    double diff = 0.0;
    for (int i = 0; i < n; i++) {
        diff += fabs(next[i] - dist_limite_q6[i]);
        dist_limite_q6[i] = next[i];
    }

    free(next);

    if (diff < 1e-6) {
        convergent_q6b = 1;
        iterations_q6b = iter;
        break;
    }
}

if (convergent_q6b) {
    printf("\n[OK] Distribution limite EXISTE (convergence apres %d iterations)\n", iterations_q6b);
    printf("\nValeurs de la distribution limite (Partie B) :\n");
    for (int i = 0; i < n; i++) {
        if (dist_limite_q6[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_limite_q6[i]);
    }
} else {
    printf("\n[ERREUR] PAS de distribution limite detectee (Partie B)\n");
}

// ========================================
// PARTIE C : Repartition aleatoire sur {6, 17, 20}
// ========================================

printf("\n\n--- PARTIE C : Repartition aleatoire sur {6, 17, 20} ---\n");

// Tester plusieurs scenarios avec differents parametres (a, b, c)
double parametres_q6[][3] = {
    {0.5, 0.3, 0.2},  // Scenario 1
    {0.2, 0.2, 0.6},  // Scenario 2
    {0.7, 0.1, 0.2},  // Scenario 3
    {0.1, 0.8, 0.1},  // Scenario 4
};

int nb_scenarios = 4;

// Stocker les distributions limites pour comparaison
double** limites_q6c = malloc(nb_scenarios * sizeof(double*));
for (int s = 0; s < nb_scenarios; s++) {
    limites_q6c[s] = malloc(n * sizeof(double));
}

for (int scenario = 0; scenario < nb_scenarios; scenario++) {
    double a = parametres_q6[scenario][0];
    double b = parametres_q6[scenario][1];
    double c = parametres_q6[scenario][2];

    printf("\n=== Scenario %d : a=%.2f, b=%.2f, c=%.2f ===\n",
           scenario+1, a, b, c);

    // Initialisation
    for (int i = 0; i < n; i++) dist_q6[i] = 0.0;
    dist_q6[5] = a;   // Etat 6
    dist_q6[16] = b;  // Etat 17
    dist_q6[19] = c;  // Etat 20

    printf("Distribution initiale :\n");
    printf("  Etat 6  : %.5f\n", a);
    printf("  Etat 17 : %.5f\n", b);
    printf("  Etat 20 : %.5f\n", c);

    // Calcul pour n = 1, 2, 10, 50 pas
    for (int k = 0; k < 4; k++) {
        int npas = pas_Q6[k];

        double* dist_n = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist_q6[i];

        for (int step = 0; step < npas; step++) {
            double* next = malloc(n * sizeof(double));

            for (int j = 0; j < n; j++) {
                next[j] = 0.0;
                for (int i = 0; i < n; i++)
                    next[j] += dist_n[i] * M[i][j];
            }

            free(dist_n);
            dist_n = next;
        }

        printf("\nDistribution apres n = %d pas :\n", npas);
        for (int i = 0; i < n; i++) {
            if (dist_n[i] > 0.0001)
                printf("  Etat %d : %.5f\n", i+1, dist_n[i]);
        }

        free(dist_n);
    }

    // Distribution limite
    for (int i = 0; i < n; i++) dist_limite_q6[i] = dist_q6[i];

    for (int iter = 1; iter <= 1000; iter++) {
        double* next = malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_limite_q6[i] * M[i][j];
        }

        double diff = 0.0;
        for (int i = 0; i < n; i++) {
            diff += fabs(next[i] - dist_limite_q6[i]);
            dist_limite_q6[i] = next[i];
        }

        free(next);

        if (diff < 1e-6) break;
    }

    printf("\nDistribution limite (Scenario %d) :\n", scenario+1);
    for (int i = 0; i < n; i++) {
        if (dist_limite_q6[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_limite_q6[i]);
    }

    // Sauvegarder pour comparaison
    for (int i = 0; i < n; i++) {
        limites_q6c[scenario][i] = dist_limite_q6[i];
    }
}

// ========================================
// COMPARAISON DES DISTRIBUTIONS LIMITES
// ========================================

printf("\n\n=== ANALYSE : Les distributions limites sont-elles identiques ? ===\n");

int identiques = 1;
for (int s = 1; s < nb_scenarios; s++) {
    double diff_totale = 0.0;
    for (int i = 0; i < n; i++) {
        diff_totale += fabs(limites_q6c[s][i] - limites_q6c[0][i]);
    }

    if (diff_totale > 1e-4) {
        identiques = 0;
        printf("[DIFF] Scenario %d differe du scenario 1 (difference = %.6f)\n",
               s+1, diff_totale);
    }
}

if (identiques) {
    printf("\n[CONCLUSION PARTIE C]\n");
    printf("Toutes les distributions limites sont IDENTIQUES !\n");
    printf("La distribution limite NE DEPEND PAS des parametres (a, b, c).\n");
    printf("\nCela signifie que {6, 17, 20} forme une classe finale APERIODIQUE.\n");
} else {
    printf("\n[CONCLUSION PARTIE C]\n");
    printf("Les distributions limites DEPENDENT des parametres (a, b, c).\n");
}

// Export CSV pour graphiques Excel
FILE* f_q6 = fopen("question6_distributions.csv", "w");
if (f_q6) {
    fprintf(f_q6, "n;Etat6;Etat17;Etat20\n");

    // Reinitialiser depuis l'etat 6
    for (int i = 0; i < n; i++) dist_q6[i] = 0.0;
    dist_q6[5] = 1.0;

    for (int step = 0; step <= 100; step++) {
        fprintf(f_q6, "%d;%.6f;%.6f;%.6f\n",
                step, dist_q6[5], dist_q6[16], dist_q6[19]);

        double* next = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_q6[i] * M[i][j];
        }
        for (int i = 0; i < n; i++) dist_q6[i] = next[i];
        free(next);
    }

    fclose(f_q6);
    printf("\n[EXPORT] Fichier 'question6_distributions.csv' cree pour tracer les graphes.\n");
}

// Liberation memoire
for (int s = 0; s < nb_scenarios; s++) {
    free(limites_q6c[s]);
}
free(limites_q6c);
free(dist_q6);
free(dist_limite_q6);

printf("\n========================================\n");
printf("      FIN DE LA QUESTION 6\n");
printf("========================================\n\n");

    // ================================
// QUESTION 7
// ================================

printf("\n\n========================================\n");
printf("           QUESTION 7\n");
printf("========================================\n");

// Etats concernes : 3, 7, 23 (indices : 2, 6, 22)
int etats_q7[] = {2, 6, 22}; // indices en C (etat-1)
int nb_etats_q7 = 3;

double* dist_q7 = malloc(n * sizeof(double));
double* dist_limite_q7 = malloc(n * sizeof(double));

int pas_Q7[] = {1, 2, 10, 50};

// ========================================
// PARTIE A : Depart depuis l'etat 3 uniquement
// ========================================

printf("\n--- PARTIE A : Etat initial = 3 ---\n");

// Initialisation : 100% dans l'etat 3
for (int i = 0; i < n; i++) dist_q7[i] = 0.0;
dist_q7[2] = 1.0; // Etat 3 = indice 2

printf("\nDistribution initiale :\n");
printf("  Etat 3 : 1.00000\n");

// Calcul pour n = 1, 2, 10, 50 pas
for (int k = 0; k < 4; k++) {
    int npas = pas_Q7[k];

    // Copie de la distribution initiale
    double* dist_n = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist_n[i] = dist_q7[i];

    // Application de n multiplications par M
    for (int step = 0; step < npas; step++) {
        double* next = malloc(n * sizeof(double));

        // Calcul : next = dist_n x M
        // next[j] = somme_i dist_n[i] x M[i][j]
        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++) {
                next[j] += dist_n[i] * M[i][j];
            }
        }

        free(dist_n);
        dist_n = next;
    }

    // Affichage
    printf("\nDistribution apres n = %d pas :\n", npas);
    for (int i = 0; i < n; i++) {
        if (dist_n[i] > 0.0001) // Afficher seulement si probabilite significative
            printf("  Etat %d : %.5f\n", i+1, dist_n[i]);
    }

    free(dist_n);
}

// Calcul de la distribution limite pour la partie A
for (int i = 0; i < n; i++) dist_limite_q7[i] = dist_q7[i];

int convergent_q7a = 0;
int iterations_q7a = 0;

for (int iter = 1; iter <= 1000; iter++) {
    double* next = malloc(n * sizeof(double));

    for (int j = 0; j < n; j++) {
        next[j] = 0.0;
        for (int i = 0; i < n; i++)
            next[j] += dist_limite_q7[i] * M[i][j];
    }

    // Calcul de la difference pour tester la convergence
    double diff = 0.0;
    for (int i = 0; i < n; i++) {
        diff += fabs(next[i] - dist_limite_q7[i]);
        dist_limite_q7[i] = next[i];
    }

    free(next);

    if (diff < 1e-6) {
        convergent_q7a = 1;
        iterations_q7a = iter;
        break;
    }
}

// Affichage du resultat
if (convergent_q7a) {
    printf("\n[OK] Distribution limite EXISTE (convergence apres %d iterations)\n", iterations_q7a);
    printf("\nValeurs de la distribution limite (Partie A) :\n");
    for (int i = 0; i < n; i++) {
        if (dist_limite_q7[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_limite_q7[i]);
    }
} else {
    printf("\n[INFO] PAS de distribution limite detectee (Partie A)\n");
    printf("La classe semble PERIODIQUE. Verification...\n\n");

    // Detection de la periode
    printf("Evolution sur 20 pas :\n");

    // Reinitialiser
    for (int i = 0; i < n; i++) dist_q7[i] = 0.0;
    dist_q7[2] = 1.0; // Etat 3

    for (int step = 0; step <= 20; step++) {
        printf("n=%2d : ", step);
        for (int i = 0; i < n; i++) {
            if (dist_q7[i] > 0.5) { // Etat avec proba dominante
                printf("Etat %d (%.3f)", i+1, dist_q7[i]);
            }
        }
        printf("\n");

        // Etape suivante
        double* next = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_q7[i] * M[i][j];
        }
        for (int i = 0; i < n; i++) dist_q7[i] = next[i];
        free(next);
    }

    printf("\n[CONCLUSION] La classe {3, 7, 23} est PERIODIQUE\n");
    printf("Il n'existe PAS de distribution limite dans ce cas.\n");
}

// ========================================
// PARTIE B : Distribution uniforme sur {3, 7, 23}
// ========================================

printf("\n\n--- PARTIE B : Uniforme sur {3, 7, 23} ---\n");

// Initialisation : 1/3 pour chaque etat
for (int i = 0; i < n; i++) dist_q7[i] = 0.0;
dist_q7[2] = 1.0/3;   // Etat 3
dist_q7[6] = 1.0/3;   // Etat 7
dist_q7[22] = 1.0/3;  // Etat 23

printf("\nDistribution initiale :\n");
printf("  Etat 3  : %.5f\n", 1.0/3);
printf("  Etat 7  : %.5f\n", 1.0/3);
printf("  Etat 23 : %.5f\n", 1.0/3);

// Calcul pour n = 1, 2, 10, 50 pas
for (int k = 0; k < 4; k++) {
    int npas = pas_Q7[k];

    double* dist_n = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) dist_n[i] = dist_q7[i];

    for (int step = 0; step < npas; step++) {
        double* next = malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_n[i] * M[i][j];
        }

        free(dist_n);
        dist_n = next;
    }

    printf("\nDistribution apres n = %d pas :\n", npas);
    for (int i = 0; i < n; i++) {
        if (dist_n[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_n[i]);
    }

    free(dist_n);
}

// Distribution limite Partie B
for (int i = 0; i < n; i++) dist_limite_q7[i] = dist_q7[i];

int convergent_q7b = 0;
int iterations_q7b = 0;

for (int iter = 1; iter <= 1000; iter++) {
    double* next = malloc(n * sizeof(double));

    for (int j = 0; j < n; j++) {
        next[j] = 0.0;
        for (int i = 0; i < n; i++)
            next[j] += dist_limite_q7[i] * M[i][j];
    }

    double diff = 0.0;
    for (int i = 0; i < n; i++) {
        diff += fabs(next[i] - dist_limite_q7[i]);
        dist_limite_q7[i] = next[i];
    }

    free(next);

    if (diff < 1e-6) {
        convergent_q7b = 1;
        iterations_q7b = iter;
        break;
    }
}

if (convergent_q7b) {
    printf("\n[OK] Distribution limite EXISTE (convergence apres %d iterations)\n", iterations_q7b);
    printf("\nValeurs de la distribution limite (Partie B) :\n");
    for (int i = 0; i < n; i++) {
        if (dist_limite_q7[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_limite_q7[i]);
    }
} else {
    printf("\n[INFO] PAS de distribution limite detectee (Partie B)\n");
}

// ========================================
// PARTIE C : Repartition aleatoire sur {3, 7, 23}
// ========================================

printf("\n\n--- PARTIE C : Repartition aleatoire sur {3, 7, 23} ---\n");

// Tester plusieurs scenarios avec differents parametres (a, b, c)
double parametres_q7[][3] = {
    {0.5, 0.3, 0.2},  // Scenario 1
    {0.2, 0.2, 0.6},  // Scenario 2
    {0.7, 0.1, 0.2},  // Scenario 3
    {0.1, 0.8, 0.1},  // Scenario 4
};

int nb_scenarios_q7 = 4;

// Stocker les distributions limites pour comparaison
double** limites_q7c = malloc(nb_scenarios_q7 * sizeof(double*));
for (int s = 0; s < nb_scenarios_q7; s++) {
    limites_q7c[s] = malloc(n * sizeof(double));
}

for (int scenario = 0; scenario < nb_scenarios_q7; scenario++) {
    double a = parametres_q7[scenario][0];
    double b = parametres_q7[scenario][1];
    double c = parametres_q7[scenario][2];

    printf("\n=== Scenario %d : a=%.2f, b=%.2f, c=%.2f ===\n",
           scenario+1, a, b, c);

    // Initialisation
    for (int i = 0; i < n; i++) dist_q7[i] = 0.0;
    dist_q7[2] = a;   // Etat 3
    dist_q7[6] = b;   // Etat 7
    dist_q7[22] = c;  // Etat 23

    printf("Distribution initiale :\n");
    printf("  Etat 3  : %.5f\n", a);
    printf("  Etat 7  : %.5f\n", b);
    printf("  Etat 23 : %.5f\n", c);

    // Calcul pour n = 1, 2, 10, 50 pas
    for (int k = 0; k < 4; k++) {
        int npas = pas_Q7[k];

        double* dist_n = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) dist_n[i] = dist_q7[i];

        for (int step = 0; step < npas; step++) {
            double* next = malloc(n * sizeof(double));

            for (int j = 0; j < n; j++) {
                next[j] = 0.0;
                for (int i = 0; i < n; i++)
                    next[j] += dist_n[i] * M[i][j];
            }

            free(dist_n);
            dist_n = next;
        }

        printf("\nDistribution apres n = %d pas :\n", npas);
        for (int i = 0; i < n; i++) {
            if (dist_n[i] > 0.0001)
                printf("  Etat %d : %.5f\n", i+1, dist_n[i]);
        }

        free(dist_n);
    }

    // Distribution limite
    for (int i = 0; i < n; i++) dist_limite_q7[i] = dist_q7[i];

    for (int iter = 1; iter <= 1000; iter++) {
        double* next = malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_limite_q7[i] * M[i][j];
        }

        double diff = 0.0;
        for (int i = 0; i < n; i++) {
            diff += fabs(next[i] - dist_limite_q7[i]);
            dist_limite_q7[i] = next[i];
        }

        free(next);

        if (diff < 1e-6) break;
    }

    printf("\nDistribution limite (Scenario %d) :\n", scenario+1);
    for (int i = 0; i < n; i++) {
        if (dist_limite_q7[i] > 0.0001)
            printf("  Etat %d : %.5f\n", i+1, dist_limite_q7[i]);
    }

    // Sauvegarder pour comparaison
    for (int i = 0; i < n; i++) {
        limites_q7c[scenario][i] = dist_limite_q7[i];
    }
}

// ========================================
// COMPARAISON DES DISTRIBUTIONS LIMITES
// ========================================

printf("\n\n=== ANALYSE : Les distributions limites sont-elles identiques ? ===\n");

int identiques_q7 = 1;
for (int s = 1; s < nb_scenarios_q7; s++) {
    double diff_totale = 0.0;
    for (int i = 0; i < n; i++) {
        diff_totale += fabs(limites_q7c[s][i] - limites_q7c[0][i]);
    }

    if (diff_totale > 1e-4) {
        identiques_q7 = 0;
        printf("[DIFF] Scenario %d differe du scenario 1 (difference = %.6f)\n",
               s+1, diff_totale);
    }
}

if (identiques_q7) {
    printf("\n[CONCLUSION PARTIE C]\n");
    printf("Toutes les distributions limites sont IDENTIQUES !\n");
    printf("La distribution limite NE DEPEND PAS des parametres (a, b, c).\n");
    printf("\nCela signifie que {3, 7, 23} forme une classe finale APERIODIQUE.\n");
} else {
    printf("\n[CONCLUSION PARTIE C]\n");
    printf("Les distributions limites DEPENDENT des parametres (a, b, c).\n");
}

// Export CSV pour graphiques Excel
FILE* f_q7 = fopen("question7_distributions.csv", "w");
if (f_q7) {
    fprintf(f_q7, "n,Etat3,Etat7,Etat23\n");

    // Reinitialiser depuis l'etat 3
    for (int i = 0; i < n; i++) dist_q7[i] = 0.0;
    dist_q7[2] = 1.0;

    for (int step = 0; step <= 100; step++) {
        fprintf(f_q7, "%d,%.6f,%.6f,%.6f\n",
                step, dist_q7[2], dist_q7[6], dist_q7[22]);

        double* next = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            next[j] = 0.0;
            for (int i = 0; i < n; i++)
                next[j] += dist_q7[i] * M[i][j];
        }
        for (int i = 0; i < n; i++) dist_q7[i] = next[i];
        free(next);
    }

    fclose(f_q7);
    printf("\n[EXPORT] Fichier 'question7_distributions.csv' cree pour tracer les graphes.\n");
}

// Liberation memoire
for (int s = 0; s < nb_scenarios_q7; s++) {
    free(limites_q7c[s]);
}
free(limites_q7c);
free(dist_q7);
free(dist_limite_q7);

printf("\n========================================\n");
printf("      FIN DE LA QUESTION 7\n");
printf("========================================\n\n");

    /*****************************/
    /*        QUESTION 12        */
    /*****************************/
    printf("\n=============================\n");
    printf("        QUESTION 12\n");
    printf("=============================\n");

    // ----- CLASSES FINALES -----
    int C1[] = {11,18,4,26,27,1};
    int C2[] = {5,12,21,25,2};
    int C3[] = {6,20,17};
    int C5[] = {16,9,8};

    int sizeC1 = 6, sizeC2 = 5, sizeC3 = 3, sizeC5 = 3;

    // ----- ÉTATS INITIAUX -----
    int S[] = {10,19,22,24};
    int nbS = 4;

    // ----- CALCUL DE M^1000 -----
    double** Mpow = creatematricezero(n);
    copymatrice(M, Mpow, n);

    for (int t = 0; t < 1000; t++) {
        double** newM = multiplymatrice(Mpow, M, n);

        // libérer l’ancienne matrice
        for (int i = 0; i < n; i++) free(Mpow[i]);
        free(Mpow);

        Mpow = newM;
    }

    printf("M^1000 calcule.\n\n");

    // ----- CALCUL DES PROBABILITÉS D’ABSORPTION -----
    for (int a = 0; a < nbS; a++) {

        int s = S[a] - 1;   // index 0-based

        // vecteur initial e_s
        double* pi = malloc(n * sizeof(double));
        double* out = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) pi[i] = 0.0;
        pi[s] = 1.0;

        // pi_final = pi × M^1000
        vec_mul_mat(pi, Mpow, out, n);

        // Sommes dans les classes finales
        double p1 = 0, p2 = 0, p3 = 0, p5 = 0;

        for (int i = 0; i < sizeC1; i++) p1 += out[C1[i] - 1];
        for (int i = 0; i < sizeC2; i++) p2 += out[C2[i] - 1];
        for (int i = 0; i < sizeC3; i++) p3 += out[C3[i] - 1];
        for (int i = 0; i < sizeC5; i++) p5 += out[C5[i] - 1];

        printf("Etat %d -> C1=%.6f  |  C2=%.6f  |  C3=%.6f  |  C5=%.6f\n",
               S[a], p1, p2, p3, p5);

        free(pi);
        free(out);
    }



    for (int i = 0; i < n; i++) free(M[i]);
free(M);


return 0;
}
