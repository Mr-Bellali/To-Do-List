#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "todo.h"

int main() {

    system("cls");
    int choix = 0;
    int filter = 0;

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
                char* nom_tache = malloc(100 * sizeof(char));
                char* description = malloc(100 * sizeof(char));
                int priorite;
                int etat;
                printf("Entrez le nom de la tache : ");
                scanf(" %[^\n]", nom_tache);
                printf("Entrez la description de la tache : ");
                scanf(" %[^\n]", description);
                printf("Entrez la priorite de la tache :\n1.not important\n2.important\n3.very important\n>>");
                scanf("%d", &priorite);
                printf("Entrez l'etat de la tache \nentrer 1 c'est la rache ete fini sinon apuyez quelque chose\n>>");
                scanf("%d", &etat);
                ajouterTache(nom_tache, description, priorite, etat);
                free(nom_tache);
                free(description);
                break;
            }

            case 2:
                afficherTaches();
                break;

            case 3:
                suprimerTache() ;
                break;

            case 4:
                modifierTache();
                break;

            case 5:
                printf("1.filtrer les taches par dates.\n2.filtrer les taches par priorite\n>>");
                scanf("%d",&filter);

                if (filter == 1){
                    filtrerParDate();
                }else if (filter == 2){
                    filtrerParPriorite();
                }
                

            default:

                break;
        }
    } while (choix != 6);

    return 0;
}
