# IPA 1. zárthelyi 2023  
## Gyors bevezetés  
A C-t, mint programnyelvet azért használjuk, mivel minimális absztrakciókkal, gyorsabban lehet alacsony szintű kódot írni. Ha láttok egy sor C kódot, szinte azonnal egyértelmű, hogy mit csinál a kód, és hogyan alakítja assembly-vé, majd gépi kóddá a fordítóprogram. 
Mivel ilyen közel van a hardwarehez, ezért szinte ugyanazzal a sebességgel fut a programunk, mintha mi írtuk volna a gépi kódját, mialatt egy magasabb szintű nyelv (pl.: C#, Java, Python) nagyságrendekkel lassabb.
Egy modern gépen ez általában mindegy, de kis kapacitású hardwaren (pl.: Arduino, RPi PICO) ezek a nyelvek vagy lassan, vagy egyáltalán nem futnának el.  
**Ebben a konzultációban *minimális* kódolási tudás elvárt**, tehát pl.: a változókat és függvényeket, mint fogalmat vagy nem-,  vagy csak minimálisan fogjuk elmagyarázni
Az anyag három részre oszklik:
- A C olyan részeinek bemutatása, ami más nyelvben is gyakori, és/vagy gyorsan megérthető
- A C nehezebb/egyedi részei (pl.: pointer, string)
- Trükkök és tippek, amik gyorsíthatnak, vagy egyszerűbbé teszik a munkát

## Anyag összefoglalása  
Gyorsan vegyük át az anyag azon részét, amivel azok, akik más nyelvet ismerenek, már foglalkoztak, mielőtt a C alacsony szintű részéhez jutunk:  

- **Típusok:**
	- Háttér: a számítógépnek mindig tudnia kell, hogy milyen típussal dolgozik, és az mekkora (a memóriában), ezért a C, és számos más nyelv különböző funkciójú, kapacitású, és hosszú típussal dolgozik
	- Egész típusok (integer), aminek vannak különböző méretű változatai:
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
		- Szöveget, ha nem módosítjuk, is használhatjuk normálisan:
			```C
			printf("Hello World!");
			```
	- Konstans <típus>:
		- Akármilyen típussal működik, de a deklarálásnál KÖTELEZŐ kezdőértéket adni, és utána módosíthatatlan:
			```C
			const char aBetu = 'a';
			```
- **Függvények:**
	- A függvényeket a változókhoz hasonlóan kell deklarálni:
		```C
		típus név(típus1 paraméter1, ...) {
			//kód
		}
		```
	- A függvénynek, ha nem ad vissza értkét, **void** a típusa
	- Itt NEM lehet kezdőértéket megadni az egyes paramétereknek (C++-ban igen)
	- NEM lehet több, azonos nevű és típusú függvény, még ha mások is a paraméterei (C++-ban lehet)
	- Ha az értéket visszaadjuk, azt a return kulcsszó használatával oldhatjuk meg:
		```C
		int szoroz(int a, int b) {
			return a * b;
		}
		```
- **Műveletek:**
	- A matematikai műveletek (+,-,*,/,()) úgy működnek, mint a matekban, beleértve a műveleti sorrendet
	- %: osztás maradéka
	- **Igazság-operátorok: && (ÉS), || (VAGY), ! (NEM)**
	- Bitenkénti operátorok: & (Bitenkénti és), | (Bitenkénti vagy), ~ (Bitenkénti komplemens), ^ (Bitenként XOR), << (Balra tolás bitenként), >> (Jobbra tolás bitenként)
	- A matematikai-, és bitműveleteknek van 
	- Módosító műveletek: az aritmetikai-, és bitoperátorok azon verziója, ami a művelet eredményét a baloldali változóban tárolja:
		```C
		a += 5; //A értékét növeljük 5-tel
		b |= 0b11011011; // Bitenkénti ÉSt futtatunk b-n és a bináris számon, a végértéket b-ben tároljuk
		```
- **Megjegyzés:**
	- `//` ha egysoros
	- `/*` és `*/` között akármilyen hosszú
- **Főfüggvény:**
	- int típusú, main a neve, három féle módon lehet a parétereket megadni:
		```C
		int main() {}						//Leggyakoribb iteráció
		int main(void) {}					//Ugyanaz, mint az előző
		int main(int argc, char** argv) {}	//Ha a konzolban futási paramétereket fogad el
		```
	- Ezek közül az első az ajánlott, de a tárgy esetében mindegy
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
- **Külső könyvtárak importálása**:
	- Amennyiben beépített könvtár, a `#include <név>` paranccsal lehet importálni, pl.:
		```C
		#include <stdio.h>
		```
- **Fontos külső könyvtárak, és függvényeik:**
	- `stdio.h`: A felhasználóval való kommunikáció:
		- `printf(szöveg,...)`: formázott kiírás a konzolba
		- `scanf_s(forma, &változó1, ...)`: formázozz beolvasás
	- `stdlib.h`: A C legfontosabb, főleg pointerekkel kapcsolatos függvényeit tartalmazza, ezért csak később fogom részletezni
	- `math.h`: Matek függvények
		- `sqrt(x)`: $\sqrt x$
		- `pow(x,y)`: $x^y$
		- szögfüggvények (`sin, cos, tan, asin`, stb.)
		- `log(x)`
		- `round(x)`: kerekít
		- `abs(x); fabs(y)`: $|x|; |y|; (x \in int, y \in double)$