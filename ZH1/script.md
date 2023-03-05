# IPA 1. zárthelyi 2023  
## Gyors bevezetés  
A C-t, mint programnyelvet azért használjuk, mivel minimális absztrakciókkal, gyorsabban lehet alacsony szintű kódot írni. Ha láttok egy sor C kódot, szinte azonnal egyértelmű, hogy mit csinál a kód, és hogyan alakítja assembly-vé, majd gépi kóddá a fordítóprogram. 
Mivel ilyen közel van a hardwarehez, ezért szinte ugyanazzal a sebességgel fut a programunk, mintha mi írtuk volna a gépi kódját, mialatt egy magasabb szintű nyelv (pl.: C#, Java, Python) nagyságrendekkel lassabb.
Egy modern gépen ez általában mindegy, de kis kapacitású hardwaren (pl.: Arduino, RPi PICO) ezek a nyelvek vagy lassan, vagy egyáltalán nem futnának el.

## Anyag összefoglalása  
Gyorsan vegyük át az anyag azon részét, amivel azok, akik más nyelvet ismerenek, már foglalkoztak, mielőtt a C alacsony szintű részéhez jutunk:  

- **Típusok:**
	- Egész típusok (integer), aminek vannak különböző méretű változatai:
		- char: 1 byte
		- short: 2 byte
		- **int**: (általában) 4 byte
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
- **Operátorok:**
	- A matematikai műveletek (+,-,*,/,()) úgy működnek, mint a matekban, beleértve a műveleti sorrendet
	- %: osztás maradéka
	- **Igazság-operátorok: && (ÉS), || (VAGY), ! (NEM)**
	- Bitenkénti operátorok: & (Bitenkénti és), | (Bitenkénti vagy), ~ (Bitenkénti komplemens), ^ (Bitenként XOR), << (Balra tolás bitenként), >> (Jobbra tolás bitenként)
- **Megjegyzés:**
	- `//` ha egysoros
	- `/*` és `*/` között akármilyen hosszú
- **Külső könyvtárak importálása**:
	- Amennyiben beépített könvtár, a `#include <név>` paranccsal lehet importálni, pl.:
		```C
		#include <stdio.h>
		```
- **Főfüggvény:**
	- int típusú, main a neve, három féle módon lehet a parétereket megadni:
		```C
		int main() {}					//Leggyakoribb iteráció
		int main(void) {}				//Ugyanaz, mint az előző
		int main(int argc, char** argv) //Ha a konzolban futási paramétereket fogad el
		```