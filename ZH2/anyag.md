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
#Define hossz 101 //Ez 100 hosszúnak számít mert a 101. a \0 (101. légió)

char pufferesStatikusString[hossz]; //Statikus tömb, ami karakterkkel feltölthető

char* pufferesDinamikusString = (char*)malloc(hossz); //Dinamikus tömb

free(pufferesDinamikusString) //free-ről meg ne feledkezz!
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

### **strcpy_s, strncpy_s**

Ezek a függvények egyik stringből a másikba másolnak.  
Egy fő különbség van: `strncpy_s` egy harmadik paramétert is kér, hogy hány bytot másoljon át  
*(Megj. ezzel kapcsolatban: mivel átmásolja a bytokat, de nem az egész stringet, kicímzés elkerüléséért manuálisan kell a 0 karaktert a végére rakni!)*

```C
char* strcpy_s(char* hova, size_t mennyit, const char* honnan);
char* strncpy_s(char* hova, size_t mennyitOda, const char* honnan, size_t mennyitOnnan);
```

Itt visszaad egy értéket, ami valójában csak $hova$ értéke, tehát általában mellőzhető  
Ennek sok haszna van, pl.: built-in stringet át lehet másolni pufferes stringbe (másik irányba nem lehet):

```C
#include <string.h>

const char* binstr = "Hello World!";

int main() {
    char pufStr[64]; //Hossz legyen minimum strlen(binstr) + 1, különben kicímzés!

    strcpy_s(pufStr, 64, binstr);
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
strcpy_s(A, 10, "Hello, ");
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
strcpy_s(A, 1024, "Hello, ");
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
char* pistr = (char*)malloc(16); // Nagyobb a kimenetnél, a biztonság kedvéért
char* valodipistr = (char*)malloc(16);

sprintf_s(pistr, 16, ".2%lf", pi); // pistr = "3.14"
sprintf_s(valodipistr, 16, ".0%lf", pi); // valodipistr = "3"

free(pistr);
free(valodipistr);
```

### **sscanf_s**

Ha a printf-nek van stringes verziója, akkor természetesen a scanf-nek is, ez a `sscanf_s` (biztonságos verzió, természetesen). A függvény egy extra paraméterrel tér csak el konzolos verziójától:  

```C
sscanf_s(char* string, char* forma, ...);
```

- $string$: a stringpuffer, ahonnan olvasunk
- $forma$: a scanf-es formázás, ahol kijelentjük, hogy mit keresünk (pl.: double olvasásnál `"%lf"`)
- **...**: extra változók, amibe olvassuk az értéket (itt is pointert kell megadni, &-ről meg ne feledkezz!)
  
### **Beolvasás konzolból**

A `scanf_s` nem jó szöveg beolvasásához, ezért a `gets_s` függvényt használjuk, ami nagyon hasonlít univerzális megfelelőjére:

```C
gets_s(char* str, size_t str_hossza);
```

Itt $str$-t írja felül, és biztonságos (_s), ezért ha $str$ hossza nem túl alacsony, az egész szöveg probléma nélkül bekerül a változónkba.

### **stringek összehasonlítása**

Mit csinálj, ha két stringet össze akarsz hasonlítani? Ha például két string azonosságát akarod ellenőrizni, `str1 == str2` nem használható, az csak a *pointer* értékét, nem a string *tartalmát* hasonlítja össze. Erre megoldás a `strcmp` és `strncmp` függvény.

```C
int strcmp(char* str1, char* str2);
int strncmp(char* str1, char* str2, size_t mennyit);
```

A stringek értéke alapján három lehetséges kimenet van:

- 1, ha $str1 > str2$
- 0, ha $str1 = str2$
- -1, ha $str1 < str2$

Itt egy példa gyakorlati hasznára:

Ahogy a kód más nyelvben (Pythonban) nézne ki:

```Python
szereti = input("Nagyon szereted a tejet? ")
if szereti == "Igen":
    kakaot = input("És a kakaót is? ")
    if kakaot == "Azt is":
        print("Jó")
    else:
        print("Szomorú, de ok")
else:
    print("Laktózérzékeny vagy, vagy csak hülye?")
```

Ennek a C megfelelője:

