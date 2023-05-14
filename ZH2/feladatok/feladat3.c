#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
    char str[64];
    gets_s(str, 64);

    int strHossz = strnlen_s(str, 64);
    uint8_t checksum = 0;

    for (int i = 0; i < strHossz; i += 2) {
        if (i != strHossz - 1) {
            // Ha nem az utolso karakternel vagyunk (mert strHossz paratlan is lehet)
            checksum += str[i] ^ str[i + 1];
        } else {
            checksum += str[i];
        }
    }

    printf("A szoveg checksuma: %hhu\n", checksum);
}