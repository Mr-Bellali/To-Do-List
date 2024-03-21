#include "todo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// menu

void afficherMenu()
{
    printf("1. Ajouter une tache.\n");
    printf("2. Afficher toutes les taches.\n");
    printf("3. Supprimer une tache.\n");
    printf("4. Modifier une tache.\n");
    printf("5. Filtrer les taches.\n");
    printf("6. Quitter.\n");
    printf("Entrer un numero pour confirmer un choix >> ");
}

// ajouter tâche

void ajouterTache(char *nom_tache, char *description, int priorite, int etat)
{
    int id = 0;
    char ch;
    char *etatF = malloc(20 * sizeof(char));
    char *prioriteF = malloc(20 * sizeof(char));

    FILE *fichier = fopen("taches.csv", "r");

    if (fichier == NULL)
    {
        printf("Le fichier n'existe pas.\n");
        return;
    }

    while ((ch = fgetc(fichier)) != EOF)
    {
        if (ch == '\n')
        {
            id++;
        }
    }

    fclose(fichier);

    if (id > 0)
    {
        id++;
    }

    fichier = fopen("taches.csv", "a");

    if (etat == 1)
    {
        strcpy(etatF, "termine");
    }
    else
    {
        strcpy(etatF, "pas encore termine");
    }

    if (priorite == 1)
    {
        strcpy(prioriteF, "non important");
    }
    else if (priorite == 2)
    {
        strcpy(prioriteF, "important");
    }
    else if (priorite == 3)
    {
        strcpy(prioriteF, "tres important");
    }

    // Obtenir la date actuelle
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%d/%m/%Y", tm_info);

    
    char deadline[20];
    printf("Entrez la date limite (JJ/MM/AAAA) : ");
    do
    {
        scanf("%s", deadline);

        int day, month, year;
        if (sscanf(deadline, "%d/%d/%d", &day, &month, &year) != 3)
        {
            printf("Format non valide. Entrez un format valide (JJ/MM/AAAA) : ");
            continue;
        }

        
        if (year < tm_info->tm_year + 1900 ||
            (year == tm_info->tm_year + 1900 && month < tm_info->tm_mon + 1) ||
            (year == tm_info->tm_year + 1900 && month == tm_info->tm_mon + 1 && day < tm_info->tm_mday))
        {
            printf("Entrez une date ulterieure ou egale a aujourd'hui (JJ/MM/AAAA) : ");
        }
        else
        {
            break;
        }
    } while (1);

    fprintf(fichier, "\n%d,%s,%s,%s,%s,%s,%s", id, nom_tache, description, prioriteF, etatF, date, deadline);

    fclose(fichier);

    system("cls");

    printf("\n L'ID de la tache qui vous a ete affectee est : %d\n\n", id);

    sleep(2.5);
    system("cls");
}

// afficher de manière organisée toutes les tâches ajoutées

void afficherTaches()
{
    system("cls");
    FILE *fichier = fopen("taches.csv", "r");
    if (fichier == NULL)
    {
        printf("Erreur : le fichier n'existe pas ou ne peut pas etre ouvert.\n");
        return;
    }

    char line[256];
    printf("ID\tNom\tDescription\tPriorite\tEtat\tDate de creation\tDate a faire\n");
    while (fgets(line, sizeof(line), fichier))
    {
        int id;
        char nom_tache[100], description[100], priorite[100], etat[100], dateinit[100], dateaff[100];
        if (sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,]", &id, nom_tache, description, priorite, etat, dateinit, dateaff) == 7)
        {
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", id, nom_tache, description, priorite, etat, dateinit, dateaff);
        }
    }

    fclose(fichier);
    sleep(3);
}

// modifier tâche

void modifierTache() {
    system("cls");
    afficherTaches();

    int taskIDToModify;
    printf("Entrez l'ID de la tache que vous voulez modifier : ");
    scanf("%d", &taskIDToModify);

    FILE *originalFile = fopen("taches.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (originalFile == NULL || tempFile == NULL) {
        printf("Erreur : Impossible d'ouvrir le(s) fichier(s).\n");
        return;
    }

    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);
    char currentDate[20];
    strftime(currentDate, sizeof(currentDate), "%d/%m/%Y", tm_info);

    char line[256];
    while (fgets(line, sizeof(line), originalFile)) {
        int id;
        char nom_tache[100], description[100], priorite[100], etat[100], taskDate[100], deadline[100];
        if (sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,]", &id, nom_tache, description, priorite, etat, taskDate, deadline) == 7) {
            if (id == taskIDToModify) {
                printf("Entrez le nouveau nom de la tache : ");
                scanf(" %[^\n]", nom_tache);
                printf("Entrez la nouvelle description de la tache : ");
                scanf(" %[^\n]", description);
                printf("Entrez la nouvelle priorité de la tache (1 : non important, 2 : important, 3 : tres important) : ");
                int priorityInput;
                scanf("%d", &priorityInput);
                if(priorityInput == 1){
                    strcpy(priorite, "non important");
                } else if(priorityInput == 2){
                    strcpy(priorite, "important");
                } else if(priorityInput == 3){
                                    strcpy(priorite, "tres important");
                } else {
                    printf("Entrée de priorite invalide.\n");
                    continue;
                }
                printf("Entrez le statut de la teche (1 : termine, 0 : pas encore termine) : ");
                int stateInput;
                scanf("%d", &stateInput);
                if (stateInput == 1) {
                    strcpy(etat, "termine");
                } else if (stateInput == 0) {
                    strcpy(etat, "pas encore termine");
                } else {
                    printf("Entree de statut invalide.\n");
                    continue;
                }
                printf("Entrez la nouvelle date limite (JJ/MM/AAAA) : ");
                do {
                    scanf("%99s", deadline);
                    int day, month, year;
                    if (sscanf(deadline, "%d/%d/%d", &day, &month, &year) != 3) {
                        printf("Format non valide. Entrez un format valide (JJ/MM/AAAA) : ");
                        continue;
                    }
                    if (year < tm_info->tm_year + 1900 || 
                        (year == tm_info->tm_year + 1900 && month < tm_info->tm_mon + 1) ||
                        (year == tm_info->tm_year + 1900 && month == tm_info->tm_mon + 1 && day < tm_info->tm_mday)) {
                        printf("Veuillez entrer une date valide a partir d'aujourd'hui (JJ/MM/AAAA) : ");
                    } else {
                        break;
                    }
                } while (1);
            }
        }
        fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s\n", id, nom_tache, description, priorite, etat, taskDate, deadline);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("taches.csv");
    rename("temp.csv", "taches.csv");
    system("cls");
    printf("Tâche modifiee avec succes !\n");
    sleep(2);
}

