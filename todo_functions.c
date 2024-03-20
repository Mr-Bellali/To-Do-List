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
    printf("2. Aficher toutes les taches.\n");
    printf("3. Suprimer une tache.\n");
    printf("4. Modifier une tache.\n");
    printf("5. Filtrer les taches.\n");
    printf("6. Quiter.\n");
    printf("Entrer un numero pour confirmer un choix >> ");
}

// ajouter tache

void ajouterTache(char *nom_tache, char *description, int priorite, int etat)
{
    int id = 0;
    char ch;
    char *etatF = malloc(20 * sizeof(char));
    char *prioriteF = malloc(20 * sizeof(char));

    FILE *fichier = fopen("taches.csv", "r");

    if (fichier == NULL)
    {
        printf("fichier n'existe pas.\n");
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
        strcpy(etatF, "fini");
    }
    else
    {
        strcpy(etatF, "pas fini");
    }

    if (priorite == 1)
    {
        strcpy(prioriteF, "not important");
    }
    else if (priorite == 2)
    {
        strcpy(prioriteF, "important");
    }
    else if (priorite == 3)
    {
        strcpy(prioriteF, "very important");
    }

    // Get current date
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%d/%m/%Y", tm_info);

    // Get deadline date
    char deadline[20];
    printf("Enter the deadline date (DD/MM/YYYY): ");
    do
    {
        scanf("%s", deadline);

        // Parse the entered date
        int day, month, year;
        if (sscanf(deadline, "%d/%d/%d", &day, &month, &year) != 3)
        {
            printf("Invalid date format. Please enter again (DD/MM/YYYY): ");
            continue;
        }

        // Validate against today's date
        if (year < tm_info->tm_year + 1900 ||
            (year == tm_info->tm_year + 1900 && month < tm_info->tm_mon + 1) ||
            (year == tm_info->tm_year + 1900 && month == tm_info->tm_mon + 1 && day < tm_info->tm_mday))
        {
            printf("Please enter a valid date from today onwards (DD/MM/YYYY): ");
        }
        else
        {
            break;
        }
    } while (1);

    fprintf(fichier, "\n%d,%s,%s,%s,%s,%s,%s", id, nom_tache, description, prioriteF, etatF, date, deadline);

    fclose(fichier);

    system("cls");

    printf("\n L'ID de la tache qui vous affecter est: %d\n\n", id);

    // Added sleep and cls
    sleep(2.5);
    system("cls");
}

// afficher de maniere organisee toutes les taches ajoutee

void afficherTaches()
{
    system("cls");
    FILE *fichier = fopen("taches.csv", "r");
    if (fichier == NULL)
    {
        printf("Erreur: fichier n'existe pas ou ne peut pas être ouvert.\n");
        return;
    }

    char line[256];
    printf("ID\tNom\tDescription\tPriorite\tEtat\tDate creation\tdate faire\n");
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

// modifier tache

void modifierTache() {
    system("cls");
    afficherTaches();

    int taskIDToModify;
    printf("Enter the ID of the task you want to modify: ");
    scanf("%d", &taskIDToModify);

    FILE *originalFile = fopen("taches.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (originalFile == NULL || tempFile == NULL) {
        printf("Erreur: Impossible d'ouvrir le(s) fichier(s).\n");
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
                printf("Enter the new name of the task: ");
                scanf(" %[^\n]", nom_tache);
                printf("Enter the new description of the task: ");
                scanf(" %[^\n]", description);
                printf("Enter the new priority of the task (1: not important, 2: important, 3: very important): ");
                int priorityInput;
                scanf("%d", &priorityInput);
                if(priorityInput == 1){
                    strcpy(priorite, "not important");
                } else if(priorityInput == 2){
                    strcpy(priorite, "important");
                } else if(priorityInput == 3){
                    strcpy(priorite, "very important");
                } else {
                    printf("Invalid priority input.\n");
                    continue;
                }
                printf("Enter the new state of the task (1: finished, 0: unfinished): ");
                int stateInput;
                scanf("%d", &stateInput);
                if (stateInput == 1) {
                    strcpy(etat, "fini");
                } else if (stateInput == 0) {
                    strcpy(etat, "pas fini");
                } else {
                    printf("Invalid state input.\n");
                    continue;
                }
                printf("Enter the new deadline date (DD/MM/YYYY): ");
                do {
                    scanf("%99s", deadline);
                    int day, month, year;
                    if (sscanf(deadline, "%d/%d/%d", &day, &month, &year) != 3) {
                        printf("Invalid date format. Please enter again (DD/MM/YYYY): ");
                        continue;
                    }
                    if (year < tm_info->tm_year + 1900 || 
                        (year == tm_info->tm_year + 1900 && month < tm_info->tm_mon + 1) ||
                        (year == tm_info->tm_year + 1900 && month == tm_info->tm_mon + 1 && day < tm_info->tm_mday)) {
                        printf("Please enter a valid date from today onwards (DD/MM/YYYY): ");
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
    printf("Task modified successfully!\n");
    sleep(2);
}

// suprimer tache

void suprimerTache()
{
    system("cls");
    afficherTaches();

    int taskIDToDelete;
    printf("Enter the ID of the task you want to delete: ");
    scanf("%d", &taskIDToDelete);

    FILE *originalFile = fopen("taches.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (originalFile == NULL || tempFile == NULL)
    {
        printf("Erreur: Impossible d'ouvrir le(s) fichier(s).\n");
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

    // Remove the original file
    remove("taches.csv");

    // Rename the temporary file to the original filename
    rename("temp.csv", "taches.csv");
    system("cls");
    printf("tache a ete suprimer!!");
    sleep(2);
}

// filtrer les dates par priorite ou par date d'echeance

char *filtrerParDate()
{
}

char *filtrerParPriorite()
{
}

// marquer les tache comme terminees

void marqueTirminer()
{
}