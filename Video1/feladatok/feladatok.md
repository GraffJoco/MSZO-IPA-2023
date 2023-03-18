# Pár tesztfeladat a gyakorláshoz
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
$$e = \lim_{n \to \infty} (1 + {1\over n})^n$$
$$ e^k = \lim_{n \to \infty} (1 + {k\over n})^n $$
(Ebben a feladatban $n \in \N^+; k \in \R$)  
Kérj be két számot a felhasználótól, és írd ki $e^k$ közelítését! Addig kérj $n$ értéket, amíg nem felel meg a szabályoknak!  
*Bónusz pontok, ha NEM használod a <math.h> könyvtárat!*  

## 4.: n-ed fokú polinóm deriválása
**FIGYELEM: ez messze a legnehezebb feladat**  
Kérj a felhasználótól egy pozitív egész számot, hogy hanyadfokú polinómot akar deriválni ($a_1x^n + a_2x^{n-1} + ... + a_n$). Hozz létre egy $n$ elemű tömböt, amibe tárolni fogod az elemeket! Utána egyesével kérd be az elemeket, és töltsd fel a tömböt (először $a_1$-et, utána $a_2$-t, stb.-t kérd ebben a sorrendben!)  
Mikor fel van töltve a tömb, írd ki `a1 * x^(n) + a2 * x^(n-1) ...` formátumbann utána külön sorban csináld ezt meg a deriválttal is!  
Ha (valahogyan) nem jut eszedbe:
$${d \over dx}a_1x^n = n*a_1x^{n-1}$$
Megjegyzések:  
- ha a kimenetben $+-$ van, az is elfogadható, m mint $-$
- furcsán kiírt, de matematikailag korrekt kifejezések (pl.:$x^0$, $x^n-0$) természetesen elfogatható
- feltételezzük, hogy jók a bemenetek, nem kell ellenőrizni, hogy $n$ pozitív-e