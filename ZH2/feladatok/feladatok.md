# Tesztfeladatok a 2. ZH túléléséhez

## Útmutató

Ezek a feladatok - az előző ZH-hoz hasonlóan - a felkészülés segítésére vannak. A nehézségi szintük változó, de többségük körülbelül olyan nehézszégű feladat, amit zárthelyin is látni lehet. Az egyes feladatok megoldása a $feladat<n>.c$ fájlban található meg.

## 1.: Leghosszabb szó egy fájlban

Olvasd be a `szoveg.txt` fájlt, és írd ki a leghosszabb szót, hosszával együtt!  
Az egyes szavakat szóköz (`' '`), új sor (`\n` és `\r`), pont vagy vessző választja el. Feltételezzük, hogy a szöveg ASCII formátumban van, tehát nem kell olyan karakterek, mint a ű jelenléte miatt aggódni.

## 2.: CSV olvasása

Kapsz egy CSV fájlt (szóközzel elválasztott elemekkel) `adatok.csv` néven.  
A fájl a következő módon van formázva:  
| Hónap | Kiadás mennyisége | Bevétel |
| --- | --- | --- |
| $szám, [1; 12]$ | Valós szám | Valós szám |

Ezek alapján számold ki:

- Az átlag profitot (Bevétel - Kiadás, adót nem számolva)
- Volt-e veszteséges hónap? (Ha igen melyikek?)
- Az összprofitot adózás (Bevétel 27%-a) után

## 3.: checksum stringre

Itt is fogunk egy "checksumot" csinálni (mint az előző konzultációban), de a bemenetünk egy string, amit konzolból olvasunk (feltételezzük, hogy a bemenet string max. 64 byte hosszú)  
A checksum algoritmus a következő:

- A kimenetünk egy 8 bites, előjel nélküli egész szám
- 2 bytonként megyünk a stringben, XOR-oljuk a 2 bytot egymással, és hozzáadjuk az összeghez
- Ha kifutottunk bytokból idő közben (nincs 2. byte, mert páratlan hosszú a string), akkor nem kell XOR-olni (kimenethez viszont hozzá kell adni)

A konzolba írjuk ki a checksum értékét!

## 4.: random tömb analizása

Kérjünk be egy $n$ pozitív egész számot a felhasználótól!  
Hozzunk létre egy $n$ darabos tömböt, amit random nemegész számokkal töltünk fel a $[0; 100]$ intervallumból
Írjuk ki az összes értéket külön sorba egy $output.txt$ nevű fájlba

A fájl végén az értékek után legyenek a következő sorok (rel. jelek között be kell helyettesíteni a korrekt értéket):

```text
Maximum ertek: <tömb maximuma>
Minimum ertek: <tömb minimuma>
Atlagertek: <tömb értékeinek átlaga>
```

## Bónusz: STL importálása

**FIGYELEM: Ez a feladat jóval magasabb szintű, mint egy ZH feladat, inkább kihívásnak szántam, mint felkészüléssegítőnek!**  

Olvassunk be egy bináris STL-t függvénnyel!  

A munkánk egyszerűsítéséhez először hozzunk létre egy 3 floatból álló $vector$ struktúrát $x, y, z$ koordinátákkal  
  
A következő módon épül fel egy STL fájl:  

- Header (80 byte): mellőzhető
- Hossz (4 byte): 32 bites egész szám, az arcok számát ($n$) tárolja
- $n$ db arc (50 byte * $n$): Ez a valódi adat, ami kell nekünk

Egy arc a következő elemeket tartalmazza:  

- normálvektor
- 3 db vektor, ami az arc 3 sarkának pontjai
- extra adatok (16 bit), mellőzhető

Csináljunk egy `STL_import` nevű függvényt, ami egy megadott helyen lévő (string paraméterű) STL fájlt olvas be, és egy arcokból álló tömböt ad vissza!  
A hosszát egy második paraméteren keresztül lehet közölni: egy `int*`, aminek értékét felülírja a függvény, beleírva az arcok számát.