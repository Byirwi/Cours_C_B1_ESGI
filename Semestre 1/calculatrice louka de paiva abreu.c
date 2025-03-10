#include <stdio.h>

void add();
void subtract();
void multiply();
void divide();

int main() {
    int choix;

    //affiche le menu
    do {
        printf("\nMenu :\n");
        printf("1. Ajouter deux nombres\n");
        printf("2. Soustraire deux nombres\n");
        printf("3. Multiplier deux nombres\n");
        printf("4. Diviser deux nombres\n");
        printf("5. Quitter le programme\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                add();
                break;
            case 2:
                subtract();
                break;
            case 3:
                multiply();
                break;
            case 4:
                divide();
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);

    return 0;
}
// fonction permetant de faire les calcule
//fonction faire une somme
void add() {
    double num1, num2;
    printf("Entrez deux nombres : ");
    scanf("%lf %lf", &num1, &num2);
    printf("Résultat : %.2lf\n", num1 + num2);
}
//fonction faire une soustraction
void subtract() {
    double num1, num2;
    printf("Entrez deux nombres : ");
    scanf("%lf %lf", &num1, &num2);
    printf("Résultat : %.2lf\n", num1 - num2);
}
//fonction faire une multiplication
void multiply() {
    double num1, num2;
    printf("Entrez deux nombres : ");
    scanf("%lf %lf", &num1, &num2);
    printf("Résultat : %.2lf\n", num1 * num2);
}
//fonction faire une division
void divide() {
    double num1, num2;
    printf("Entrez deux nombres : ");
    scanf("%lf %lf", &num1, &num2);
    if (num2 != 0) {
        printf("Résultat : %.2lf\n", num1 / num2);
    } else {
        printf("Erreur : Division par zéro impossible.\n");
    }
}
