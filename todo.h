#ifndef TODO_H
#define TODO_H

#include <stdio.h> // Include necessary header files here

// Function declarations
void afficherMenu();
void ajouterTache(char *nom_tache, char *description, int priorite, int etat);
void modifierTache();
void suprimerTache();
char* filtrerParDate();
char* filtrerParPriorite();
void afficherTaches();
void marqueTerminer();

#endif
