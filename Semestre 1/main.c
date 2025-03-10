#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Taille d'un paquet standard de cartes
#define PAQUET_TAILLE 52

// Enumération pour les couleurs de carte
typedef enum {
    PIQUE,
    COEUR,
    CARREAU,
    TREFLE
} Couleur;

// Enumération pour les valeurs de carte
typedef enum {
    AS = 1,
    DEUX,
    TROIS,
    QUATRE,
    CINQ,
    SIX,
    SEPT,
    HUIT,
    NEUF,
    DIX,
    VALET,
    DAME,
    ROI
} Valeur;

// Structure pour représenter une carte
typedef struct {
    Couleur couleur;
    Valeur valeur;
} Carte;

// Fonction pour initialiser le paquet de cartes
void initPaquet(Carte paquet[PAQUET_TAILLE]) {
    int index = 0;
    for (int couleur = PIQUE; couleur <= TREFLE; couleur++) {
        for (int valeur = AS; valeur <= ROI; valeur++) {
            paquet[index].couleur = couleur;
            paquet[index].valeur = valeur;
            index++;
        }
    }
}

// Fonction pour mélanger le paquet de cartes
void melangerPaquet(Carte paquet[PAQUET_TAILLE]) {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    for (int i = 0; i < PAQUET_TAILLE; i++) {
        int j = rand() % PAQUET_TAILLE;
        // Échanger les cartes à l'index i et j
        Carte temp = paquet[i];
        paquet[i] = paquet[j];
        paquet[j] = temp;
    }
}

// Fonction pour afficher une carte
void afficherCarte(Carte carte) {
    const char *nomsCouleurs[] = {"Pique", "Coeur", "Carreau", "Trefle"};
    const char *nomsValeurs[] = {"", "As", "Deux", "Trois", "Quatre", "Cinq", "Six", "Sept", "Huit", "Neuf", "Dix", "Valet", "Dame", "Roi"};

    printf("%s de %s\n", nomsValeurs[carte.valeur], nomsCouleurs[carte.couleur]);
}

// Fonction pour afficher tout le paquet
void afficherPaquet(Carte paquet[PAQUET_TAILLE]) {
    for (int i = 0; i < PAQUET_TAILLE; i++) {
        afficherCarte(paquet[i]);
    }
}

int main() {
    Carte paquet[PAQUET_TAILLE];

    initPaquet(paquet);       // Initialiser le paquet avec les 52 cartes
    melangerPaquet(paquet);    // Mélanger le paquet

    printf("Paquet mélangé :\n");
    afficherPaquet(paquet);    // Afficher le paquet mélangé

    return 0;
}
