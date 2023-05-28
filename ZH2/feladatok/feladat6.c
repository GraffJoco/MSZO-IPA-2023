#include <stdio.h>
#include <stdlib.h>

#define fajlNev "sudoku.txt"

char tabla[81]; // 9x9-es tabla

// Azért, hogy egyszerűbb legyen koordinátákkal dolgozni, csinálok egy kis
// függvényt, ami a koordinátákból tömbindexet csinál
int koordinatabolindex(int x, int y) {
    return y * 9 + x;
}

int main() {
    FILE* input; fopen_s(&input, fajlNev, "r");
    if (input == NULL) {
        printf("A %s fajlt nem sikerult megnyitni\n",fajlNev);
        return -1;
    }

    // Beolvasás
    char temp;
    int index = 0;
    
    // Feltételezhetjük, hogy jó a fájl, és 81 értéket kell beolvasnunk
    while (index != 81) {
        temp = (char)getc(input);
        
        // Szűrünk, hogy csak jó karakterek kerüljenek a tömbbe
        // Itt switchel csinálom (break nélkül, mert akkor több érték futtatja ugyanazt a kódot),
        // de if is ugyanúgy elfogadható természetesen
        switch (temp) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'x':
                tabla[index] = temp;
                index++;
                break;
        }
    }

    // Koordináta bekérése
    int x;
    int y;
    printf("Adjon meg egy ellenorizendo koordinatat! (szokozzel elvalasztva): ");
    scanf_s("%d %d", &x, &y);

    x--; y--; // Csökkentjük, mert az emberek 1-9-ig számolnak koordinátát, a számítógép pedig 0-8-ig számol

    // Cella ürességének ellenőrzése
    // Először megnézzük, hogy értelmes-e a koordinátapár
    if (x < 0 || x > 8 || y < 0 || y > 8) {
        printf("Ertelmetlen koordinatat adott meg!\n");
        exit(0);
    }
    // A cella ürességének *valódi* ellenőrzése
    if (tabla[koordinatabolindex(x, y)] != 'x') {
        printf("A cella nem ures!\n");
        exit(0);
    }

    // A beírandó szám kérése
    char beirando;
    printf("Milyen erteket kivan beirni? ");
    // Szóköz fontos itt, mert karakterbeolvasásnál különben nem mellézné az üres (pl. újsor) karaktereket!
    // Eredetileg itt egy csúnya sprintf-es hacket raktam (működik, de szuboptimális)
    scanf_s(" %c", &beirando);

    
    // Ideje ellenőrizni az érték helyességét
    // Első if a sorok, a második az oszlopok helyességét ellenőrzi
    for (int i = 0; i < 8; i++) {
        if (tabla[koordinatabolindex(i, y)] == beirando) {
            printf("Nem lehet beirni az erteket!\n");
            exit(0);
        }
        if (tabla[koordinatabolindex(x, i)] == beirando) {
            printf("Nem lehet beirni az erteket!\n");
            exit(0);
        }
    }

    // Almező ellenőrzése
    /*
    Ehhez részletesebb magyarázatot adok, hogy érthető legyen
    Az kell, hogy az almező első (minimális x és y) koordinátáját megszerezzük,
    mivel akkor lehet egy [[0;0];[2;2]]-es dupla forciklussal ellenőzizni az összes ottani értéket
    De ezt hogy lehet megcsinálni?
    Gondolkozzunk: mi igaz az összes almező sarkára? Oszthatóak 3-mal (0; 3; 6 a sarokponti koordináta), tehát koord % 3 == 0
    Úgy lehet ezt kinyerni a mostani koordinátánkból, hogy a nem 3-mal osztható részét kivonjuk, tehát:
    x_sarok = x - (x % 3);
    Utána a for ciklusokban lehet ehhez adni az ideiglenes értéket, így a for ciklus az almező össze koordinátáját ellenőrzi
    */

    int x_sarok = x - (x % 3);
    int y_sarok = y - (y % 3);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (tabla[koordinatabolindex(x_sarok + i, y_sarok + j)] == beirando) {
                printf("Nem lehet beirni az erteket!\n");
                exit(0);
            }
        }

    // Ha ide eljutottunk, akkor beírható
    printf("Be lehet irni az erteket!\n");

    fclose(input);
}