//
// Created by khela on 14/11/2025.
//



#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"

t_tarjan_vertex* creertableau(int taille){ //là je créer mon tableau
    if(taille <=0) return NULL;

    t_tarjan_vertex* tableau = malloc(sizeof(t_tarjan_vertex) * taille);
    if(tableau == NULL) return NULL;
    for (int i = 0; i < taille; i++) {
        tableau[i].id = i +1;         // identifiant = numéro du sommet ici on commence à 1 et pas à 0
        tableau[i].number = -1;        // numéro temporaire initialisé à -1
        tableau[i].numberacces = -1;   // numéro accessible initialisé à -1
        tableau[i].indic = false;      // pas encore dans la pile
    }

return tableau;
}

void parcours(int a, t_tarjan_vertex* sommets, t_stack* pile, int* compteur, t_infos* infos){
    sommets[a].numberacces = *compteur;
    sommets[a].number = *compteur;
    (*compteur)++;

    *pile = empiler(*pile, sommets[a]);
    sommets[a].indic = true;

    for (int i = 0; i < infos->nb_voisins[a]; i++){ //ici on va parcourir les voisins
        int voisin = infos->adj[a][i];//ici on crée variable voisin
       if (sommets[voisin].number == -1)  {
           parcours(voisin, sommets, &pile, &compteur, &infos);
            if (sommets[voisin].numberacces < sommets[a].numberacces) {
                sommets[a].numberacces = sommets[voisin].numberacces;
            }

        }
        else if (sommets[voisin].indic) {//ici on est dans la pile
            if (sommets[voisin].numberacces < sommets[a].numberacces) {
                sommets[a].numberacces = sommets[voisin].numberacces;}
        }

    }
    //si on a sommet qui est une racine d'une composante
    if (sommets[a].numberacces == sommets[a].number) {
        t_classe new_classe;
        new_classe.nb_sommets = 0;
        printf("Nom de la composante : ");
        scanf("%16s", new_classe.name);// éviter les débordements

        new_classe.head = malloc(sizeof(t_tarjan_vertex)*1); //ici on cree notre nouvelle classe à laquelle on va incrementer les valeurs de la pile
        t_tarjan_vertex sommet_temp; //on cree une valeur temporaire pour ne pas perdre la pile et ses valeurs
        int index = 0;//on commence au début

        while (!stack_vide(*pile)) { //si liste pas vide
            *pile = depiler(*pile, &sommet_temp); //on sort les valeurs des sommets
            sommet_temp.indic = false;//le sommet est dépilé donc plus dans la pile, donc pas "actif"
            //on va créer notre nouvelle classe
            new_classe.nb_sommets++; // on augmente les sommets de 1
            new_classe.head = realloc(new_classe.head, sizeof(t_tarjan_vertex)*new_classe.nb_sommets);
            new_classe.head[new_classe.nb_sommets - 1] = sommet_temp; // pour les deux lignes, on a .head car on va venir de 1, modifier
//l'allocation dynamique de la nouvelle classe, mais aussi, de 2/ ajouter la valeur du sommet qu'on a dépilé à celui où l'index est, /!\ Il s'agit donc de manipulation de tableau ici

            if (sommet_temp.id == a ) break; //jusqu'à le sommet de la racine
        }
         //On va ajouter la classe à la partition (le tout)
         infos->partition->nb_classes++;
         infos->partition->classes = realloc(infos->partition->classes, sizeof(t_classe) * infos->partition->nb_classes); //on réaloue pour ne pas écraser l'ancienne mémoire
         infos->partition->classes[infos->partition->nb_classes-1] = new_classe; //on fait -1 car on a incrémenté juste avant

    }

}

t_partition* tarjan(int nb_sommets, int** adj, int* nb_voisins) {
    // Initialisation des sommets, pour ça on va utiliser la fonction tableau (pas créée pour rien...)
    t_tarjan_vertex* sommets = creertableau(nb_sommets);
    if (!sommets) {
        printf("Erreur\n");
        return NULL;
    }
    // Maintenant on va initialiser la partition
    t_partition* partition = malloc(sizeof(t_partition)); //ici partition est un pointeur donc attention on y accèdes avec ->, c'est une alocation dynamique d'un structure
    partition->nb_classes = 0;
    partition->classes = NULL;
    //on va créer une pile vide
    t_stack pile = creer_stack();
    //on initialise la structure de l'info
    t_infos* infos = malloc(sizeof(t_infos));
    infos->partition = partition;
    infos->nb_voisins = nb_voisins;
    infos->adj = adj;

    //on va initialiser un compteur tarjan
    int compteur = 0;

    //finalement on va parcourir tous les sommets
    for (int i = 0; i < nb_sommets; i++) {
        if (sommets[i].number == -1) {
            parcours(i, sommets, &pile, &compteur, &infos);
        }
    }
    //comme toujours, on libère notre tableau de sommets et notre pile
    free(sommets);
    free(pile);

    //et on return la partition
    return partition;
}
