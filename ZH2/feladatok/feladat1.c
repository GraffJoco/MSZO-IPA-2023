#include <stdio.h>

#define fajlNev "szoveg.txt"

int main() {
    // Fájl objektum létrehozása
    FILE* szoveg; fopen_s(&szoveg, fajlNev, "r");
    if (szoveg == NULL) {
        printf("A %s fajlt nem sikerult megnyitni!\n",fajlNev);
        return -1;
    }

    int maxHossz = 0;
    int mostHossz = 0;
    char leghosszabbSzo[64];
    
    while (!feof(szoveg)) {
        // Itt switchet használok, mert gyorsabb
        // egy if természetesen ugyanúgy működne
        switch (getc(szoveg)) {
        case '.':
        case ',':
        case ' ':
        case ':':
        case '\n':
            // Szó hosszanalízise
            if (mostHossz > maxHossz) {
                // Vissza mozgatja a kurzort, hogy a stringet bemásolhassuk a pufferünkbe
                fseek(szoveg,-mostHossz-1,SEEK_CUR);
                fgets(leghosszabbSzo,mostHossz+1,szoveg);
                maxHossz = mostHossz;
            }
            mostHossz = 0;
            break;
        default:
            mostHossz++;
            break;
        }
    }

    printf("A leghosszabb szo: %s\n",leghosszabbSzo);
    printf("A szo %d betus!\n",maxHossz);

    fclose(szoveg);
}