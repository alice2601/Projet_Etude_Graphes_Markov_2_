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

void distrib_limite(double* dist, double** M, int n);

void question4(double** M, int n);




//ETAPE 2


// Permet d'extraire une sous-matrice correspondant à une composante spécifique
double** subMatrix(double** matrix, int n, t_partition* partition, int compo_index);


//Permet de calculer la distribution stationnaire d'une composante
void calcul_stationnaire(double** sous_matrice, int taille, double* distribution);



//Permet d'analyser toutes les composantes et afficher leurs distributions stationnaires
void analyserComposantesMarkov(double** M, int n, t_partition* partition);



//ETAPE 3


//Permet de calculer et retourner le PGCD (Plus Grand Commun Diviseur) de plusieurs valeurs
int gcd(int* vals, int nbvals);



//Permet de calculer la période d'une composante fortement connexe
//Reopurne la période : 1 si apériodique ou >1 si périodique
int getPeriod(double ** sub_matrix, int n);



//Permet de ccalculer les distributions stationnaires périodiques
void calculer_distribution_periodiques(double** sous_matrice, int taille, int periode, double** distributions);


//Permeet d'analyser toutes les composantes du graphe, de calculer leur période et d'afficher les distributions stationnaires
void analyser_composantes_periodicite(double** M, int n, t_partition* partition);


#endif //TP_MATRICE_H