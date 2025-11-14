//
// Created by khela on 14/11/2025.
//


//
// Created by alice on 12/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"
#include "stack.h"


// crée une pile vide (pile = NULL)
t_stack creer_stack(void) {
    return NULL;
}

// renvoie vrai si la pile est vide
bool stack_vide(t_stack p) {
    return (p == NULL);
}

// empile un élément (ajoute en tête)
t_stack empiler(t_stack p, t_tarjan_vertex v) {
    cellule* c = malloc(sizeof(cellule));
    if (c == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée dans empiler.\n");
        return p;
    }
    *(c->val) = v;
    c->suiv = p;
    p = c;
    return p;
}

// dépile le sommet, place la valeur dans *v
t_stack depiler(t_stack p, t_tarjan_vertex* v) {
    if (p == NULL) {
        fprintf(stderr, "Erreur : tentative de dépiler une pile vide.\n");
        return NULL;
    }
    cellule* tmp = p;
    *v = *(tmp->val);
    p = tmp->suiv;
    free(tmp);
    return p;
}

// affiche le contenu de la pile du haut vers le bas
void afficher_stack(t_stack p) {
    if (p == NULL) {
        printf("Pile vide.\n");
        return;
    }

    printf("Contenu de la pile (haut -> bas) :\n");
    cellule* tmp = p;
    while (tmp != NULL) {
        printf("[id = %d | num = %d | acces = %d | indic = %d]\n",
               tmp->val->id, tmp->val->number, tmp->val->numberacces, tmp->val->indic);
        tmp = tmp->suiv;
    }
    printf("\n");
}

// libère toute la pile
void free_stack(t_stack p) {
    cellule* tmp;
    while (p != NULL) {
        tmp = p;
        p = p->suiv;
        free(tmp->val);
        free(tmp);
    }
}
