#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"
#include "fonction.h"

// Structure pour stocker un lien entre deux classes
typedef struct {
    int classe_depart;
    int classe_arrivee;
} t_link;

// Structure pour stocker tous les liens
typedef struct {
    t_link* links;
    int nb_links;
} t_link_array;

/**
 * Crée un tableau vide de liens
 */
t_link_array* createLinkArray() {
    t_link_array* array = malloc(sizeof(t_link_array));
    array->links = NULL;
    array->nb_links = 0;
    return array;
}

/**
 * Vérifie si un lien existe déjà dans le tableau
 */
bool linkExists(t_link_array* array, int depart, int arrivee) {
    for (int i = 0; i < array->nb_links; i++) {
        if (array->links[i].classe_depart == depart &&
            array->links[i].classe_arrivee == arrivee) {
            return true;
        }
    }
    return false;
}

/**
 * Ajoute un lien au tableau s'il n'existe pas déjà
 */
void addLink(t_link_array* array, int depart, int arrivee) {
    if (!linkExists(array, depart, arrivee)) {
        array->nb_links++;
        array->links = realloc(array->links, sizeof(t_link) * array->nb_links);
        array->links[array->nb_links - 1].classe_depart = depart;
        array->links[array->nb_links - 1].classe_arrivee = arrivee;
    }
}

/**
 * Crée un tableau qui indique pour chaque sommet du graphe
 * la classe à laquelle il appartient
 * Retourne un tableau de taille nb_sommets où tableau[i] = numéro de la classe du sommet i+1
 */
int* createSommetToClasseMapping(t_partition* partition, int nb_sommets) {
    int* mapping = malloc(sizeof(int) * nb_sommets);

    // Initialiser à -1 (pas de classe)
    for (int i = 0; i < nb_sommets; i++) {
        mapping[i] = -1;
    }

    // Pour chaque classe
    for (int c = 0; c < partition->nb_classes; c++) {
        // Pour chaque sommet de cette classe
        for (int s = 0; s < partition->classes[c].nb_sommets; s++) {
            int sommet_id = partition->classes[c].head[s].id;
            mapping[sommet_id - 1] = c; // -1 car les sommets commencent à 1
        }
    }

    return mapping;
}

/**
 * Recense tous les liens entre classes
 * Algorithme :
 * Pour chaque sommet i du graphe
 *   Ci = classe à laquelle appartient i
 *   Pour tous les sommets j dans la liste d'adjacence du sommet i
 *     Cj = classe à laquelle appartient j
 *     Si Ci différent de Cj (arête entre classes)
 *       Si le lien (Ci,Cj) n'existe pas
 *         Ajouter le lien (Ci,Cj)
 */
t_link_array* findClassLinks(t_partition* partition, t_list_adjacente* graphe) {
    t_link_array* links = createLinkArray();

    // Créer le mapping sommet -> classe
    int* sommet_to_classe = createSommetToClasseMapping(partition, graphe->taille);

    // Pour chaque sommet du graphe
    for (int i = 0; i < graphe->taille; i++) {
        int Ci = sommet_to_classe[i]; // Classe du sommet i+1

        // Parcourir tous les voisins dans la liste d'adjacence
        t_cell* current = graphe->tab[i].head;
        while (current != NULL) {
            int j = current->sommet_arrive - 1; // -1 car les sommets commencent à 1
            int Cj = sommet_to_classe[j]; // Classe du sommet j

            // Si les classes sont différentes (arête entre classes)
            if (Ci != Cj) {
                addLink(links, Ci, Cj);
            }

            current = current->next;
        }
    }

    free(sommet_to_classe);
    return links;
}

/**
 * Génère le diagramme de Hasse au format Mermaid
 * Affiche les classes (composantes) et les liens entre elles
 * Format identique à la partie 1
 */
