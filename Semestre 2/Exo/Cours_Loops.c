#include <stdio.h>
// int main() {
//     int lignes;
//
//     // Demander à l'utilisateur d'entrer le nombre de lignes
//     printf("Nombre de lignes ? ");
//     scanf("%d", &lignes);
//
//     // Afficher le premier motif de triangle
//     printf("Motif 1:\n");
//     for (int i = 1; i <= lignes; i++) {
//         for (int j = 1; j <= i; j++) {
//             printf("* ");
//         }
         // printf("\n");
//     }


        // Afficher le deuxième motif de triangle
// int main() {
//      int nbr_l = 4;
//      for(int i = 1;i <= nbr_l;i++) {
//          // printf("");
//          for(int j=1;j <= nbr_l-i+1;j++) {
//              printf("*");
//          }
//          printf("\n");
//      }
//     }
// Afficher le deuxième motif de triangle
// int main() {
//     int nbr_l = 4;
//     for(int i = 0;i <= nbr_l;i++) {
//         for(int j=1;j <= nbr_l-i;j++) {
//             printf("*");
//         }
//         printf("\n");
//     }
// }

// motif 3
// int main() {
//     int nbr_l = 4;
//     int i=0; //intialisation etape 1
//     for(; i < nbr_l; ){ //ETAPE 2 VERIFIER LA CONDITION,
//         // SI CETTE CONDITION EST VRAI EXECUTER LES BOUCLES SUIVANTES
//         for(int j = 0; j <i ; j++) {
//            printf("  ");
//            }
//             for(int k=0; k < nbr_l-i;k++) {
//                 printf("* ");
//             }
//         printf("\n");
//         i++;
//         }
//     }
// motif 4#include <stdio.h>

// int main() {
//     // Déclaration et initialisation du nombre de lignes du triangle
//     int nbr_l = 4;
//
//     // Boucle pour chaque ligne du triangle
//     for(int i = 0; i < nbr_l ; i++) {
//         // Boucle pour les espaces avant les étoiles
//         for(int j = 0; j < nbr_l - i; j++) {
//             printf("  ");
//         }
//         // Boucle pour imprimer les étoiles
//         for(int k = 0; k <= i; k++) {
//             printf("* ");
//         }
//         // Imprimer un saut de ligne après chaque ligne du triangle
//         printf("\n");
//     }
//     return 0;
// }

// Exo2
int main() {
    // Déclaration et initialisation du tableau
    int tableau[] = {1, 3, 5, 7, 9};

    // Calcul de la taille du tableau
    int taille_tableau = sizeof(tableau) / sizeof(tableau[0]);

    // Déclaration des variables pour la valeur cible et la position
    int valeur_cible;
    int position = -1;

    // Demande à l'utilisateur d'entrer la valeur cible
    printf("Entrez la valeur cible: ");
    scanf("%d", &valeur_cible);

    // Boucle pour parcourir le tableau et chercher la valeur cible
    for (int i = 0; i < taille_tableau; i++) {
        if (tableau[i] == valeur_cible) {
            position = i;
            break; // Arrêter la boucle si la valeur cible est trouvée
        }
    }

    // Vérification si la valeur cible a été trouvée et affichage du résultat
    if (position != -1) {
        printf("La valeur cible %d se trouve a la position: %d\n", valeur_cible, position);
    } else {
        printf("La valeur cible n'a pas été trouvée dans le tableau.\n");
    }

    return 0;
}