// supprimer tâche

void suprimerTache()
{
    system("cls");
    afficherTaches();

    int taskIDToDelete;
    printf("Entrez l'ID de la tâche que vous voulez supprimer : ");
    scanf("%d", &taskIDToDelete);

    FILE *originalFile = fopen("taches.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (originalFile == NULL || tempFile == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le(s) fichier(s).\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), originalFile))
    {
        int id;
        char nom_tache[100], description[100], priorite[100], etat[100], date[100], deadline[100];
        if (sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,]", &id, nom_tache, description, priorite, etat, date, deadline) == 7)
        {
            if (id != taskIDToDelete)
            {
                fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s", id, nom_tache, description, priorite, etat, date, deadline);
            }
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    remove("taches.csv");

    rename("temp.csv", "taches.csv");
    system("cls");
    printf("Tache supprimee avec succes !!\n");
    sleep(2);
}

// filtrer les dates par priorité ou par date d'échéance

void filtrerParDate() {
    system("cls");
    FILE *file = fopen("taches.csv", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des taches.\n");
        return;
    }

    // Obtenir la date actuelle
    time_t now;
    time(&now);
    struct tm *tm_info;
    tm_info = localtime(&now);

    char line[256];
    printf("ID\tNom\tDescription\tPriorite\tEtat\tDate de creation\tDate a faire\n");

    while (fgets(line, sizeof(line), file)) {
        int id;
        char nom_tache[100], description[100], priorite[100], etat[100], date[100], deadline[100];
        if (sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,]", &id, nom_tache, description, priorite, etat, date, deadline) == 7) {
            
            int day, month, year;
            sscanf(deadline, "%d/%d/%d", &day, &month, &year);

            
            time_t deadline_time = mktime(&(struct tm){.tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day});
            double difference = difftime(deadline_time, now) / (60 * 60 * 24);

            // Définir les couleurs pour l'affichage de la date
            char *color;
            if (difference < 5) {
                color = "\033[0;31m"; // Couleur rouge
            } else if (difference >= 5 && difference <= 7) {
                color = "\033[0;33m"; // Couleur or
            } else {
                color = "\033[0;32m"; // Couleur verte
            }

            // Afficher uniquement la date avec la couleur
            char date_formatted[100];
            sprintf(date_formatted, "%s%s%s", color, deadline, "\033[0m"); // Réinitialiser la couleur
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", id, nom_tache, description, priorite, etat, date, date_formatted);
        }
    }

    fclose(file);
    sleep(2);
}

// filtrer par priorité

void filtrerParPriorite() {
    system("cls");
    FILE *file = fopen("taches.csv", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des taches.\n");
        return;
    }

    char line[256];
    printf("ID\tNom\tDescription\tPriorite\tEtat\tDate de creation\tDate a faire\n");
    while (fgets(line, sizeof(line), file)) {
        int id;
        char nom_tache[100], description[100], priorite[100], etat[100], date[100], deadline[100];
        if (sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,]", &id, nom_tache, description, priorite, etat, date, deadline) == 7) {
            // Définir les couleurs pour l'affichage de la priorité
            char *color;
            if (strcmp(priorite, "non important") == 0) {
                color = "\033[0;32m"; // Couleur verte
            } else if (strcmp(priorite, "important") == 0) {
                color = "\033[0;33m"; // Couleur or
            } else if (strcmp(priorite, "tres important") == 0) {
                color = "\033[0;31m"; // Couleur rouge
            } else {
                // Couleur par défaut
                color = "\033[0m"; // Réinitialiser la couleur
            }

            // Afficher uniquement la priorité avec la couleur
            char priorite_formattee[100];
            sprintf(priorite_formattee, "%s%s%s", color, priorite, "\033[0m"); // Réinitialiser la couleur
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", id, nom_tache, description, priorite_formattee, etat, date, deadline);
        }
    }

    fclose(file);
    sleep(2);
}