```C
#include <stdio.h>
#include <string.h>

char szereti[64];
char kakaot[64];

int main() {
    printf("Nagyon szereted a tejet? ");
    gets_s(szereti, 64);
    if (strcmp(szereti, "Igen") == 0) {
        printf("Es a kakaot is? ");
        gets_s(kakaot, 64);

        if (strcmp(kakaot, "Azt is") == 0)
            printf("Jo");
        else
            printf("Szomoruva tettel");
    } else printf("Do you are have stupid?");
}
```

### **Keresés egy stringben**

Ha egy stringben keresni akarsz egy karaktert/szövegrészletet, akkor a `strch` és `strstr` (igen, így hívják valamiért) függvényeket használd. Ezek megkeresik az első helyet, ahol a keresett érték megjelenik, és visszaadják a helyét (értsd: pointerét). Amennyiben nem találja a keresett értéket, $NULL$-t ad vissza  
A hely külön stringként is használható, csak arról meg ne feledkezzetek, hogy az eredeti és itt szerzett string akármilyen módosítása mindkettőre érvényes!

```C
char* strch(char* string, char keresettKarakter);
char* strstr(char* string, char* keresettString);
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

### **split, csak rosszabb**

A C-ben, mint programnyelvben van számtalan gyors, szép és/vagy hatékony függvény, ami azt csinálja, amit akarsz. Ezeken a kategóriákon kívül meg ott van az `strtok`, ami megválaszolja a kérdést: hogy lehet a stringek szétdarabolását tönkretenni?  
Szerencsére, habár ez a függvény az anyag része, szinte biztos nem lesz a ZH-ban, előadáson egyértelmű volt, hogy nem csak én nem szeretem ezt a függvényt.

A függvény a következő képpen működik:

```C
char* strtok(char* string, char* keresett);
```

Itt a stringnek a következő előfordulását küldi el neked, mint karakterpointer. Hogyan tudja, hogy melyik volt az előző viszont?  
Úgy, hogy **AZ STRTOK TÖNKRETESZI A STRINGET**  

Tehát nem optimális, ha stringedet meg kívánod tartani módosítás nélkül (ergo. szinte mindig). Mit csinálj, hogy a stringedet ne tegye tönkre? *Csinálsz egy másolatot, hadd roncsolja azt*:

```C
// Itt str az eredeti string, amit nem kívánunk módosítani
char* strDeRoncsolhato = (char*)malloc(strnlen_s(str, 2048)); // 2048 csak egy random szám itt

strcpy_s(strDeRoncsolhato, strnlen_s(str, 2048), str);

char* strDarab;

while (1) {
    strDarab = strtok(strDeRoncsolhato, " "); // Mintha egy splittömb i. elemét használnád más nyelvben
    if (strDarab == NULL) break; // Ha nem talál semmit, kilépünk

    // strDarabbal csinálhatunk itt, amit akarunk
}

free(strDeRoncsolhato);
```

Amennyiben rendesen, stringkárodítás nélkül akarjátok megcsinálni, így lehet függvényt írni erre:

```C
char* strSplit(char* str, char* keresendoErtek, int hanyadik) {
    char* kezdo = str;
    
    for (int i = 0; i < hanyadik; i++) {
        kezdo = strstr(kezdo, keresendoErtek);
        if (kezdo == NULL) return NULL;
    }

    char* vegso = strstr(kezdo, keresendoErtek);
    if (vegso == NULL) return kezdo;

    long long strHossz = (long long)vegso - (long long) kezdo;

    char* rtn = (char*)malloc(strHossz + 1); // + 1, mert a 0 karakter automatikusan nem kerülne bele
    rtn[strHossz] = '\0';

    strncpy_s(rtn, strHossz, kezdo, strHossz);

    return rtn; // rtn-t majd fel kell szabadítani!
}
```

# **Fájlok**

## Alapok  

A fájlkezelés a C-ben változó nehézséggel rendelkezik attól függően, hogy beolvasunk, vagy kiírunk: fájlt írni egyszerű, beolvasni nem az, ugyanis az olvasáshoz dinamikus hosszal rendelkező stringekkel kell dolgozni.  

A fájlprotokoll a `stdio.h` könyvtár része, tehát nem kell importálni még egy könyvtárat.  

A fájl egy pointerobjektummal működik, a `FILE*` típussal. Egy fájl beolvasásához a `fopen_s` függvényt használjuk, melynek az első argumentuma a fájl helyének egy stringje, a másik is egy string, ami a kódja a beolvasás/írás típusának (ez nem az összes, de ezek a fontosak, itt is csak a w/r-t, és bináris verzióját kell tudni):  

| kód | "w" | "r" | "a" | "wb" | "rb" | "ab" |
| --- | :-: | :-: | :-: | :-: | :-: | :-: |
| jelentés | Fájl írása | Fájl olvasás | Fájl végére írás | Fájl írása bináris módban | Fájl olvasása binráis módban | Fájl végére írás bináris módban |
| Kell a fájlnak léteznie? | | X | | | X | |

A fájl helye, mint argumentum lehet relatív (az exe mappájához képest) vagy abszolút (egész fájlhelyet kiírjuk), ezt automatikusan tudja, de fontos megjegyezni, hogy mivel a Windows a fájlpozícióknál \ (fordított per, alt gr + Q) karaktereket használ, és a C-ben a \ speciális karaktert jelent, az összes \ ből legyen kettő (\ helyett \\\\) a stringben, vagy különben a fordító errort fog adni és/vagy rossz helyen keres fájlt.

A fájlt természetesen majd be is kell zárni, erre az `fclose()` függvény szolgál. Úgy gondoljatok az `fopen`-`fclose` függvények relációjára, mint a `malloc`-`free`-re.

Egy példa:

```C
FILE* fajl;
fopen_s(&fajl, "D:\\Long\\Long\\fajl.txt", "w");

