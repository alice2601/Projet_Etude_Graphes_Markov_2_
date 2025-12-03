//
// Created by alice on 19/11/2025.
//

#include <math.h>
#include "matrice.h"

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
    double** M = creatematricezero(n);
    if (M == NULL) {
        printf("Erreur allocation matrice\n");
        return NULL;
    }

    // Remplissage temporaire des poids (non normalisés)
    for (int i = 0; i < n; i++) {
        t_cell* current = adj->tab[i].head;
        while (current != NULL) {
            int j = current->sommet_arrive - 1;
            double w = current->proba; // si ce sont des poids
            if (j >= 0 && j < n) {
                M[i][j] = w;
            } else {
                printf("Warning: indice hors-limite i=%d j=%d\n", i, j);
            }
            current = current->next;
        }
    }

    // Normalisation ligne par ligne (sorties de i)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) sum += M[i][j];

        if (sum > 0.0) {
            for (int j = 0; j < n; j++) M[i][j] /= sum;
        } else {
            // Pas de sortie: rendre le noeud absorbant (ou distribuer uniformément)
            // Option A: auto-boucle
            M[i][i] = 1.0;
            // Option B (alternative): distribuer uniformément
            // for (int j = 0; j < n; j++) M[i][j] = 1.0 / n;
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
            //printf("DEBUG: sub[%d][%d] = M[%d][%d] = %.2f\n",
                   //i, j, original_row, original_col, matrix[original_row][original_col]);
        }
    }

    return sub;
}

void calcul_stationnaire(double** sous_matrice, int taille, double* distribution) {
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
        for (int i = 0; i < taille; i++) {
            next[i] = 0.0;
            for (int j = 0; j < taille; j++) {
                next[i] += distribution[j] * sous_matrice[j][i];
            }
        }


        //test
        double sum = 0.0;
        for (int i = 0; i < taille; i++) {
            sum += next[i];
        }

        if (sum < 1e-10) {
            for (int i = 0; i < taille; i++) {
                distribution[i] = 0.0;
            }
            free(next);
            return;
        }

        for (int i = 0; i < taille; i++) {
            next[i] /= sum;
        }

        // Calculer la différence
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
        calcul_stationnaire(sub_M, comp.nb_sommets, stationary);

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



//ETAPE 3


int gcd(int *vals, int nbvals) {
    // Cas avec aucune valeur
    if (nbvals == 0) return 0;

    // On commence avec la première valeur
    int result = vals[0];

    // On calcule le PGCD avec chaque valeur suivante
    for (int i = 1; i < nbvals; i++) {
        int a = result;      // Résultat précédent
        int b = vals[i];     // Valeur actuelle

        // Algorithme d'Euclide
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }

        // Après la boucle, 'a' contient le PGCD de result et vals[i]
        result = a;
    }

    return result;
}






int getPeriod(double** sub_matrix, int n)
{
    // Tableau pour stocker les longueurs de cycles détectées
    int *periods = (int *)malloc(n * sizeof(int));
    int period_count = 0;  // Nombre de périodes détectées

    // Matrices pour les calculs de puissances
    // power_matrix contiendra la matrice M^k à chaque itération
    double** power_matrix = creatematricezero(n);


    // Initialisation : power_matrix = M^1
    copymatrice(sub_matrix, power_matrix, n);

    // On teste pour toutes les puissances de 1 à n
    for (int cpt = 1; cpt <= n; cpt++) {
        // Vérifier si la DIAGONALE contient des valeurs différentes de 0
        int diag_nonzero = 0;
        for (int i = 0; i < n; i++)
        {
            // Si M^cpt[i][i] > 0, on peut revenir au sommet i en cpt étapes
            if (power_matrix[i][i] > 0.0f)
            {
                diag_nonzero = 1;
                break;  // Pas besoin de vérifier les autres
            }
        }

        // Si on a trouvé des valeurs non-nulles sur la diagonale,
        // cpt est une longueur de cycle possible
        if (diag_nonzero) {
            periods[period_count] = cpt;
            period_count++;
        }

        // Calculer la puissance suivante : M^(cpt+1) = M^cpt × M
        if (cpt<n) {
            double** temp_result = multiplymatrice(power_matrix, sub_matrix, n);

            // Libérer l'ancienne power_matrix
            for (int i = 0; i < n; i++) {
                free(power_matrix[i]);
            }
            free(power_matrix);

            // Copier le résultat dans power_matrix pour la prochaine itération
            power_matrix = temp_result;
        }

    }



        // Calculer le PGCD de toutes les longueurs de cycles détectées
        int periode = gcd(periods, period_count);

        // Libération de la mémoire
        free(periods);
        for (int i = 0; i < n; i++) {
            free(power_matrix[i]);
        }
        free(power_matrix);

        return periode;
    }






