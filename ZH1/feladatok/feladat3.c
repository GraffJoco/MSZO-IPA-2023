#include <stdio.h>
#include <math.h>

//A függvények, math.h-val
double emathhval(int n){
    return pow(1.0 + (1.0 / (double)n), (double)n);
}
double ekmathhval(int n, double k){
    return pow(1.0 + (k / (double)n), (double)n);
}

//A függvények math.h nélkül
double emathhnelkul(int n){
    double vegertek = 1.0;
    double hatvanyalap = 1.0 + (1.0 / (double) n); //kiszámoljuk a hatvány alapját
    // n-szer összeszorozzuk a hatványalapot, ergó alap^n, és pont ez kell nekünk
    for (int i = 0; i < n; i++)
        vegertek *= hatvanyalap;
    return vegertek;
}

double ekmathhnelkul(int n, double k){
    double vegertek = 1.0;
    double hatvanyalap = 1.0 + (k / (double) n); //kiszámoljuk a hatvány alapját
    // n-szer összeszorozzuk a hatványalapot, ergó alap^n, és pont ez kell nekünk
    for (int i = 0; i < n; i++)
        vegertek *= hatvanyalap;
    return vegertek;
}

int main() {
    int nbe = -1;
    double kbe;

    //do while ciklus, ugyanaz, mint a while, csak lefut és *utána* ellenőrzi, hogy igaz-e a feltétel
    do {
        printf("Adja meg a közelítési változót e számításánál (e legyen pozitív és egész)! ");
        scanf_s("%d", &nbe);
    } while (nbe < 1);

    printf("Adja meg, hogy e hanyadik hatványát kéri! ");
    scanf_s("%lf",&kbe);

    printf("e^%lf = %lf\n", kbe, ekmathhnelkul(nbe,kbe));
}