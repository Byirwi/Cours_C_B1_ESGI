#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAQUET_TAILLE 52
#define PILES 7
#define FONDATIONS 4
#define MIN_FONDATION 101
#define MAX_FONDATION 104

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
    int visible; // 1 si la carte est visible, 0 sinon
} Carte;

// Structure pour une pile de cartes
typedef struct {
    Carte cartes[PAQUET_TAILLE];
    int taille;
} Pile;

// Initialisation du paquet
void initPaquet(Carte paquet[PAQUET_TAILLE]) {
    int index = 0;
    for (int couleur = PIQUE; couleur <= TREFLE; couleur++) {
        for (int valeur = AS; valeur <= ROI; valeur++) {
            paquet[index++] = (Carte){.couleur = couleur, .valeur = valeur, .visible = 0};
        }
    }
}

// Mélange des cartes
void melangerPaquet(Carte paquet[PAQUET_TAILLE]) {
    srand(time(NULL));
    for (int i = 0; i < PAQUET_TAILLE; i++) {
        int j = rand() % PAQUET_TAILLE;
        Carte temp = paquet[i];
        paquet[i] = paquet[j];
        paquet[j] = temp;
    }
}

// Affichage d'une carte
void afficherCarte(Carte carte) {
    const char *nomsCouleurs[] = {"Pique", "Coeur", "Carreau", "Trefle"};
    const char *nomsValeurs[] = {"", "As", "Deux", "Trois", "Quatre", "Cinq", "Six", "Sept", "Huit", "Neuf", "Dix", "Valet", "Dame", "Roi"};
    if (carte.visible) {
        printf("%s de %s", nomsValeurs[carte.valeur], nomsCouleurs[carte.couleur]);
    } else {
        printf("[Carte cachee]");
    }
}

// Affichage d'une pile
void afficherPile(Pile *pile) {
    for (int i = 0; i < pile->taille; i++) {
        afficherCarte(pile->cartes[i]);
        printf(" ");
    }
}

// Distribution des cartes
void distribuerCartes(Carte paquet[PAQUET_TAILLE], Pile piles[PILES], Pile *stock) {
    int index = 0;
    for (int i = 0; i < PILES; i++) {
        piles[i].taille = i + 1;
        for (int j = 0; j <= i; j++) {
            piles[i].cartes[j] = paquet[index++];
            piles[i].cartes[j].visible = (j == i);
        }
    }
    stock->taille = PAQUET_TAILLE - index;
    for (int i = 0; i < stock->taille; i++) {
        stock->cartes[i] = paquet[index++];
    }
}

// Retourner la dernière carte cachée d'une pile
void retournerCartePile(Pile *pile) {
    if (pile->taille > 0 && !pile->cartes[pile->taille - 1].visible) {
        pile->cartes[pile->taille - 1].visible = 1;
    }
}

// Recyclage du stock
void recyclerStock(Pile *stock, Pile *cartesTirees) {
    for (int i = cartesTirees->taille - 1; i >= 0; i--) {
        stock->cartes[stock->taille++] = cartesTirees->cartes[i];
    }
    cartesTirees->taille = 0;
}

// Tirer une carte du stock
void tirerCarte(Pile *stock, Pile *cartesTirees) {
    if (stock->taille > 0) {
        Carte carteTiree = stock->cartes[--stock->taille];
        carteTiree.visible = 1;
        cartesTirees->cartes[cartesTirees->taille++] = carteTiree;
        printf("Carte tiree : ");
        afficherCarte(carteTiree);
        printf("\n");
    } else {
        printf("Le stock est vide. Recyclage en cours...\n");
        recyclerStock(stock, cartesTirees);
    }
}

