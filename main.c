#include <stdio.h>
#include <stdlib.h>
#include "todo.h"

int main(){
    int choix=0;

    printf("\t\t\tTo-Do-List\n\n\n");
    do{
        afficherMenu();
        scanf("%d",&choix);

        if (choix > 6 || choix <= 0 ){
            printf("\nentrer une valeur valide.\n>> ");
            scanf("%d",&choix);
        }
        

        switch (choix)
        {
        case 1 :
            ajouterTache();
            break;
        
        default:
            printf("\nentrer une valeur valid..");
            break;
        }

    }while (choix != 6);
    
}