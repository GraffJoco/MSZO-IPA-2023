# **2. zárthelyi anyagai**

*(Itt már feltételezzük, hogy az 1. ZH anyagát értitek, ha valamit nem értetek, nézzetek rá az 1. ZH anyag fájljára!)*

# Stringek

## Alapok

A *string*, ellentétben más nyelvekkel, nem külön típus, hanem csak egy pointer, ami egy karaktertömbhöz mutat (`(const) char*`). A szoftver úgy határozza meg a string végét, hogy addig olvas, amíg nem fut bele a 0-s ASCII karakterbe (`\0`).  
Példa arra, hogy hogyan néz ki egy string:  

```C  
const char* tesztString = "Hello";
```  

Az adatok a memóriában így néznek ki:  
| index | 0 | 1 | 2 | 3 | 4 | 5 |
| --- | --- | --- | --- | --- | --- | --- |
| érték (ASCII) |  'H' | 'e' | 'l' | 'l' | 'o' | '\0' |
| érték (tízes számrendszer) | 72 | 101 | 108 | 108 | 111 | 0 |

Ez a rendszer (keresi a `\0` bytot) viszont természetesen egyszerűen vezethet komoly hibákhoz (főleg kicímzéshez), ezért biztonságos (`_s`) verziói is vannak a gyakori stringfüggvényeknek, hogy ne tegye hibássá/támadhatóvá a stringkezelés a programunkat.  
Ezeket a függvényeket a `<string.h>` beépített könyvtárban lehet elérni

### **Beépített string vs. pufferes string**

A stringeknél, ha nem figyelsz, egyszerű kicímezni, jóval egyszerűbb, mint a tömböknél, és ez a rész azért van, hogy leírjak pár alapszabányt. Először is el kell magyaráznom az itteni két stringfajtát.  

**Beépített (built-in) string**:  
Ezek már a fordításkor beágyazódnak a programba, ezek azok a stringek, amiket ekkor is használtunk:  
`"Ez egy beépített string"`  
Az idézőjelek közötti szövegek mind azok. Ez egyszerűvé teszi a szövegek írását, viszont van egy hátránya is: Mivel beépül magába a programba, ezért módosíthatatlan (mint egy *const* érték), ezért a típusneve `const char*`. Akármilyen módosítási próba errorhoz vagy crashez vezet.

**Pufferes string**  
Ezek a stringek nem olyan egyszerűen hozhatóak létre, de módosíthatóak. Itt valódi karaktertömbökről van szó, tehát a két létrehozási mód természetesen:

```C
char pufferesStatikusString[hossz]; //Statikus tömb, ami karakterkkel feltölthető

char* pufferesDinamikusString = malloc(hossz); //Dinamikus tömb, free-ről meg ne feledkezz!
```

## Alapfüggvények

### **strnlen_s**

A szöveg hosszát adja vissza. Az `strlen` függvény biztonságos verziója, használata a következő:  

```C
size_t strnlen_s(const char* str, size_t hossz);
```

*(`size_t`-től nem kell megijedni, csak egy egész típus, ugyanúgy szám, mint pl.: a long long vagy az int)*  

- $str$ természetesen a szövegünk, amit extra karakterek (&) nélkül adunk meg  
- $hossz$ a kicímzés elkerülésének érdekében az az érték, aminél ha hosszabb a string (vagy legalábbis ha eddig eljut 0 karakter megtalálása nélkül), akkor a függvény leáll, visszaadva $hossz$-t  

Itt egy példa a potenciális hasznára:

```C
#include <string.h>
#include <stdio.h>

int main() {
    const char* szoveg = "Tesztszöveg";
    printf("A tesztszövegünk: %s\n", szoveg);
    printf("Ennek a hossza: %lld", strnlen_s(szoveg,32));
    //32 egy alapszám, ami nagyobb a valódi hossznál, de elég kicsi, hogy a mi memóriaterületünkön maradhassunk
}
```

### **strcpy, strncpy**

Ezek a függvények egyik stringből a másikba másolnak.  
Egy fő különbség van: `strncpy` egy harmadik paramétert is kér, hogy hány bytot másoljon át  
*(Megj. ezzel kapcsolatban: mivel átmásolja a bytokat, de nem az egész stringet, kicímzés elkerüléséért manuálisan kell a 0 karaktert a végére rakni!)*