void generateHasseMermaidFile(t_partition* partition, t_list_adjacente* graphe, const char* output_filename) {
    if (partition == NULL || graphe == NULL) {
        printf("Erreur : partition ou graphe NULL\n");
        return;
    }

    printf("\n DEBUG generateHasseMermaidFile \n");
    printf("Nombre de classes dans partition : %d\n", partition->nb_classes);
    printf("Taille du graphe : %d sommets\n", graphe->taille);

    FILE* file = fopen(output_filename, "wt");
    if (file == NULL) {
        perror("Impossible de creer le fichier Mermaid pour le diagramme de Hasse");
        return;
    }

    // En-tête Mermaid (identique à la partie 1)
    fprintf(file, "---\n");
    fprintf(file, "config:\n");
    fprintf(file, "  layout: elk\n");
    fprintf(file, "  theme: neo\n");
    fprintf(file, "  look: neo\n");
    fprintf(file, "---\n");
    fprintf(file, "flowchart LR\n"); // LR = Left to Right (comme partie 1)

    // Déclarer toutes les classes avec des doubles cercles
    printf("\nDeclaration des classes :\n");
    for (int i = 0; i < partition->nb_classes; i++) {
        printf("  Classe %d: %s avec %d sommets\n", i, partition->classes[i].name, partition->classes[i].nb_sommets);

        fprintf(file, "  %s((\"%s: {",
                partition->classes[i].name,
                partition->classes[i].name);

        // Afficher les sommets de la classe
        for (int j = 0; j < partition->classes[i].nb_sommets; j++) {
            fprintf(file, "%d", partition->classes[i].head[j].id);
            if (j < partition->classes[i].nb_sommets - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "}\"))\n");
    }

    // Trouver les liens entre classes
    printf("\nRecherche des liens entre classes...\n");
    t_link_array* links = findClassLinks(partition, graphe);

    printf("Nombre de liens trouves : %d\n", links->nb_links);

    // Écrire les liens (sans probabilité, juste des flèches)
    for (int i = 0; i < links->nb_links; i++) {
        int depart = links->links[i].classe_depart;
        int arrivee = links->links[i].classe_arrivee;

        printf("  Lien %d: C%d (%s) --> C%d (%s)\n", i,
               depart, partition->classes[depart].name,
               arrivee, partition->classes[arrivee].name);

        fprintf(file, "  %s --> %s\n",
                partition->classes[depart].name,
                partition->classes[arrivee].name);
    }

    fclose(file);

    printf("\n=== FIN DEBUG ===\n");
    printf("Diagramme de Hasse genere dans '%s'\n", output_filename);
    printf("Nombre de classes : %d\n", partition->nb_classes);
    printf("Nombre de liens entre classes : %d\n", links->nb_links);

    // Libérer la mémoire
    free(links->links);
    free(links);
}

/**
 * Affiche les caractéristiques du graphe (Étape 3 de la partie 2)
 */
void displayGraphCharacteristics(t_partition* partition, t_list_adjacente* graphe) {
    if (partition == NULL || graphe == NULL) {
        printf("Erreur : partition ou graphe NULL\n");
        return;
    }

    printf("\n CARACTERISTIQUES DU GRAPHE \n\n");

    // Trouver les liens entre classes
    t_link_array* links = findClassLinks(partition, graphe);

    // Pour chaque classe, vérifier si elle est transitoire ou persistante
    for (int i = 0; i < partition->nb_classes; i++) {
        bool has_outgoing_link = false;

        // Vérifier s'il existe un lien sortant de cette classe
        for (int j = 0; j < links->nb_links; j++) {
            if (links->links[j].classe_depart == i) {
                has_outgoing_link = true;
                break;
            }
        }

        printf("Classe %s: {", partition->classes[i].name);
        for (int s = 0; s < partition->classes[i].nb_sommets; s++) {
            printf("%d", partition->classes[i].head[s].id);
            if (s < partition->classes[i].nb_sommets - 1) {
                printf(",");
            }
        }
        printf("} est ");

        if (has_outgoing_link) {
            printf("TRANSITOIRE\n");
            printf("  -> Les etats ");
            for (int s = 0; s < partition->classes[i].nb_sommets; s++) {
                printf("%d", partition->classes[i].head[s].id);
                if (s < partition->classes[i].nb_sommets - 1) {
                    printf(", ");
                }
            }
            printf(" sont transitoires\n");
        } else {
            printf("PERSISTANTE\n");
            printf("  -> Les etats ");
            for (int s = 0; s < partition->classes[i].nb_sommets; s++) {
                printf("%d", partition->classes[i].head[s].id);
                if (s < partition->classes[i].nb_sommets - 1) {
                    printf(", ");
                }
            }
            printf(" sont persistants\n");

            // Vérifier si c'est un état absorbant
            if (partition->classes[i].nb_sommets == 1) {
                printf("  -> L'etat %d est ABSORBANT\n", partition->classes[i].head[0].id);
            }
        }
    }

    // Vérifier si le graphe est irréductible
    printf("\nLe graphe de Markov est ");
    if (partition->nb_classes == 1) {
        printf("IRREDUCTIBLE (une seule classe)\n");
    } else {
        printf("NON IRREDUCTIBLE (%d classes)\n", partition->nb_classes);
    }

    // Libérer
    free(links->links);
    free(links);
}