#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "todo.h"

int main() {
    int choix = 0;

    printf("\t\t\tTo-Do-List\n\n");
    do {
        afficherMenu();
        scanf("%d", &choix);

        if (choix > 6 || choix <= 0) {
            printf("\nentrer une valeur valide.\n>> ");
            scanf("%d", &choix);
        }

        switch (choix) {
            case 1: {
                // Declare and allocate memory for nom_tache and description
                char* nom_tache = malloc(100 * sizeof(char));
                char* description = malloc(100 * sizeof(char));
                char* priorite = malloc(100 * sizeof(char));
                char* date = malloc(10*sizeof(char));
                int etat;
                printf("Entrez le nom de la tache : ");
                scanf("%s", nom_tache);
                printf("Entrez la description de la tache : ");
                scanf("%s", description);
                printf("Entrez la priorite de la tache : ");
                scanf("%s", priorite);
                printf("Entrez l'etat de la tache \nentrer 1 c'est la rache ete fini sinon apuyez quelque chose : ");
                scanf("%d", &etat);
                printf("Entrer la date de tache(JJ/MM/AAAA) : ");
                scanf("%s", date);
                ajouterTache(nom_tache, description, priorite, etat, date);
                free(nom_tache);
                free(description);
                free(date);
                break;
            case 2:
                afficherTaches();
                break;
            }
            default:
                printf("\nentrer une valeur valide.");
                break;
        }
    } while (choix != 6);

    return 0;
}
