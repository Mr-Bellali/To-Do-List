#include "todo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE* fichier;
//menu

void afficherMenu(){
    printf("1. Ajouter une tache.\n");
    printf("2. Aficher toutes les taches.\n");
    printf("3. Suprimer une tache.\n");
    printf("4. Modifier une tache.\n");
    printf("5. Filtrer les taches.\n");
    printf("6. Quiter.\n");
    printf("Entrer un numero pour confirmer un choix >> ");

}

//ajouter tache

void ajouterTache(char* nom_tache, char* description, char* priorite, int etat, char* date) {
    int id = 0;
    char ch;
    char* etatF = malloc(20*sizeof(char));

    fichier = fopen("taches.csv", "r");

    if (fichier == NULL) {
        printf("fichier n'exist pas.\n");
        return; 
    }

    while ((ch = fgetc(fichier)) != EOF) {
        if (ch == '\n') {
            id++;
        }
    }

    fclose(fichier);

    fichier = fopen("taches.csv", "a");

    if(etat == 1 ){
        strcpy(etatF,"fini");
    }else{
        strcpy(etatF,"pas fini");
    }

    fprintf(fichier,"\n%d,%s, %s, %s, %s,%s",id, nom_tache, description, priorite, etatF, date);

    fclose(fichier);

    system("cls");

    printf("\n l'id de la tache qui vous afficter est:  %d\n\n", id);

    sleep(2.5);
    system("cls");

}

//afficher de maniere organisee toutes les taches ajoutee

void afficherTaches() {
 

    system("cls");
    FILE *fichier = fopen("taches.csv", "r");
    if (fichier == NULL) {
        printf("Erreur: fichier n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    char line[256];
    printf("ID\tNom\tDescription\tPriorite\tEtat\tDate\n");
    while (fgets(line, sizeof(line), fichier)) {
        int id;
        char nom_tache[100], description[100], priorite[100], etat[100], date[100];
        if (sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%10s\n", &id, nom_tache, description, priorite, etat, date) == 6) {
            printf("%d\t%s\t%s\t%s\t%s\t%s\n", id, nom_tache, description, priorite, etat, date);
        }
    }

    fclose(fichier);

    //system("start cmd /c \"type taches.csv && pause\"");
    sleep(3);
}


//modifier tache 

void modifierTache(){

}

//suprimer tache 

void suprimerTache(){


}

//filtrer les dates par priorite ou par date d'echeance 

char * filtrerParDate(){

}

char * filtrerParPriorite(){
    
}


//marquer les tache comme terminees

void marqueTirminer(){

}