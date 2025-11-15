#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarjan.h"

t_tarjan_vertex* creertableau(int taille) {
    if(taille <= 0) return NULL;

    t_tarjan_vertex* tableau = malloc(sizeof(t_tarjan_vertex) * taille);
    if(tableau == NULL) return NULL;
    
    for (int i = 0; i < taille; i++) {
        tableau[i].id = i + 1;         // identifiant = numéro du sommet (commence à 1)
        tableau[i].number = -1;        // numéro temporaire initialisé à -1
        tableau[i].numberacces = -1;   // numéro accessible initialisé à -1
        tableau[i].indic = false;      // pas encore dans la pile
    }

    return tableau;
}

void parcours(int a, t_tarjan_vertex* sommets, t_stack* pile, int* compteur, t_infos* infos) {
    sommets[a].numberacces = *compteur;
    sommets[a].number = *compteur;
    (*compteur)++;

    *pile = empiler(*pile, sommets[a]);
    sommets[a].indic = true;

    // Parcourir les voisins
    for (int i = 0; i < infos->nb_voisins[a]; i++) {
        int voisin = infos->adj[a][i];

        if (sommets[voisin].number == -1) {
            parcours(voisin, sommets, pile, compteur, infos);
            if (sommets[voisin].numberacces < sommets[a].numberacces) {
                sommets[a].numberacces = sommets[voisin].numberacces;
            }
        }
        else if (sommets[voisin].indic) {
            if (sommets[voisin].numberacces < sommets[a].numberacces) {
                sommets[a].numberacces = sommets[voisin].numberacces;
            }
        }
    }

    // Si le sommet est une racine d'une composante
    if (sommets[a].numberacces == sommets[a].number) {
        t_classe new_classe;
        new_classe.nb_sommets = 0;

        // Générer automatiquement le nom de la classe (C1, C2, C3...)
        sprintf(new_classe.name, "C%d", infos->partition->nb_classes + 1);

        new_classe.head = NULL;
        t_tarjan_vertex sommet_temp;

        // Dépiler jusqu'au sommet racine
        do {
            *pile = depiler(*pile, &sommet_temp);
            // CORRECTION CRITIQUE : mettre à jour l'indic dans le tableau original
            sommets[sommet_temp.id - 1].indic = false;

            new_classe.nb_sommets++;
            new_classe.head = realloc(new_classe.head, sizeof(t_tarjan_vertex) * new_classe.nb_sommets);
            new_classe.head[new_classe.nb_sommets - 1] = sommet_temp;

        } while (sommet_temp.id != sommets[a].id);

        // Ajouter la classe à la partition
        infos->partition->nb_classes++;
        infos->partition->classes = realloc(infos->partition->classes,
                                           sizeof(t_classe) * infos->partition->nb_classes);
        infos->partition->classes[infos->partition->nb_classes - 1] = new_classe;
    }
}

t_partition* tarjan(int nb_sommets, int** adj, int* nb_voisins) {
    // Initialisation des sommets
    t_tarjan_vertex* sommets = creertableau(nb_sommets);
    if (!sommets) {
        printf("Erreur lors de la creation du tableau de sommets\n");
        return NULL;
    }

    // Initialiser la partition
    t_partition* partition = malloc(sizeof(t_partition));
    partition->nb_classes = 0;
    partition->classes = NULL;

    // Créer une pile vide
    t_stack pile = creer_stack();

    // Initialiser la structure d'infos
    t_infos* infos = malloc(sizeof(t_infos));
    infos->partition = partition;
    infos->nb_voisins = nb_voisins;
    infos->adj = adj;

    // Initialiser le compteur
    int compteur = 0;

    // DEBUG
    printf("DEBUG Tarjan - Debut du parcours de %d sommets\n", nb_sommets);

    // Parcourir tous les sommets
    for (int i = 0; i < nb_sommets; i++) {
        if (sommets[i].number == -1) {
            //printf("DEBUG Tarjan - Visite du sommet %d (id=%d)\n", i, sommets[i].id);
            parcours(i, sommets, &pile, &compteur, infos);
        } else {
            //printf("DEBUG Tarjan - Sommet %d déjà visité (number=%d)\n", i, sommets[i].number);
        }
    }

    printf("DEBUG Tarjan - Fin du parcours, %d classes trouvees\n", partition->nb_classes);
    
    // Libérer la mémoire
    free(sommets);
    free_stack(pile);
    free(infos);
    
    return partition;
}