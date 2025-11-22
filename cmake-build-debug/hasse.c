#include <stdlib.h>
#include <stdio.h>
#include "hasse.h"

/**
 * Retire les liens transitifs (redondances) du tableau de liens
 * Un lien (A->C) est redondant s'il existe un chemin A->B->C
 */
void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->nb_links)
    {
        t_link link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;

        while (j < p_link_array->nb_links && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];

                // Si link1 et link2 partent de la même classe
                if (link1.classe_depart == link2.classe_depart)
                {
                    // Chercher un lien qui va de link2.arrivee vers link1.arrivee
                    int k = 0;
                    while (k < p_link_array->nb_links && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = p_link_array->links[k];

                            // Si on trouve un chemin link1.depart -> link2.arrivee -> link1.arrivee
                            // alors link1 est redondant
                            if ((link3.classe_depart == link2.classe_arrivee) &&
                                (link3.classe_arrivee == link1.classe_arrivee))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }

        if (to_remove)
        {
            // Supprimer link1 en le remplaçant par le dernier lien
            p_link_array->links[i] = p_link_array->links[p_link_array->nb_links - 1];
            p_link_array->nb_links--;
        }
        else
        {
            i++;
        }
    }
}

/**
 * Génère le diagramme de Hasse SIMPLIFIE (sans redondances) au format Mermaid
 */
void generateMermaidSimplified(t_partition* partition, t_list_adjacente* graphe, const char* output_filename) {
    if (partition == NULL || graphe == NULL) {
        printf("Erreur : partition ou graphe NULL\n");
        return;
    }

    FILE* file = fopen(output_filename, "wt");
    if (file == NULL) {
        perror("Impossible de creer le fichier Mermaid simplifie");
        return;
    }

    // En-tête Mermaid
    fprintf(file, "---\n");
    fprintf(file, "config:\n");
    fprintf(file, "  layout: elk\n");
    fprintf(file, "  theme: neo\n");
    fprintf(file, "  look: neo\n");
    fprintf(file, "---\n");
    fprintf(file, "flowchart LR\n");

    // Déclarer toutes les classes
    for (int i = 0; i < partition->nb_classes; i++) {
        fprintf(file, "  %s((\"%s: {",
                partition->classes[i].name,
                partition->classes[i].name);

        for (int j = 0; j < partition->classes[i].nb_sommets; j++) {
            fprintf(file, "%d", partition->classes[i].head[j].id);
            if (j < partition->classes[i].nb_sommets - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "}\"))\n");
    }

    // Trouver les liens entre classes
    t_link_array* links = findClassLinks(partition, graphe);

    int nb_links_avant = links->nb_links;

    // RETIRER LES REDONDANCES
    removeTransitiveLinks(links);

    int nb_links_apres = links->nb_links;

    // Écrire les liens
    for (int i = 0; i < links->nb_links; i++) {
        int depart = links->links[i].classe_depart;
        int arrivee = links->links[i].classe_arrivee;

        fprintf(file, "  %s --> %s\n",
                partition->classes[depart].name,
                partition->classes[arrivee].name);
    }

    fclose(file);

    printf("\nDiagramme de Hasse SIMPLIFIE genere : '%s'\n", output_filename);
    printf("Liens avant simplification : %d\n", nb_links_avant);
    printf("Liens apres simplification : %d\n", nb_links_apres);
    printf("Redondances retirees : %d\n", nb_links_avant - nb_links_apres);

    // Libérer la mémoire
    free(links->links);
    free(links);
}