// Fájlírás

fclose(fajl);
```

A $malloc$-hoz hasonlóan az `fopen` függvény sem tud mindig lefutni sikeresen, de ellentétben az előzővel, itt figyelni kell arra, hogy ez ha megtörténik, ne okozzon katasztrofális hibát. Erre több módszer is van, megmutatom a kettő legegyszerűbbet:  

- if: ha a függvény sikertelen, a változónk értéke $NULL$, amit egy iffel tudunk ellenőrizni, ha az if igazad ad vissza, baj történt, bezárjuk a programot:  

```C
FILE *input;
fopen_s(&input, "C:\\nincs\\ilyen\\ami\\nem\\jó.csv","r");

if (input == NULL) {
    printf("ERROR! A fájlbeolvasás sikertelen volt!");
    exit(-1); //stdlib.h kell ehhez a függvényhez!
}

// ...

fclose(input);
```

- assert: az `assert.h` könyvtár névadó makrója ezt csinálja, de egyszerűbben: adunk neki egy paramétert, a programot leállítja, ha az $NULL$ (amúgy assertet malloc sikeres lefutásának ellenőrzéséhez is lehet használni):  

```C
FILE* input;
fopen_s(&input, "nemletezikezkollega.json", "r");
assert(input); // assert.h kell hozzá, de egyszerű használni

//...

fclose(input);
```

Most, hogy a fájlobjetummal tudunk dolgozni, ideje a *valódi* fájlkezelésre

## Fájlírás

Mint ezelőtt mondtam, ez az egyszerűbb része a fájlkezelésnek, tehát ezzel kezdjük  

Gyakorlatilag ugyanazt csináljuk, mint a stringírásnál, ugyanis a fájloknak is van saját print függvénye: `fprintf`  

Így a fájlírás úgy mehet, mintha a konzolba írnánk:  

```C
#include <assert.h>
#include <stdio.h>

int main() {
    FILE* output
    fopen_s(&output, "kiiras.txt", "w");
    assert(output);

    fprintf(output, "Sima söveget lehet,\n");
    fprintf(output, "De megy a behelyettesítés is, pl.: pi = %lf\n", M_PI);
    for (int i = 0; i < 10; i++)
        fprintf(output, "A ciklusok is természetesen működnek, ez a %d. iteráció\n", i);

    fclose(output);
}
```

## Fájlolvasás

Erre több fajta megoldás is van természetesen, tehát átmegyünk rajtunk egyesével:

- `fscanf_s`: természetesen így is lehet beolvasni, habár nem ajánlott. Így szöveget nem tudunk beolvasni, de ha tudjuk, hogy hogy vannak formáva az elemek a fájlban (és csak számok vannak), akkor természetesen be lehet olvasni ezzel. Fontos megjegyzés, hogy a függvény nem csak az újsor, hanem a szóköz karaktert is elválasztónak tekinti, tehát nem lehet pl.: "%d %lf" formátummal olvasni, több utasítás kell.

Példa:

$adat.txt$ fájl:

```text
550 600 900
```

$main.c$ fájl:

```C
#include <stdio.h>
#include <assert.h>

