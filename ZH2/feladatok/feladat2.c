#include <stdio.h>
#include <stdbool.h>

#define fajlNev "adatok.csv"

int main() {
    FILE* input; fopen_s(&input, fajlNev, "r");
    if (input == NULL) {
        printf("A %s fajlt nem sikerult megnyitni!\n",fajlNev);
        return -1;
    }

    // 1. sor átugrása
    do {

    } while (getc(input) != '\n');

    double kiadasSzumma = 0;
    double bevetelSzumma = 0;
    // int is használható (false/true helyett 1/0 értékekkel)
    bool voltVesztesegesHonap = false;

    int mostaniHonap;
    double mostaniKiadas;
    double mostaniBevetel;
    for (int i = 0; i < 12; i++) {
        fscanf_s(input,"%d",&mostaniHonap);
        fscanf_s(input,"%lf",&mostaniKiadas);
        fscanf_s(input,"%lf",&mostaniBevetel);

        kiadasSzumma += mostaniKiadas;
        bevetelSzumma += mostaniBevetel;

        if (mostaniBevetel < mostaniKiadas) {
            voltVesztesegesHonap = true;
            printf("A %d. honap veszteseges volt!\n", mostaniHonap);
        }
    }
    if (!voltVesztesegesHonap) printf("Nem volt veszteseges honap!\n");

    printf("Az atlag profit ado nelkul: %lf\n", (bevetelSzumma - kiadasSzumma)/12);
    printf("Az osszprofit adozas utan: %lf\n", bevetelSzumma * (1.0 - 0.27) - kiadasSzumma);

    fclose(input);
}