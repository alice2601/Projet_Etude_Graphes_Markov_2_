//
// Created by alice on 12/11/2025.

#ifndef DOWNLOADS_STACK_H
#define DOWNLOADS_STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// éviter les problèmes circulaire
typedef struct t_tarjan_vertex t_tarjan_vertex;

typedef struct cellule {
    t_tarjan_vertex val;
    struct cellule* suiv;
} cellule;

typedef cellule* t_stack;

// création et test
t_stack creer_stack(void);
bool stack_vide(t_stack s);

// opérations
t_stack empiler(t_stack s, t_tarjan_vertex v);
t_stack depiler(t_stack s, t_tarjan_vertex* v);

// affichage et libération
void afficher_stack(t_stack s);
void free_stack(t_stack s);

#endif //DOWNLOADS_STACK_H
