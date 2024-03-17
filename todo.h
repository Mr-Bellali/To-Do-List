//menu

void afficherMenu(){
    printf("1. Ajouter une tache.\n");
    printf("2. Modifier une tache.\n");
    printf("3. Suprimer une tache.\n");
    printf("4. Aficher toutes les taches.\n");
    printf("5. Filtrer les taches.\n");
    printf("6. Quiter.");
    printf("Entrer un numero pour confirmer un choix >> ");

}

//ajouter tache

void ajouterTache(){
    FILE* fichier;

    fichier = fopen("taches.csv","a");

    fprintf(fichier,"test");

    fclose(fichier);

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

//afficher de maniere organisee toutes les taches ajoutee

void afficherTaches(){

}

//marquer les tache comme terminees

void marqueTirminer(){

}