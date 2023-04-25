#include <stdio.h>
#include <stdlib.h> // dinamikus tömb, és rand()
#include <stdint.h> // ha tudni kell, hogy hány bites egészt használunk, ezzel a legegyszerűbb

int main() {
    uint8_t n; //uint8_t előjel nélküli és 8-bites, de unsigned char-t is lehet használni, ha nem használod a stdint.h-t

    scanf_s("%hhd",&n);

    // A dinamikus tömb mindig pointer, calloccal n db, sizeof(int32_t) (= 2) elemhosszú memóriát kaptunk
    int16_t* tomb = calloc(n,sizeof(int16_t));

    //feltöltés random számokkal
    for (int i = 0; i < n; i++) {
        tomb[i] = rand(); // A rand függvény intet ad vissza, ami 32 bites
        printf("%d; ",tomb[i]); //Az elemet azonnal ki lehet írni
    }
    printf("\n"); //Kiírás után új sor!

    int16_t max, min;
    //beállítjuk a tömb első elemének, hogy a kimenet BIZTOS a tömb eleme legyen
    max = tomb[0];
    min = tomb[0];
    int32_t szumma = 0; //Azért nem 16-bites, mert lehet, hogy a szumma a 32-bites egész típus kapacitásánál nagyobb

    for (int i = 0; i < n; i++){
        szumma += tomb[i];
        if (tomb[i] > max) max = tomb[i];
        if (tomb[i] < min) min = tomb[i];
    }

    printf("A tömb maximum értéke: %d\n",max);
    printf("A tömb minimum értéke: %d\n",min);
    printf("A tömb értékeinek átlaga: %lf\n",(double)szumma/n);

    //ha nem használjuk a dinamikus tömböt, KÖTELEZŐ felszabadítani a memóriát
    free(tomb);
}