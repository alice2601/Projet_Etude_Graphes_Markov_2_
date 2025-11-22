//
// Created by alice on 19/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"//je l'ai ajouté au cas où
#include "fonction.h"
#ifndef TP_MATRICE_H
#define TP_MATRICE_H
// ici on créer une matrice n×n initialisée à 0
double** creatematricezero(int n);

// ici construction de la matrice de transition à partir d’une liste d’adjacence
double** createtransitionmatrice(t_list_adjacente* graph);// là c'est soit t_class soit t_partition

// fonction qui recopie les valeurs de A dans B (mêmes dimensions)
void copymatrice(double** A, double** B, int n);

// Multiplication de deux matrices carrées n×n
// Retourne une nouvelle matrice C = A × B
double** multiplymatrice(double** A, double** B, int n);

// Différence entre deux matrices : attention on va faire la somme des valeurs absolues
// |M[i][j] - N[i][j]|
double diffmatrice(double** M, double** N, int n);

// affichage
void printmatrice(double** M, int n);

double** subMatrix(double** matrix, int n, t_partition* partition, int compo_index);

void analyserComposantesMarkov(double** M, int n, t_partition* partition);

#endif //TP_MATRICE_H