void calculer_distribution_periodiques(double** sous_matrice, int taille,
                                   int periode, double** distributions) {
printf("  Calcul des %d distributions periodiques...\n", periode);

double** M_periode = creatematricezero(taille);
copymatrice(sous_matrice, M_periode, taille);

for (int i = 1; i < periode; i++) {
    double** temp = multiplymatrice(M_periode, sous_matrice, taille);
    for (int r = 0; r < taille; r++) {
        free(M_periode[r]);
    }
    free(M_periode);
    M_periode = temp;
}

for (int p = 0; p < periode; p++) {
    double* dist_init = (double*)malloc(taille * sizeof(double));
    for (int i = 0; i < taille; i++) {
        dist_init[i] = 1.0 / taille;
    }

    for (int step = 0; step < p; step++) {
        double* next = (double*)malloc(taille * sizeof(double));
        for (int i = 0; i < taille; i++) {
            next[i] = 0.0;
            for (int j = 0; j < taille; j++) {
                next[i] += dist_init[j] * sous_matrice[j][i];
            }
        }
        free(dist_init);
        dist_init = next;
    }

    double* next = (double*)malloc(taille * sizeof(double));
    double diff;
    int iterations = 0;
    const double epsilon = 1e-10;

    do {
        diff = 0.0;
        for (int i = 0; i < taille; i++) {
            next[i] = 0.0;
            for (int j = 0; j < taille; j++) {
                next[i] += dist_init[j] * M_periode[j][i];
            }
        }

        double sum = 0.0;
        for (int i = 0; i < taille; i++) {
            sum += next[i];
        }
        for (int i = 0; i < taille; i++) {
            next[i] /= sum;
        }

        for (int i = 0; i < taille; i++) {
            diff += fabs(next[i] - dist_init[i]);
            dist_init[i] = next[i];
        }

        iterations++;
        if (iterations > 10000) break;

    } while (diff > epsilon);

    for (int i = 0; i < taille; i++) {
        distributions[p][i] = dist_init[i];
    }

    free(dist_init);
    free(next);
}

for (int i = 0; i < taille; i++) {
    free(M_periode[i]);
}
free(M_periode);
}






    void analyser_composantes_periodicite(double** M, int n, t_partition* partition) {
    printf("\n ANALYSE DES COMPOSANTES AVEC PERIODICITE \n\n");

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

        // Extraire la sous-matrice
        double** sub_M = subMatrix(M, n, partition, comp_index);
        if (sub_M == NULL) {
            printf("Erreur lors de l'extraction de la sous-matrice\n");
            continue;
        }

        printf("Sous-matrice de transition:\n");
        printmatrice(sub_M, comp.nb_sommets);

        // *** NOUVEAU : Calcul de la période ***
        int periode = getPeriod(sub_M, comp.nb_sommets);
        printf("PERIODE de la composante: %d\n", periode);

        if (periode == 1) {
            // Classe apériodique : une seule distribution stationnaire
            printf("  => Composante APERIODIQUE\n");

            double *stationary = (double*)malloc(comp.nb_sommets * sizeof(double));
            calcul_stationnaire(sub_M, comp.nb_sommets, stationary);

            printf("Distribution stationnaire unique:\n");
            for (int i = 0; i < comp.nb_sommets; i++) {
                printf("  Sommet %d: %.4f\n", comp.head[i].id, stationary[i]);
            }
            free(stationary);

        } else {
            // Classe périodique : plusieurs distributions stationnaires
            printf("  => Composante PERIODIQUE (periode = %d)\n", periode);
            printf("  Il existe %d distributions stationnaires qui alternent cycliquement\n", periode);

            // Allouer un tableau 2D pour les distributions
            double** distributions = (double**)malloc(periode * sizeof(double*));
            for (int p = 0; p < periode; p++) {
                distributions[p] = (double*)malloc(comp.nb_sommets * sizeof(double));
            }

            calculer_distribution_periodiques(sub_M, comp.nb_sommets, periode, distributions);

            // Afficher les distributions périodiques
            for (int p = 0; p < periode; p++) {
                printf("\n  Distribution periodique #%d (apres %d etapes modulo %d):\n",
                       p+1, p, periode);
                for (int i = 0; i < comp.nb_sommets; i++) {
                    printf("    Sommet %d: %.4f\n", comp.head[i].id, distributions[p][i]);
                }
            }

            // Libération
            for (int p = 0; p < periode; p++) {
                free(distributions[p]);
            }
            free(distributions);
        }

        printf("\n");

        // Libération de la sous-matrice
        for (int i = 0; i < comp.nb_sommets; i++) {
            free(sub_M[i]);
        }
        free(sub_M);
    }
}