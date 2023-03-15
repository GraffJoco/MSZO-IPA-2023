# IPA 1. zárthelyi videó 2023  
## Gyors bevezetés  
A C-t, mint programnyelvet azért használjuk, mivel minimális absztrakciókkal, gyorsabban lehet alacsony szintű kódot írni. Ha láttok egy sor C kódot, szinte azonnal egyértelmű, hogy mit csinál a kód, és hogyan alakítja gépi kóddá a fordítóprogram. 
Mivel ilyen közel van a hardwarehez, ezért szinte ugyanazzal a sebességgel fut a programunk, mintha mi írtuk volna a gépi kódját, mialatt egy magasabb szintű nyelv (pl.: C#, Java, Python) nagyságrendekkel lassabb.
Egy modern gépen ez általában mindegy, de kis kapacitású hardwaren (pl.: Arduino, RPi PICO) ezek a nyelvek vagy lassan, vagy egyáltalán nem futnának el.    
**Példa: sebességek összehasonlítása a legnépszerűbb programnyelvekben**  
| Teszt neve | C / C++ | C# | Javascript | Python |
| :-: | :-: | :-: | :-: | :-: |
| [Pi számítása a Liebniz formulával](https://github.com/niklas-heer/speed-comparison) (s) | 67 | 209 | 305 | 669 |
| [50. Fibonacci szám rekurzív számítása](https://github.com/EdwardRees/Programming-Language-Speed-Comparison) (s) | 42,5 | 104 | 71 | 3434 |  
  
**Ebben a konzultációban *minimális* kódolási tudás elvárt**, tehát pl.: a változókat és függvényeket, mint fogalmat vagy nem-,  vagy csak minimálisan fogjuk elmagyarázni  
Az anyag négy részre oszklik:
- Gyors összefoglaló alapfogalmakról azoknak, akik nem tudnak programozni
- A C olyan részeinek bemutatása, ami más nyelvben is gyakori, és/vagy gyorsan megérthető
- A C nehezebb/egyedi részei (pl.: pointer, string)
- Trükkök és tippek, amik gyorsíthatnak, vagy egyszerűbbé teszik a munkát

# Alapfogalmak
- **Utasítás**: A számítógép egy feladatot (pl.: számítást csinál meg)  
	A C-ben ; kell utána:  
	```C
	A = 50;
	printf("Hello World!");
	```
- **Függvények:**
	- A matekhoz hasonlóan **paraméter**(ek) segítségével dolgozik, és (általában) egy **értéket ad** vissza
	- A függvényeket a változókhoz hasonlóan kell deklarálni (a típusok a követekző részben el lesznek magyarázva):
		```C
		típus név(típus1 paraméter1, ...) {
			//kód
		}
		```
	- A függvénynek, ha nem ad vissza értkét, **void** a típusa
	- Itt NEM lehet kezdőértéket megadni az egyes paramétereknek (C++-ban igen)
	- NEM lehet több, azonos nevű és típusú függvény, még ha mások is a paraméterei (C++-ban lehet)
	- Akárhány paraméter lehet, még 0 is
	- Ha az értéket visszaadjuk, azt a **return** kulcsszó használatával oldhatjuk meg:
		```C
		int szoroz(int a, int b) {
			return a * b;
		}
		```
- **Műveletek:**
	- A matematikai műveletek (+,-,*,/,()) úgy működnek, mint a matekban, beleértve a műveleti sorrendet
	- %: osztás maradéka
	- **Igazság-operátorok: && (ÉS), || (VAGY), ! (NEM)**
	- **Összehasonlítási művelet: == *(KETTŐ, NEM EGY EGYENLŐSÉGJEL, EZ EGY KRITIKUS HIBA!)*, <, > , <=, >=**
	- Bitenkénti operátorok: & (Bitenkénti és), | (Bitenkénti vagy), ~ (Bitenkénti komplemens), ^ (Bitenként XOR), << (Balra tolás bitenként), >> (Jobbra tolás bitenként)
	- A matematikai-, és bitműveleteknek van 
	- Módosító műveletek: az aritmetikai-, és bitoperátorok azon verziója, ami a művelet eredményét a baloldali változóban tárolja:
		```C
		a += 5; //A értékét növeljük 5-tel
		b |= 0b11011011; // Bitenkénti ÉSt futtatunk b-n és a bináris számon, a végértéket b-ben tároljuk
		```

- **Feltételek és ciklusok**:
	- **if**: ha a zárójelben lévő érték igaz (nem 0), akkor a mögötte lévő utasítást vagy kódblokkot lefuttatja:  
		```C
		if (x == 5) printf("Az x értéke 5!"); //Egy utasításos if
		```
	- **switch**: egy értéket több potenciális értékhez hasonlít, feltétel után szinte mindig break:
		```C
		switch (x) {
			case 5:
				printf("Az x tényleg 5!");
				break;
			case 4: //Mivel nincs break, a 6-os alatt lévő kód is lefut
			case 6:
				printf("Az x majdnem 5!");
				break;
			default:
				printf("Az x közel sem 5!");
		}
		```
	- **while**: olyan mint az if, de addig futtatja a mögötte lévő kódblokkot, amíg az nem lesz igaz:
		```C
		int x = 0;
		while (x != 5) {
			printf("Az x még nem 5!\n");
			x++;
		}
		printf("Az x mostmár 5!\n");
		```
	- **for**: a gyakoribb ciklus, habár a C-ben egy módosított *while*nak felel meg:  
		```C  
		for (ciklus előtt; feltétel; minden futás után) {
			//kód
		}
		```  
		Az előző példa *for*ral egyszerűbb:  
		```C
		for (int x = 0; x != 5; x++) {
			printf("Az x még nem 5!\n");
		}
		printf("Az x mostmár 5!");
		```  
- **Megjegyzés:**
	- `//` ha egysoros
	- `/*` és `*/` között akármilyen hosszú

# C-s fogalmak azoknak, akik már tudnak más nyelvet

- **Típusok:**
	- Háttér: a számítógépnek mindig tudnia kell, hogy milyen típussal dolgozik, és az mekkora (a memóriában), ezért a C, és számos más nyelv különböző funkciójú, kapacitású, és hosszú típussal dolgozik
	- Egy kisebb típus kevesebb értéket tud tárolni és pontatlanabb, de memória esetében kevesebb helyet foglal. Sebessége nagyobb típushoz képest az architektúrától függ
	- Egész típusok (integer), aminek vannak különböző méretű változatai (mindegyik $2^n$ különböző értéket tud tárolni, n a bitek, nem bytok száma):
		- char: 1 byte
		- short: 2 byte
		- **int**: *általában* 4 byte (VS-ben az, ZH-n nem kell emiatt aggódni)
		- long (int): 4 byte
		- **long long (int)**: 8 byte
		- unsigned <típus>: ugyanolyan hosszú, de csak természetes számokat tud, viszont kétszer annyit, mint előjeles változata:
			```C
			unsigned long long man = 76438932;
			```
	- Nemegész típusok, ú.n. lebegőpontos típusok, nem 100% pontosak, viszont ez a legtöbb esetben nem számít sokat:
		- float: 4 bytos
		- **double**: 8 bytos, ez az ajánlott típus
	- Tömbök és szöveg:
		- Nem valódi típusok, hanem pointerek, de megemlítendő, hogy van
		- Konstanshosszú tömböt úgy lehet deklarálni, mint más nyelvben:
			```C
			int tomb[5] = {0, 1, 2, 3, 4};
			tomb[3] = 97;
			```
		- Szöveget, ha nem módosítjuk, is használhatjuk normálisan (idézőjelben), viszont string helyett a típusa **char\***:
			```C
			char* szoveg = "Tesztszoveg";
			printf("Hello World!");
			```
	- Konstans <típus>:
		- Akármilyen típussal működik, de a deklarálásnál KÖTELEZŐ kezdőértéket adni, és utána módosíthatatlan:
			```C
			const char aBetu = 'a';
			```
- **Főfüggvény:**
	- itt kezdődik a program, ha futtatható (exe) formátummal dolgozunk, **kötelező** minden programban
	- int típusú, main a neve, három féle módon lehet a parétereket megadni:
		```C
		int main() {}						//Leggyakoribb iteráció
		int main(void) {}					//Ugyanaz, mint az előző
		int main(int argc, char** argv) {}	//Ha a konzolban futási paramétereket fogad el
		```
	- Ezek közül az első az ajánlott, de a tárgy esetében mindegy
- **Külső könyvtárak/headerek importálása**:
	- Amennyiben beépített könvtár, a `#include <név>` paranccsal lehet importálni, pl.:
		```C
		#include <stdio.h>
		```
	- Ha a headert mi csináltuk, akkor relációs jel helyett idézőjelet kell használni
		```C
		#include "tesztHeader.h"
		```
- **Fontos külső könyvtárak, és függvényeik:**
	- `stdio.h`: A felhasználóval való kommunikáció:
		- `printf(szöveg,...)`: formázott kiírás a konzolba
		- `scanf_s(forma, &változó1, ...)`: formázott beolvasás
	- `stdlib.h`: A C legfontosabb, főleg pointerekkel kapcsolatos függvényeit tartalmazza, ezért csak később fogom részletezni
	- `math.h`: Matek függvények
		- `sqrt(x)`: $\sqrt x$
		- `pow(x,y)`: $x^y$
		- szögfüggvények (`sin, cos, tan, asin`, stb.)
		- `log(x)`
		- `round(x)`: kerekít
		- `abs(x); fabs(y)`: $|x|; |y|; (x \in int, y \in double)$
# A C alacsonyabb szintű, nehezebben megérthető részei

Ez a rész jóval részletesebb lesz a többinél, nem kell aggódni.

## **STRUKTÚRÁK**
Hasonlítanak a magasabb szintű nyelvek objektumaira: egy változóba több, névvel ellátott és különböző típusú elemet lehet rakni, itt viszont nincsenek alfüggvények, konstruktorok, stb.  
Egy struktúra létrehozása a következő módon történik:
```C
struct nev {
	tipus1 elem1;
	tipus2 elem2;
	...
}; // Végére pontosvessző!
```
Mostantól kezdve ezt a típust használhatjuk, ha típusnak `struct nev`-et használunk.
Az elemekhez természetesen `nev.elem` szintakszissal lehet hozzáférni (pointer esetében máshogy, azt később említem)
Amikor létrehozzuk a változót, ha a típusokat, és sorrendjüket is tudjuk, kapcsos zárójelben meg tudjuk adni a kezdőértékeket.  
```C
struct ember {
	int kor;
	char nem;
};

struct ember Adam;
Adam.kor = 30;
Adam.nem = 'M';

struct ember Eva = {29, 'F'};
```  
Amennyiben deklaráláskor nem akarjuk kiírni mindig, hogy "struct", típust is definiálthatunk:
```C
typedef struct ember {
	int kor;
	char nem;
} ember; // Ez a második elnevezés a típus valódi neve, KÖTELEZŐ megadni!

ember Eva = {29,'F'}; // Ugyanúgy működik
```

Innentől kezdve ez a struktúra olyan, mint akármelyik másik változótípus: lehet függvényben paraméterként és return típusként használni, tömböt csinálhatunk belőle, és lehet neki pointere.  

## **POINTEREK**
Ez a C leghírhedtebb része, mert - habár szimpla fogalom - eléggé absztrakt, és magas szintű nyelvekben nem lehet/kell ezekkel foglalkozni, de ha egyszer megértitek, akkor onnantól kezdve a nyelv (és ez a tantárgy) nem lesz nehéz.  
  
A pointer valójában csak egy szám, ami megmutatja, hol az érték, amit keresel. Olyan, mint egy tartalomjegyzék egyik eleme: látod, a helyét annak, amit keresel, de maga az elem nem tárolja az adatot magában, csak megmutatja, hol van. A pointer azt is tudja, hogy milyen típus (pl.: double, int) van a helyen, ahova mutat.

**Szintaxis és szima pointerek**:  
A pointer egy bizonyos típusú értékhez mutat, ezért a deklarálásnál ezt máris jelöljuk: `típus*` egy pointer-változó típusa. A csillag kötelező, de a helye a típus és a változó neve között szabadon választható:
```C
int* inthezMutat;
double *doublehozMutat;
float * floathozMutat;
```

A pointernek kell egy érték, természetesen. Ha egy változó helyét/pointerét szeretnénk megszerezni, egyszerűen rakunk egy `&` jelet a neve elé:
```C
int ertek;
int* ertekHelye = &ertek;
```
Ezért van az, hogy amikor a `scanf_s` függvénnyel értéket olvasunk be a konzolból, `&`-t rakunk a neve elé. A függvény azt akarja tudni, hogy a beolvasott értéket *hova* rakja, ez pedig egy pointer feladata.
```C
int ertek;
int *ertekHelye = &ertek;

//A következő két sor ugyanazt csinálja:
scanf_s("%d",&ertek);
scanf_s("%d",ertekHelye);
```

Az jó, ha meg tudjuk szerezni egy változó/érték helyét, de hogy *módosítjuk* azt?  
Erre szolgál `*` (ami miatt van a deklarációban), ami a fordítottját csinálja az `&`-nek: nem azt adja meg, hogy hol az érték, hanem azt, hogy mi az érték a megadott helyen:
```C
double ertek = 67.0;
double ertekHelye = &ertek;

//A következő két sor ugyanazt csinálja:
printf("%lf\n",*ertekHelye);
printf("%lf\n",ertek);

//Nem csak az értéket, hanem JOBBÉRTÉKET kapunk vissza, ezért tudjuk azt módosítani:
*ertekHelye = 69.0;

printf("%lf\n",ertek); //69-et ír ki
```

Ennek gyakorlati haszna is van: pl.: egy függvény tudja módosítani a pointer helyén lévő értéket, és *ezért* adunk pointert a `scanf_s` függvénynek. Természetesen ilyen függvényt mi is tudunk írni:
```C
//Ez a függvény NEM ad vissza értéket, a paraméterként adott változót módosítja direkben
void duplaz(double* ertek){
	*ertek *= 2.0;
}

double teszt = 21.0;
duplaz(&teszt);
printf("%lf\n",teszt); //teszt értékét dupláztuk, 42.0-t ír ki
```

**Dinamikus tömbök**:  
Azt már mondtam, hogy egy konstans (értsd: tudjuk az értéket már a fordításkor) elemszámú tömböt tudunk létrehozni, de mi van, ha a fordítás pillanatában nem tudjuk, hogy hány elemre van szükségünk?  
Itt is pointer a megoldás, valamint a `stdlib.h` három legfontosabb függvénye: `malloc`, `calloc` és `free`
- **malloc**: megadot neki, hogy milyen hosszú (hány byte) memóriát kérsz, és egy pointert kapsz vissza, ahol ez a blokk memória kezdődik:
	```C
	int* memoria = malloc(sizeof(int)); //Kapsz sizeof(int) = VS-ben 4 byte memóriát
	*memoria = 96;
	*memoria += 2;
	// ...
	free(memoria); // EZ KÖTELEZŐ
	```
- **calloc**: malloc, de két különbséggel:
	- A memóriát lenullázza, mielőtt használod
	- Azt kéri, hogy hány elemet kérsz, és milyen hosszú egy elem (ez pont jó tömböknél, tehát ezt a függvényt ajánlom azeretben)
	```C
	//Létrehozunk egy három elemű (0-2-ig menő indexű) tömböt
	int* tombteszt = calloc(3,sizeof(int));
	tombteszt[0] = 79;
	tombteszt[2] = 28;
	tombteszt[2]++;
	tombteszt[1] = -986;

	printf("%d\n",tombteszt[2]); // 29
	
	//...
	free(tombteszt);
	```
- **free**: Akár `calloc`-kal, akár `malloc`-kar kértünk az oprendszertől memóriát, amikor abbahagytuk a használatát, fell kell szabadítanunk. Ahogy az előző példákban láthattátok, csak a pointert kell odaadni, mint paramétert a függvénynek.  
	**CSAK MALLOC ÉS CALLOC ÁLTAL SZERZET MEMÓRIÁT KELL/SZABAD FELSZABADÍTANI**

**Struktúrák pointerei**:  
Ha (pl.: egy külső könyvtár miatt) nem egy struktúrához, hanem annak a pointeréhez van hozzáférésed, hogyan tudod megszerezni/módosítani az elemeit?  
A `*`-gal lehet:
```C
ember Janos = {19, 'M'};
ember* JanosHolVan = &Janos;

*(JanosHolVan).kor++;
```
De valljuk be, ez eléggé csúnya, és nem egyértelmű, hogy mi történik. Ezért ennek az egyszerűsítésére létrehozták a `->` operátort: ugyanazt csinálja, mint a `.`, amikor egy struktúra eleméhez akarunk hozzáférni, de a struktúra helyett a struktúra pointere van előtte:
```C
JanosHolVan->kor++; //ugyanazt csinálja, de érthetőbb
```
Ebben a tárgyban ezt esély szerint nem kell majd használni, de következő félévben C++-ból igen.

# Tippek és trükkök
Ezeket nem feltétlenül kell tudni, de egyszerűbbé teheti az életed ZH-kon.  
  
**stdbool.h**:  
A C-ben nincs *alapból* boolean (igen/nem) típus, de a "modern" C-ben (C99 óta) minden fordító ismeri a `stdbool.h` nevű könyvtárat, ami pont ezt implementálja:
```C
#include <stdbool.h>
#include <stdio.h>

int main() {
	bool tesztvaltozo = true;
	printf("%d\n",tesztvaltozó); //1-et ír ki

	tesztvaltozo = false;
	printf("%d\n",tesztvaltozo); //0-t ír ki
}
```
  
*Megj.: A stdbool szerint true == 1, tehát valami == true nem mindig a valós választ adja (C-ben akármilyen nem 0 érték, pl.: 35 is igaz!), de ezt kiírni pl.: ifben eleve felesleges*

**stdint.h**:  
Elfelejtetted, hogy melyik egész típus 2 byte hosszú? Nem kell aggódni, C99 óta van stdint! Ez fordítóspecifikus makrókkal garantálja, hogy egyszerűen használj olyan hosszal rendelkező egész típusokat, amilyeneket akarsz!
```C
#include <stdint.h>
#include <stdio.h>

int main() {
	int16_t ketByteHosszu;
	uint64_t nyolcBytosElojelNelkuli;
	printf("%d, %d\n",sizeof(ketByteHosszu),sizeof(nyolcBytosElojelNelkuli)); // 2, 8
}
```

Ha tudni akarod a max/min értéket, amit egy típus tud tárolni, arra is vannak makrók!
pl.:
| név | hossz | min | max |
| --- | --- | --- | ---|
| int16_t | 16 bit / 2 byte | INT16_MIN | INT16_MAX |
| uint64_t | 64 bit / 8 byte | UINT64_MIN (előjel nélküli, tehát 0) | UINT64_MAX |  
  
**random számok használata**:  
Ha kell egy random szám, azt hogyan lehet megszerezni?  
A `stdlib.h` (amit már így is szinte biztos használsz) erre is tartalmaz egy függvényt, a `rand()`-ot.  
Ez a függvény eléggé egyszerű: 0 és `RAND_MAX` között ad vissza egy random (egész) értéket. Ebből viszont hogy csinálunk véletlenszerű számot egy random intervallumba?  
A maradék (`%`) művelet erre tökéletes:  
`rand() % valami` 0 és valami - 1 között ad vissza egy random számot.  
Ez már csak egy konstans hozzáadásával el kell tolni, és megvan az $[x; y[$ közötti random számunk!
```C
rand() % (x - y) + x
```

# Végszó
Ez (dióhélyban) az első IPA zárthelyi gyakorlati anyaga. Remélem, hogy hasznos volt, és tudtatok tanulni belőle. Sok szerencsét és sikeres zárthelyit kívánok nektek!