#include <stdio.h>
#include <string.h>

char elsoSor[512];
char masodikSor[512];

int main() {
    printf("Kerem az elso sort (Ekezet nelkul)! ");
    gets_s(elsoSor, 512);
    printf("Kerem a masodik sor (Ezt is ekezet nelkul)!" );
    gets_s(masodikSor, 512);

    int elsoMaganhangzoi = 0;
    int masodikMaganhangzoi = 0;
    char elsoUtolsoMaganhangzoja;
    char masodikUtolsoMaganhangzoja;

    for (long long i = 0; i < (long long)strnlen_s(elsoSor, 512); i++) {
        // Maganhangzo keresese, switchel tobbet is lehet egyszerre ellenozizni, ha nincs break
        switch(elsoSor[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            elsoUtolsoMaganhangzoja = elsoSor[i];
            elsoMaganhangzoi++;
        }
    }
    for (long long i = 0; i < (long long)strnlen_s(masodikSor, 512); i++) {
        // Maganhangzo keresese, switchel tobbet is lehet egyszerre ellenozizni, ha nincs break
        switch(masodikSor[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            masodikUtolsoMaganhangzoja = masodikSor[i];
            masodikMaganhangzoi++;
        }
    }

    if (masodikUtolsoMaganhangzoja != elsoUtolsoMaganhangzoja)
        printf("Nem rimel a ketto!\n");
    else if (masodikMaganhangzoi != elsoMaganhangzoi)
        printf("Rimel a ketto, de csak gyengen!\n");
    else
        printf("Erosen rimel a ket sor!");
}