```C
char* strcpy(char* hova, const char* honnan);
char* strncpy(char* hova, const char* honnan, size_t mennyit);
```

Itt visszaad egy értéket, ami valójában csak $hova$ értéke, tehát általában mellőzhető  
Ennek sok haszna van, pl.: built-in stringet át lehet másolni pufferes stringbe (másik irányba nem lehet):

```C
#include <string.h>

const char* binstr = "Hello World!";

int main() {
    char pufStr[64]; //Hossz legyen minimum strlen(binstr) + 1, különben kicímzés!

    strcpy(pufStr, binstr);
}
```

### **strcat_s, strncat_s**

A szövegek összeadása közel sem olyan egyszerű a C-ben, mint más nyelvekben, ezért ezt most részletesen fogom leírni.  
  
Először nem néz ki túl nehéznek:

```C
strcat(A, B); // A += B más nyelvekben

//"Biztonságos" verziók, amiket mi fogunk használni
strcat_s(char* A, size_t AMerete, const char* B);
strncat_s(char* A, size_t AMerete, const char* B, size_t BbolHanyBytot);
```

De van egy probléma: ha nincsen A-ban legalább `strlen(B)` használatlan byte, akkor kicímzünk. Természetesen van az strcat-nek biztonságos verziója, DE ez azt jelenti, hogy amikor kicímezne, akkor onnantól levágja a szöveg végét:  

```C
char A[10];
strcpy(A, "Hello, ");
const char* B = "World";
strcat_s(A, 10, B);

printf("%s", A);
```

Ez a program fut, de az output hibás lesz (maga a hiba esetfüggő, néha nincs hely, és hiányzik a 0 karakter, néha a string részei vannak levágva), ezt hogyan oldjuk meg?  
  
Természetesen több elfogadható megoldás van, a legegyszerűbbhöz csak egy szimpla kérdést kell feltenni: Baj az, ha $A$-nak több helyet adunk a RAM-ban, mint kellene?  
Egyszerű a válasz: **NEM, adhatunk neki több helyet, mint amennyit használ!**  
Adjunk neki elfogaható mennyiségű bytot, ami több, mint amire szükségünk lesz, és abból baj nem nagyon lehet. Kis kódot írunk modern gépen, kit érdekel, ha 1 KB-tal többet foglal a progamunk, mint ami optimális lenne?  
Esetfüggő, hogy mennyit kell, de mondjuk egy nem nagy stringnek lehet 50-1000 bytot adni. Itt egy módosítása az előző kódnak, ami működik:  

```C
char A[1024];
strcpy(A, "Hello, ");
const char* B = "World";
strcat_s(A, 10, B);

printf("%s", A);
```

Probléma megoldva!  
Ezt nem kell *mindig* csinálni, de ha változó hosszú a string kimenet, akkor így egyszerűen el lehet kerülni pár nagyon csúnya kicímzést.  

### **sprintf_s**  

Ez (személyes véleményem szerint) a leghasznosabb stringfüggvény (`strlen` kivételével): Ugyanúgy írhatsz stringet, mint ahogy a konzolba írnál.  

A függvény a `printf` paraméterek előtt kettő stringparamétert kér, a többi azonos:  

```C
sprintf_s(char* string, size_t strMeret, char* szoveg, ...);
```

Itt egy példa:

```C
double pi = 3.14159;
char* pistr = malloc(16); // Nagyobb a kimenetnél, a biztonság kedvéért
char* valodipistr = malloc(16);

sprintf_s(pistr, 16, ".2%lf", pi); // pistr = "3.14"
sprintf_s(pistr, 16, ".0%lf", pi); // valodipistr = "3"

free(pistr);
free(valodipistr);
```

### **stringből számérték**

Mi van, ha stringből akarsz számot csinálni? Erre vannak függvények természetesen, de nem a `string.h`-ban, hanem a `stdlib.h`-ban!  
Sok van belőlük, de itt vannak a fontosak:  
| típus | függvény |
| --- | --- |
| int | atoi |
| long long (int) | atoll |
| double | atof |

Például:

```C
long long man = atoll("54321");
printf("%lld", man); //54321
```
