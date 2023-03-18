#include <stdio.h> // Konzolon keresztül kommunikálás a felhasználóval

int main() {
    unsigned long long int x; //elméletileg akármelyik egész típus működne, de ez adja a legnagyobb egész intervallumot

    printf("Adjon egy pozitív egész számot! ");
    scanf_s("%lld", &x); //beolvasás

    while (x != 1) {
        printf("%lld\n",x);

        if (x % 2 == 0){
            //Ha x páros (kettővel osztás maradéka 0)
            x /= 2; //x felezése
        } else {
            //Ha nem az
            x *= 3;
            x++;
        }
    }
    printf("%lld\n",x); // egy végső alkalommal kiírjuk x-et, mert különben nem írja ki a végső értékét (1)
}