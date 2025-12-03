//
// Created by alice on 30/11/2025.
//
#include "matrice.h"

#ifndef UNTITLED10_PROBA_H
#define UNTITLED10_PROBA_H
// imprime vecteur probabilité
void print_vector(double* v, int n);
// multiplie un vecteur ligne pi (taille n) par une matrice P (n x n), résultat dans out (taille n)
void vec_mul_mat(double* pi, double** P, double* out, int n);
// lit une matrice carrée n x n depuis un fichier texte (séparateurs: espace/tab/newline)
double** read_matrix_file(const char* filename, int n);
#endif //UNTITLED10_PROBA_H