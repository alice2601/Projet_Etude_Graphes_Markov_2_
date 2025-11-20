//
// Created by alice on 19/11/2025.
//


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
            int j = current->sommet_arrive; // numéro du voisin
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
return;
}