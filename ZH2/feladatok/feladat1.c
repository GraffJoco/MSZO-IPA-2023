#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    // Fájl objektum létrehozása
    FILE* szoveg; fopen_s(&szoveg, "szoveg.txt", "r");
    assert(szoveg);

    // Fájl hosszának megszerzése
    fseek(szoveg, 0, SEEK_END);
    int fajlHossz = ftell(szoveg);
    fseek(szoveg, 0, SEEK_SET);

    // Beolvasás
    char* fajlTomb = (char*)malloc(fajlHossz);
    int index = 0;
    while (!feof(szoveg)) {
        fajlTomb[index] = getc(szoveg);
        index++;
    }

    // Mostantól maxHossz a leghosszabb szó hosszát tartalmazza,
    // index pedig a helyét fajlTomb-ben
    int maxHossz = 0;
    index = 0;
    int mostaniHossz = 0;

    for (int i = 0; i < fajlHossz; i++) {
        // Szó vége
        if (fajlTomb[i] == ' ' || fajlTomb[i] == '\n' || fajlTomb[i] == '\r' || fajlTomb[i] == '.' || fajlTomb[i] == ',' || i == fajlHossz - 1) {
            if (mostaniHossz > maxHossz) {
                index = i - mostaniHossz;
                maxHossz = mostaniHossz;
            }
            mostaniHossz = 0;
        } else {
            mostaniHossz++;
        }
    }
    
    printf("A leghosszabb szo %d betu hosszu!\n", maxHossz);
    printf("A leghosszabb szo pedig: ");
    for (int i = index; i < index + maxHossz; i++)
        printf("%c", fajlTomb[i]);
    printf("\n");

    free(fajlTomb);
    fclose(szoveg);
}