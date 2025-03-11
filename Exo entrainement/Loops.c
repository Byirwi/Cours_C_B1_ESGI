// Exo 1

 #include <stdio.h>

 int main() {
     int lignes;

     // Demander à l'utilisateur d'entrer le nombre de lignes
     printf("Nombre de lignes ? ");
     scanf("%d", &lignes);

     // Afficher le premier motif de triangle
     printf("Motif 1:\n");
     for (int i = 1; i <= lignes; i++) {
         for (int j = 1; j <= i; j++) {
             printf("* ");
         }
         printf("\n");
     }

     // Afficher le deuxième motif de triangle
     printf("Motif 2:\n");
     for (int i = lignes; i >= 1; i--) {
         for (int j = 1; j <= i; j++) {
             printf("* ");
         }
         printf("\n");
     }

     // Afficher le quatrième motif de triangle (inverse du motif 1)
     printf("Motif 3:\n");
     for (int i = lignes; i >= 1; i--) {
         for (int j = 1; j <= lignes - i; j++) {
             printf("  ");
         }
         for (int j = 1; j <= i; j++) {
             printf("* ");
         }
         printf("\n");
     }

     // Afficher le troisième motif de triangle (inverse du motif 2)
     printf("Motif 4:\n");
     for (int i = 1; i <= lignes; i++) {
         for (int j = 1; j <= lignes - i; j++) {
             printf("  ");
         }
         for (int j = 1; j <= i; j++) {
             printf("* ");
         }
         printf("\n");
     }

     return 0;
 }

//Exo 2

 #include <stdio.h>

//  Fonction pour trouver la position d'une valeur cible dans un tableau trié
 int findPosition(int arr[], int size, int target) {
     for (int i = 0; i < size; i++) {
         if (arr[i] == target) {
             return i; // Retourne l'indice si la valeur cible est trouvée
         }
     }
     return -1; // Retourne -1 si la valeur cible n'est pas trouvée
 }

 int main() {
     // Exemple d'entrée
     int list1[] = {1, 3, 5, 7, 9};
     int targetValue = 3;
     int arraySize = sizeof(list1) / sizeof(list1[0]);

     // Trouver la position de la valeur cible
     int PositionVariable = findPosition(list1, arraySize, targetValue);

     // Afficher le résultat
     if (PositionVariable != -1) {
         printf("Position : %d\n", PositionVariable);
     } else {
         printf("Valeur non trouvée dans le tableau.\n");
     }

     return 0;
 }

// Exo 3

#include <stdio.h>

// Fonction pour calculer la somme des chiffres d'un nombre entier
// int sum_of_digits(int number) {
//     int sum = 0;
//     while (number != 0) {
//         sum += number % 10; // Ajouter le dernier chiffre à la somme
//         number /= 10; // Retirer le dernier chiffre du nombre
//     }
//     return sum;
// }
//
// int main() {
//     int number;
//
//     // Demander à l'utilisateur d'entrer un nombre
//     printf("Entrez un nombre entier : ");
//     scanf("%d", &number);
//
//     // Calculer la somme des chiffres
//     int result = sum_of_digits(number);
//
//     // Afficher le résultat
//     printf("La somme des chiffres de %d est : %d\n", number, result);
//
//     return 0;
// }

// Exo 4

// #include <stdbool.h>
//
// // Fonction pour vérifier si un nombre est premier
// bool estNombrePremier(int nombre) {
//     if (nombre <= 1) {
//         return false;
//     }
//     for (int i = 2; i * i <= nombre; i++) {
//         if (nombre % i == 0) {
//             return false;
//         }
//     }
//     return true;
// }
//
// int main() {
//     int nombre;
//
//     // Demander à l'utilisateur d'entrer un nombre
//     printf("Entrez un nombre : ");
//     scanf("%d", &nombre);
//
//     // Vérifier si le nombre est premier
//     if (estNombrePremier(nombre)) {
//         printf("Nombre premier\n");
//     } else {
//         printf("Ce n est pas un nombre premier\n");
//     }
//
//     return 0;
// }

// Exo 5

#include <stdio.h>
#include <stdbool.h>

// Fonction pour vérifier si un nombre est un palindrome
bool estPalindrome(int nombre) {
    int original = nombre;
    int reverse = 0;

    while (nombre != 0) {
        int digit = nombre % 10;
        reverse = reverse * 10 + digit;
        nombre /= 10;
    }

    return original == reverse;
}

int main() {
    int nombre;

    // Demander à l'utilisateur d'entrer un nombre
    printf("Entrez un nombre : ");
    scanf("%d", &nombre);

    // Vérifier si le nombre est un palindrome
    if (estPalindrome(nombre)) {
        printf("Palindrome\n");
    } else {
        printf("Ce n'est pas un palindrome\n");
    }

    return 0;
}