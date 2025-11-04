//
// Created by khela on 27/10/2025.
//

#include "fonction.h"

t_cell *createCell(int val, float proba)
{
    t_cell *nouv;
    nouv =(t_cell *)malloc(sizeof(t_cell));
    nouv->sommet_arrive = val;
    nouv->proba = proba;
    nouv->next =NULL;
    return nouv;
}


t_list* createEmptyList()
{
    t_list* nouvliste = (t_list*)malloc(sizeof(t_list));
    nouvliste->head = NULL;
    return nouvliste;
}



t_list* addCell(t_list *ptr_list, int val, float proba)
{
    t_cell *nouv = createCell(val, proba);
    nouv->next = ptr_list->head;
    ptr_list->head= nouv;
    return ptr_list;
}


void displayList(t_list* l) {
    t_cell* curr;
    curr=l->head;
    if (curr==NULL){
        printf("Liste vide\n");
    }
    while (curr !=NULL) {
        printf(" →%d(%.2f)", curr->sommet_arrive, curr->proba);
        curr =curr->next ;
    }

}



t_list_adjacente* create_Adj_Empty_List(int taille) {
    t_list_adjacente* new_listeADJ= malloc(sizeof(t_list_adjacente));

    new_listeADJ->taille = taille;
    new_listeADJ->tab= malloc(taille * sizeof(t_list));

    for (int i=0; i<taille; i++) {
        new_listeADJ->tab[i].head = NULL;

    }
    return new_listeADJ;
}


void displayAdjacente(t_list_adjacente* myListeAdja) {
    for (int i=0; i<myListeAdja->taille; i++) {
        printf("Liste pour le sommet %d:", i+1);
        displayList(&myListeAdja->tab[i]);
        printf("\n");
    }

}

t_list_adjacente* readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    int nbvert;
    int depart;
    int arrivee;
    float proba;


    t_list_adjacente* mongraphe;

    if (file == NULL) {
        perror("Impossible d’ouvrir le fichier");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Erreur lors de la lecture du nombre de sommets");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    mongraphe = create_Adj_Empty_List(nbvert);

    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3) {

        addCell(&mongraphe->tab[depart - 1], arrivee, proba);
    }

    fclose(file);

    return mongraphe;
}

/*
 * On vérifie si un graphe est un graphe de Markov.
 * Pour chaque sommet i : on additionne toutes les probabilités des arêtes sortantes
et on vérifie que la somme est entre 0.99 et 1.00 (inclus)
 * /!\ Si un sommet n'est pas valide, on l'affiche lui et sa somme.
 * Sinon on affiche que le graphe est un graphe de Markov.
 */
void verifiersigraphMarkov(t_list_adjacente* mongraphe) {
    if (mongraphe == NULL) {
        printf("Le graphe est vide, il n'y a rien à verifier.\n");
        return;
    }
    int graphMarkov = 1;

    for (int i = 0; i < mongraphe->taille; i++) {
        float somme = 0.0f;
        t_cell* ptr = mongraphe->tab[i].head;
        while (ptr != NULL) {
            somme += ptr->proba;
            ptr = ptr->next;
        }
        if (somme < 0.99f || somme > 1.00f) {

            printf("La somme des probabilités du sommet %d est %.2f\n", i + 1, somme);
            graphMarkov = 0;
        }
    }

    if (graphMarkov==1) {
        printf("Le graphe est un graphe de Markov\n");
    }
    else {
        printf("Le graphe n'est pas un graphe de Markov\n");
    }
}

/*
 * Fonction getId : convertit un numéro de sommet en identifiant alphabétique
 * 1 -> "A", 2 -> "B", ...
 * Buffer --  stocker identifiant
 * Conversion en base 26 (comme Excel : A, B, ..., Z, AA, AB, ...)
 * puis inverser la chaîne car on l'a construite à l'envers
 */
char* getId(int num) {
    static char buffers[100][3];  // Multiple buffers
    static int counter = 0;

    if (num <= 0) num = 1;
    if (num > 52) num = 52;

    char* buffer = buffers[counter++ % 100];

    if (num <= 26) {
        buffer[0] = 'A' + (num - 1);
        buffer[1] = '\0';
    } else {
        // Pour AA, AB, etc.
        buffer[0] = 'A' + ((num - 27) / 26);
        buffer[1] = 'A' + ((num - 27) % 26);
        buffer[2] = '\0';
    }

    return buffer;
}



/*
 * Fonction generateMermaidFile : génère un fichier texte au format Mermaid
 * à partir d'une liste d'adjacence (graphe de Markov)
 * puis on va écrire l'en-tête du fichier Mermaid
 * ensuite on va déclarer tous les sommets avec leurs numéros + écrire toutes les arêtes avec leurs probabilités
 */
void generateMermaidFile(t_list_adjacente* graphe, const char* output_filename) {
    if (graphe == NULL) {
        printf("Erreur : le graphe est NULL\n");
        return;
    }

    FILE* file = fopen(output_filename, "wt");

    if (file == NULL) {
        perror("Impossible de créer le fichier Mermaid");
        return;
    }


    fprintf(file, "---\n");
    fprintf(file, "config:\n");
    fprintf(file, "  layout: elk\n");
    fprintf(file, "  theme: neo\n");
    fprintf(file, "  look: neo\n");
    fprintf(file, "---\n");
    fprintf(file, "flowchart LR\n");


    for (int i = 0; i < graphe->taille; i++) {
        fprintf(file, "  %s((%d))\n", getId(i + 1), i + 1);
    }


    for (int i = 0; i < graphe->taille; i++) {
        t_cell* current = graphe->tab[i].head;
        printf("DEBUG Sommet %d:", i+1);

        while (current != NULL) {    // Format : A -->|0.95|B
            printf(" ->%d(%.2f)", current->sommet_arrive, current->proba);
            fprintf(file, "  %s -->|%.2f|%s\n",
                    getId(i + 1),
                    current->proba,
                    getId(current->sommet_arrive));

            current = current->next;
        }
        printf("\n");
    }

    fclose(file);

}
