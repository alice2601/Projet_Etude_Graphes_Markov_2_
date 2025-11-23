//
// Created by alice on 19/11/2025.
//

#include <math.h>
#include "matrice.h"//ici pareil je ne sais pas si il faut l'ajouter en cmakedebug ou juste normalement

double** creatematricezero(int n) {
    double** M = (double**)malloc(n * sizeof(double*));
    if (M == NULL) {
        printf("Erreur\n");
        return 0;}
    for (int i = 0; i < n; i++) {
        M[i] = (double*)malloc(n * sizeof(double));
        if (M[i] == NULL) {
            printf("Erreur\n");
            return 0;}
        for (int j = 0; j < n; j++) {
            M[i][j] = 0.0;
        }
    }
    return M;
}
double** createtransitionmatrice(t_list_adjacente* adj) {
    int n = adj->taille;
//création d'un matrice n x n remplie de zeros
    double** M = creatematricezero(n);
    if (M == NULL) {
        printf("Erreur\n");
        return NULL;}
//pour chaque sommet i
    for (int i = 0; i < n; i++) {
       t_cell* current = adj->tab[i].head; // pointeur temporaire vers la tête de la liste
        while (current != NULL) {// Parcourir la liste des voisins
            int j = current->sommet_arrive - 1; // numéro du voisin
            double p = current->proba; // probabilité de la transition de i à j
            M[i][j] = p; // on rempli la matrice
            current = current->next;
        }
    }
return M;
}

void copymatrice(double** A, double** B, int n){
// A et B sont des matrices n x n qu'on a créé en amont
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
    }
return;
}

double** multiplymatrice(double** A, double** B, int n){
    double** C = creatematricezero(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }

        }
    }
return C;
}

double diffmatrice(double** M, double** N, int n){
    double diff = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            diff += fabs(M[i][j] - N[i][j]);
        }
    }
return diff;
}

void printmatrice(double** M, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", M[i][j]);}
        printf("\n");
    }
printf("\n");
}

double** subMatrix(double** matrix, int n, t_partition* partition, int compo_index) {
    if (compo_index < 0 || compo_index >= partition->nb_classes) {
        printf("Erreur : indice de composante invalide (%d sur %d composantes)\n",
               compo_index, partition->nb_classes);
        return NULL;
    }

    t_classe comp = partition->classes[compo_index];
    double** sub = creatematricezero(comp.nb_sommets);


    // Remplir la sous-matrice AVEC -1 pour convertir 1-10 → 0-9
    for (int i = 0; i < comp.nb_sommets; i++) {
        for (int j = 0; j < comp.nb_sommets; j++) {
            int original_row = comp.head[i].id - 1;  // Gardez le -1
            int original_col = comp.head[j].id - 1;  // Gardez le -1

            // Vérification des indices
            if (original_row < 0 || original_row >= n || original_col < 0 || original_col >= n) {
                printf("ERREUR: Indice hors limites [%d][%d] pour matrice taille %d\n",
                       original_row, original_col, n);
                continue;
            }

            sub[i][j] = matrix[original_row][original_col];
            printf("DEBUG: sub[%d][%d] = M[%d][%d] = %.2f\n",
                   i, j, original_row, original_col, matrix[original_row][original_col]);
        }
    }

    return sub;
}

void calculerDistributionStationnaire(double** sous_matrice, int taille, double* distribution) {
    if (taille == 0) return;

    // Distribution uniforme initiale
    for (int i = 0; i < taille; i++) {
        distribution[i] = 1.0 / taille;
    }

    double *next = (double*)malloc(taille * sizeof(double));
    double diff;
    int iterations = 0;
    const double epsilon = 1e-10;

    do {
        diff = 0.0;

        // Multiplier : distribution * matrice
        for (int j = 0; j < taille; j++) {
            next[j] = 0.0;
            for (int i = 0; i < taille; i++) {
                next[j] += distribution[i] * sous_matrice[i][j];
            }
        }

        // Calculer la différence pour vérifier la convergence
        for (int i = 0; i < taille; i++) {
            diff += fabs(next[i] - distribution[i]);
            distribution[i] = next[i];
        }

        iterations++;
        if (iterations > 10000) {
            printf("  Attention: Convergence non atteinte après 10000 iterations\n");
            break;
        }

    } while (diff > epsilon);

    free(next);
}

void analyserComposantesMarkov(double** M, int n, t_partition* partition) {
    printf("\n");


    if (partition == NULL || partition->nb_classes == 0) {
        printf("Aucune composante trouvee dans le graphe.\n");
        return;
    }

    printf("Nombre total de composantes fortement connexes: %d\n\n", partition->nb_classes);

    for (int comp_index = 0; comp_index < partition->nb_classes; comp_index++) {
        t_classe comp = partition->classes[comp_index];

        printf("--- Composante %s (taille: %d) ---\n", comp.name, comp.nb_sommets);
        printf("Sommets: ");
        for (int i = 0; i < comp.nb_sommets; i++) {
            printf("%d ", comp.head[i].id);
        }
        printf("\n");

        // Extraire la sous-matrice de la composante
        double** sub_M = subMatrix(M, n, partition, comp_index);
        if (sub_M == NULL) {
            printf("Erreur lors de l'extraction de la sous-matrice\n");
            continue;
        }

        printf("Sous-matrice de transition:\n");
        printmatrice(sub_M, comp.nb_sommets);

        // Calculer la distribution stationnaire
        double *stationary = (double*)malloc(comp.nb_sommets * sizeof(double));
        calculerDistributionStationnaire(sub_M, comp.nb_sommets, stationary);

        printf("Distribution stationnaire:\n");
        double sum = 0.0;
        for (int i = 0; i < comp.nb_sommets; i++) {
            printf("  Sommet %d: %.4f\n", comp.head[i].id, stationary[i]);
            sum += stationary[i];
        }
        printf("  Somme des probabilites: %.6f\n", sum);

        // Analyser le type de composante
        if (comp.nb_sommets == 1) {
            printf("  Type: Composante absorbante (1 seul sommet)\n");
        } else {
            printf("  Type: Composante persistante\n");
        }

        printf("\n");

        // Libérer la mémoire
        free(stationary);
        for (int i = 0; i < comp.nb_sommets; i++) {
            free(sub_M[i]);
        }
        free(sub_M);
    }
}