int adatok[3];

int main() {
    FILE* input;
    fopen_s(&input,"adat.h","r");
    assert(input);
    
    for (int i = 0; i < 3; i++)
        fscanf_s(input, "%d", adatok + i);
    
    printf("A beolvasott adatok: ");
    for (int i = 0; i < 3; i++)
        printf("%d ", adatok[i]);
    printf("\n");

    fclose(input);
}
```

Ez általában nem működik, tehát nem ajánlott, de ha lehet alkalmazni, ez a legegyszerűbb megoldás.

- fgets: Ha egy stringbe akarjuk beolvasni a fájlunkat, akkor az `fgets` függvényt használjuk, aminek a következők a paraméterei:

```C
char* fgets(char* string, int stringHossza, FILE* fajl);
```

Ha a visszaadott érték $NULL$, elértük a fájl végét.

Fontos megjegyezni, hogy ez *csak* a következő újsor (\n) karakterig olvas, de meg lehet oldani, hogy egy egész fájlt olvasson be egy "szimpla" algoritumussal:

```C
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    char* fajlTartalma = (char*)calloc(4096, 1); //Hosszabbnak kell lennie a fájl tartalmánál!
    char* tempPuffer = (char*)calloc(4096, 1);

    FILE* input; fopen_s(&input, "adatok.csv", "r");
    assert(input);

    while (fgets(tempPuffer, 4096, input) != NULL)
        strcat_s(fajlTartalma, 4096, tempPuffer);

    free(tempPuffer);
    fclose(input);

    // Mostantól fajlTartalma-ban van a fájl teljes tartalma, használhatjuk sima stringként
    
    //...

    free(fajlTartalma);
}
```

Itt azért calloccot használunk, mivel lehet, hogy hibásan értelmezi az üres változónkat a `strcat_s` függvény, tehát most kivételesen a malloc nem megfelelő.  
Ez egy példa a stringfüggvények, és fájlolvasás kombinálásának, de ennél szimplábban is megoldható a fájlolvasás  
  
Ehhez még 2, minimális függvényt kell tanulnunk

### **fseek**

Ezzel a függvénnyel lehet a fájl belső pozícióját (olvasási pointert/kurzort) mozgatni:

```C
fseek(FILE* fajl, size_t delta, size_t mod);
```

- $fajl$ a fájlobjektum
- $delta$ az, hogy mennyivel kell a $mód$ által definiált pozícióhoz képest mozgatni a kurzort (szinte mindig 0)
- $mod$ a speciális pozíciót definiálja, amihez képest tudjuk mozgatni a kurzort, 3 mód van:
    - SEEK_SET: fájl eleje
    - SEEK_CUR: mostani pozíció
    - SEEK_END: fájl vége

### **ftell**

Ez egy szimpla függvény, ami visszaadja a mostani kurzorpozíciót a fájlban:

```C
int ftell(FILE* fajl);
```
  
### **A legegyszerűbb stringbe olvasó algoritmus**   
```C
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    FILE* fajl; fopen_s(&fajl, "adatok.txt", "r");
    assert(fajl);

    //A fájl végére ugrás
    fseek(fajl, 0, SEEK_END);
    int fajlHossz = ftell(fajl); //Kiírja a fájl pozícióját (fájl vége = hossza)
    fseek(fajl, 0, SEEK_SET); //Vissza az elejére

    char* fajlTartalma = (char*)malloc(fajlHossz);
    int index = 0;

    // Tömbbe kiírjuk karakterenként a fájl tartalmát
    // Lehetne egyszerűbb/gyorsabb? Persze
    // Ez viszont szimpla, és bőven megfelel
    while (!feof(fajl)) {
        fajlTartalma[index] = getc(fajl);
        index++;
    }

    //...

    free(fajlTartalma);
    fclose(fajl);
}
```

### **Fájlműveletek**

- Fájl átnevezése:

```C
rename(char* reginev, char* ujnev);
```

- Fájl törlése:

```C
unlink(char* nev);
```
