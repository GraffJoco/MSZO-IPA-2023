# Pár tesztfeladat a gyakorláshoz
## Útmutató
Ezek a feladatok segítenek egyes fogalmakat begyakorolni, növekvő segítséggel.  
Ezek közül a 4. feladattól kezdve ZH szintűek vannak! 
Az egyes feladatok megoldásait a feladat\<n>.c fájlban lehet találni.
## 1.: 3n + 1
Olvass be egy (pozitív egész) számot a konzolból, és a számon futtasd le a következő algoritmust!
- Ha a szám páros, felezd
- Ha a szám páratlan, szorozd meg 3-mal, és utána adj hozzá egyet
- Addig ismétli ezeket a lépéseket, amíg a szám nem lesz egyenlő eggyel

Írj ki minden lépést, külön sorba!

## 2.: Random számok tömbje
Kérj a felhasználótól egy pozitív egész 8-bites számot (legyen ez a szám innentől $n$)!
Hozz létre egy $n$ elemű tömböt, és töltsd fel random egész 16-bites számokkal. Írd ki a tömb összes elemét egy sorban, minden szám után legyen egy pontosvessző és egy szóköz.
Utána írd ki külön-külön sorozban a következőket:
- A legnagyobb értéket a tömbben
- A legkisebb értéket a tömbben
- Az elemek átlagát

## 3.: $e$, $e^k$ közelítéses kiszámítása
Írj egy függvényt, ami egy paraméter ($n$) használatával közelíti meg $e$-t (Euler-szám) a limeszes képletet használva!  
ezesetben $ n \to \infty$ helyett $n$ egyenlő a paraméterrel  
Ebből a függvényből csinálj egy másodikat, ami $e^k$-t számolja ki!
Azoknak, akiknek nem jut eszébe:  
  
$$ e^k = \lim_{n \to \infty} (1 + {k\over n})^n $$  
  
(Ebben a feladatban $n \in \N^+; k \in \R$)  
Kérj be két számot a felhasználótól, és írd ki $e^k$ közelítését! Addig kérj $n$ értéket, amíg nem felel meg a szabályoknak!  
*Bónusz pontok, ha NEM használod a <math.h> könyvtárat!*  

## 4.: n-ed fokú polinóm deriválása 
Kérj a felhasználótól egy pozitív egész számot, hogy hanyadfokú polinómot akar deriválni ($a_1x^n + a_2x^{n-1} + ... + a_n$). Hozz létre egy $n$ elemű tömböt, amibe tárolni fogod az elemeket! Utána egyesével kérd be az elemeket, és töltsd fel a tömböt (először $a_1$-et, utána $a_2$-t, stb.-t kérd ebben a sorrendben!)  
Mikor fel van töltve a tömb, írd ki `a1 * x^(n) + a2 * x^(n-1) ...` formátumbann utána külön sorban csináld ezt meg a deriválttal is!  
Ha (valahogyan) nem jut eszedbe:  
$${d \over dx}a_1x^n = n*a_1x^{n-1}$$  
Megjegyzések:  
- ha a kimenetben $+-$ van, az is elfogadható, m mint $-$
- furcsán kiírt, de matematikailag korrekt kifejezések (pl.: $x^0$, $x^n-0$) természetesen elfogatható
- feltételezzük, hogy jók a bemenetek, nem kell ellenőrizni, hogy $n$ pozitív-e

## 5.: Checksum elkészítése
A checksum feladata egyszerű: Kapsz egy $n$ bytos adatot, és ezt egy meghatározott változóba tárolod úgy, hogy minden lehetséges módosítás változtat a checksum értékén. Most egy primitív checksumot fogunk csinálni, és $n$ formátuma és hossza kötött.  
Kérj be két számot a felhasználótól:  
- $sum$: A checksum, amihez hasonlítjuk az értéket. Ez egy egy bytos egész.  
- $x$: A szám, aminek számoljuk a checksumját. Ez pedig egy hatvannégy bites nem-egész változó.  
  
A checksum algoritmusunk a következő: Megszámoljuk, hogy $x$-ben hány 1 értékű bit található.  
Összehasonlítjuk a két checksumot:  
- Ha egyenlőek, akkor kiírjuk az egyik bináris értékét, és kiírjuk, hogy stimmelnek a checksumok
- Ha nem, akkor a következőket írjuk:  
    - $sum$ bináris értékét
    - A mi checksumunk bináris értékét
    - Egy kevert reprezentációt: Ha a bit azonos mindkettőnél, kiírjuk a bit értékét, ha nem, akkor egy 'x'-et

Tipp: tudsz egybytos egésztömböt csinálni $x$-ből a következő módon:  
```C
egy_bytos_egesz* egeszTomb = (egy_bytos_egesz*) &x;
```
Mivel $x$ hatvannégy bites, `egeszTomb`-et is olyan hosszú változóként kell kezelni!

## 6.: Vektorok
**FONTOS MEGJEGYZÉS**: A függvények (és ez a feladat) nem mindegyik csoport ZH anyagának része!  
Hozz létre egy három double ($x$, $y$, $z$) elemű `vektor` struktúrát.
Implementáld a következő függvényeket:  
$$plus(\underline{v_1}, \underline{v_2}) \to \underline{v_1} + \underline{v_2}$$
Ezt csináld meg kivonással `minus` néven is, valamint csinálj egy `scale` skalárral szoró, egy `cross` vektoriális szorzással (Ezek mind vektorokból és doubleből csinálnak vektort)!  
Csinálj még egy `scalar` skalárszorzó és egy `length` függvényt is, ami double-t ad vissza!  
Csinálj egy kiíró függvéynt is, ami egy vektort kiír $\{v_x; v_y; v_z\}$ formátumban!  
Utána csinálj egy egyszerű vektoros számológépet!  
- Kérj két vektorhoz értékeket ($x_1, y_1, z_1, x_2, y_2, z_2$), amiket vektorokként fogsz kezelni ( $v_1, v_2$)!  
- Kérj egy karaktert, hogy mit fogsz velük csinálni:
    - '+': összeadod őket
    - '-': kivonod őket
    - '*': skaláris szorzatot számolsz
    - 'x': vektoriális szorzatot számolsz
    - 's': kérsz egy double-t, $v_1$-et skalárral szorzod vele
    - 'l': kiírod $v_1$ hosszát
