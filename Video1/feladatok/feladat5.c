#include <stdint.h>  //int8_t: egy bytos egész (helyette char is használható)
#include <stdio.h>
#include <stdlib.h>

int main() {
    int8_t sum;
    int8_t miSumunk = 0;
    double x;

    // Beolvasás
    printf("Kérek egy számot! ");
    scanf_s("%lf", &x);
    printf("Kérek egy checksumot! ");
    scanf_s("%hhd", &sum);

    // Mi checksumunk elkészítése

    // Átmegyünk x bytejain
    int8_t* xTomb = (int8_t*)&x;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            miSumunk += xTomb[i] >> j & 1;
    /*
    Bitvarázs magyarázva:
        Először vesszük xTomb i. elemét (byteját)
        Utána a byte értékét eltoljuk j-vel, ezért a bit, amit keresünk,
        az első helyiértéken lesz, de van még egy teendő:
        az eltolással nem garantáltuk, hogy a j. bit az egyetlen, ami a számban marad,
        ezt az & 1 utasítással oldjuk meg, és így csak az egyes helyiértéken lévő
        bit értéke (i. byte j. bitje) lesz az eredmény
        Ez egy 0 vagy 1, és pont annyival kell növelni miSumunk értékét,
        tehát egy sima += utasítás növeli
    */

    // Jöjjön az összehasonlítás:
    if (sum == miSumunk) {
        printf("A két checksum egyenlö!\nÉrtéke: \n");
        // forciklusunk [0;7] között megy visszafele, mert először a
        // legnagyobb helyiértéket kell kiírni bitreprezentálásnál
        for (int i = 7; i >= 0; i--)
            printf("%d", sum >> i & 1);
        // Ugyanolyan bitvarázs, mint ezelőtt
    } else {
        printf("A két cheksum nem stimmel!\nMi checksumunk: ");
        for (int i = 7; i >= 0; i--)
            printf("%d", sum >> i & 1);
        printf("\nA sum, amit a programunk számoltunk: ");
        for (int i = 7; i >= 0; i--)
            printf("%d", miSumunk >> i & 1);
        
        printf("\nA két checksum összehasonlítva: ");
        for (int i = 7; i >= 0; i--)
            if ((sum >> i & 1) == (miSumunk >> i & 1))
                printf("%d", sum >> i & 1);
            else printf("x");
    }
    printf("\n");
}