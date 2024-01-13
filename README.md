# Gazdálkodj Okosan bankszámla kezelő program
Ez a program a magyarországon kapható *Gazdálkodj okosan!* című társasjátékhoz készült, a játék részét képző bankszámla kezelésének megkönnyítésére.
## Telepítés
A telepítéshez először be kell fordítani a kódot, ehhez szükség van a Qt5 fejlesztő fájlokra, C++ fordítóra, valamint GNU make szoftverre. Az első lépés a Makefile elkészítése a qmake segítségével:
```
qmake robi-gui.pro
```
Ezt követően a program elkészíthető a qmake által készült Makefile-on keresztül:
```
make -j
```
Ha a fordítás sikeresen befejeződött a *robi-gui* nevű futtatható állomány indításával a program már használható is!
