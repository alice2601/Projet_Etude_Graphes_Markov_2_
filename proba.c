//
// Created by alice on 30/11/2025.
//

// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proba.h" // ta header, contient prototypes

// lit une matrice carrée n x n depuis un fichier texte (séparateurs: espace/tab/newline)
double** read_matrix_file(const char* filename, int n) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        return NULL;
    }
    double** M = creatematricezero(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fscanf(f, "%lf", &M[i][j]) != 1) {
                fprintf(stderr, "Erreur lecture matrice à %d,%d\n", i, j);
                // libérer et quitter
                for (int r = 0; r < n; ++r) free(M[r]);
                free(M);
                fclose(f);
                return NULL;
            }
        }
    }
    fclose(f);
    return M;
}

// multiplie un vecteur ligne pi (taille n) par une matrice P (n x n), résultat dans out (taille n)
void vec_mul_mat(double* pi, double** P, double* out, int n) {
    for (int j = 0; j < n; ++j) out[j] = 0.0;
    for (int i = 0; i < n; ++i) {
        if (pi[i] == 0.0) continue;
        for (int j = 0; j < n; ++j) {
            out[j] += pi[i] * P[i][j];
        }
    }
}

// imprime vecteur probabilité
void print_vector(double* v, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%2d: %.6f  ", i+1, v[i]);
        if ((i+1) % 6 == 0) printf("\n");
    }
    printf("\n");
}

double** lire_sparse(const char* filename, int n) {
    FILE* f = fopen(filename, "r");
    if (!f) { perror("fopen"); return NULL; }

    double** M = creatematricezero(n);

    int i, j; double val;
    while (fscanf(f, "%d %d %lf", &i, &j, &val) == 3) {
        M[i-1][j-1] = val;
    }
    fclose(f);
    return M;
}