#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main() {
    srand((unsigned int)time(NULL));
    int n;
    do {
        scanf_s("%d", &n);
    } while (n <= 0);

    double* szamok = (double*) malloc(n * sizeof(double));
    double szumma = 0.0;

    FILE* output; fopen_s(&output, "output.txt", "w");
    assert(output);

    for (int i = 0; i < n; i++) {
        szamok[i] = (double)rand() / RAND_MAX * 100;
        szumma += szamok[i];
        fprintf(output, "%lf\n", szamok[i]);
    }

    double max = szamok[0];
    double min = szamok[0];
    for (int i = 1; i < n; i++) {
        if (min > szamok[i]) min = szamok[i];
        if (max < szamok[i]) max = szamok[i];
    }

    fprintf(output, "Maximum ertek: %lf\n", max);
    fprintf(output, "Minimum ertek: %lf\n", min);
    fprintf(output, "Atlagertek: %lf\n", szumma/n);

    fclose(output);
    free(szamok);
}