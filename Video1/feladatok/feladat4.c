#include <stdio.h> //printf, scanf_s
#include <stdlib.h> //calloc, free

int main() {
    int n;
    printf("Hanyadfokú polinómot kíván deriválni? ");
    scanf_s("%d",&n);

    //Tömb létrehozása és feltöltése
    printf("Adja meg (külön-külön, csökkenő sorrendben) a polinóm tagjait!\n");
    double* polinomTomb = calloc(n + 1,sizeof(double));
    for (int i = 0; i <= n; i++)
        scanf_s("%lf", &polinomTomb[i]);
    
    //Kiírás
    for (int i = 0; i <= n; i++) {
        printf("+ %lf * x^%d ", polinomTomb[i], n - i);
    }

    //Derivált kiírása
    printf("\nA polinóm deriváltja:\n");
    for (int i = 0; i < n; i++){
        printf("+ %lf * x^%d ",(n - i) * polinomTomb[i], n - i - 1);
    }
    printf("\n");
    free(polinomTomb);
}