// Déplacement des cartes
void deplacerCarte(Pile piles[PILES], Pile fondations[FONDATIONS], Pile *cartesTirees, int source, int destination) {
    Carte carteDeplacee;

    // Vérifier et récupérer la carte de la source
    if (source >= 1 && source <= PILES && piles[source - 1].taille > 0) {
        carteDeplacee = piles[source - 1].cartes[--piles[source - 1].taille];
        retournerCartePile(&piles[source - 1]);
    } else if (source >= MIN_FONDATION && source <= MAX_FONDATION && fondations[source - MIN_FONDATION].taille > 0) {
        carteDeplacee = fondations[source - MIN_FONDATION].cartes[--fondations[source - MIN_FONDATION].taille];
    } else if (source == 99 && cartesTirees->taille > 0) {
        carteDeplacee = cartesTirees->cartes[--cartesTirees->taille];
    } else {
        printf("Source invalide ou vide. Annulation du déplacement.\n");
        return;
    }

    // Vérifier la destination et ajouter la carte
    if (destination >= 1 && destination <= PILES) {
        piles[destination - 1].cartes[piles[destination - 1].taille++] = carteDeplacee;
    } else if (destination >= MIN_FONDATION && destination <= MAX_FONDATION) {
        fondations[destination - MIN_FONDATION].cartes[fondations[destination - MIN_FONDATION].taille++] = carteDeplacee;
    } else {
        printf("Destination invalide. Annulation du déplacement.\n");
        return;
    }

    printf("Déplacement réussi : ");
    afficherCarte(carteDeplacee);
    printf("\n");
}

// Affichage de l'état du jeu
void afficherEtat(Pile piles[PILES], Pile fondations[FONDATIONS], Pile *cartesTirees, Pile *stock) {
    printf("\n--- Etat actuel du jeu ---\n");
    printf("Piles :\n");
    for (int i = 0; i < PILES; i++) {
        printf("Pile %d: ", i + 1);
        afficherPile(&piles[i]);
        printf("\n");
    }
    printf("\nFondations :\n");
    for (int i = 0; i < FONDATIONS; i++) {
        printf("Fondation %d: ", i + MIN_FONDATION);
        afficherPile(&fondations[i]);
        printf("\n");
    }
    printf("\nCarte tire : ");
    if (cartesTirees->taille > 0) {
        afficherCarte(cartesTirees->cartes[cartesTirees->taille - 1]);
    } else {
        printf("Aucune carte tiree.");
    }
    printf("\nCartes restantes dans le stock : %d\n", stock->taille);
}

// Menu de déplacement
void afficherMenuDeplacement() {
    printf("\n--- Déplacement ---\n");
    printf("Options disponibles :\n");
    printf("  1-7 : Sélectionner une Pile.\n");
    printf("  101-104 : Sélectionner une Fondation.\n");
    printf("  99 : Deplacer une carte tirée.\n");
    printf("  0 : Retourner au menu principal.\n");
}

// Fonction principale
int main() {
    Carte paquet[PAQUET_TAILLE];
    Pile piles[PILES] = {0};
    Pile fondations[FONDATIONS] = {0};
    Pile stock = {0};
    Pile cartesTirees = {0};

    initPaquet(paquet);
    melangerPaquet(paquet);
    distribuerCartes(paquet, piles, &stock);

    while (1) {
        afficherEtat(piles, fondations, &cartesTirees, &stock);

        printf("\n--- Menu Principal ---\n");
        printf("1. Tirer une carte\n");
        printf("2. Deplacer une carte\n");
        printf("3. Quitter le jeu\n");
        printf("Choix : ");
        int choix;
        scanf("%d", &choix);

        if (choix == 3) {
            printf("Fin du jeu.\n");
            break;
        } else if (choix == 1) {
            tirerCarte(&stock, &cartesTirees);
        } else if (choix == 2) {
            afficherMenuDeplacement();

            int source, destination;
            printf("Choisissez la source : ");
            scanf("%d", &source);

            if (source == 0) continue;

            printf("Choisissez la destination : ");
            scanf("%d", &destination);

            deplacerCarte(piles, fondations, &cartesTirees, source, destination);
        }
    }

    return 0;
}