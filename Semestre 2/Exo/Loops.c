#include <stdio.h>

// Fonction pour trouver la position d'une valeur cible dans un tableau trié
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
    int sortedArray[] = {1, 6, 5, 5, 7};
    int targetValue = 7;
    int arraySize = sizeof(sortedArray) / sizeof(sortedArray[0]);

    // Trouver la position de la valeur cible
    int position = findPosition(sortedArray, arraySize, targetValue);

    // Afficher le résultat
    if (position != -1) {
        printf("Position : %d\n", position);
    } else {
        printf("Valeur non trouvée dans le tableau.\n");
    }

    return 0;
}

scanf("%lf %lf", &num1, &num2);