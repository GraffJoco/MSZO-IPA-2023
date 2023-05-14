#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main() {
    FILE* input; fopen_s(&input, "adatok.csv", "r");
    assert(input);

    // 1. sor átugrása
    do {

    } while (getc(input) != '\n');

    double kiadasSzumma = 0;
    double bevetelSzumma = 0;
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