#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include "palya.h"
#include <time.h>
#include <cstdlib>

class Game
{

    Palya palya;
    char akt_jatekos;
    char ellenfel;
    int palya_meret;
    bool jatek_vege;
    int passz;
    char cpu;

public:

    /**
     * Nulla-, egy- vagy két paraméteres konstruktor
     * Új játék kezdésénél beállítja az adattagok alapértelmezett értékét.
     * Amennyiben a cpu nem semleges karakter, úgy a cpu ellenfél létrehozás irányába tereli a programot.
     * @param boardsize - megadható vele a létrehozandó pálya méretét
     * @param gep - beállítja a cpu ellenfél karakterét (alapértelmezetten '.')
     */
    Game(int boardSize = 8, char gep = '.') :palya(Palya(boardSize, boardSize)), akt_jatekos('B'), ellenfel('W'), palya_meret(boardSize), jatek_vege(false), passz(0), cpu(gep) {
        initGame();
        if(cpu != '.')
            randomKezdet();
    }

    /**
     * Háromparaméteres konstrukor
     * A pálya létrehozása mellett beállítja a cpu és a kezdõ játékos karakterét.
     * A fájlból beolvasásnál fontos, amikor nem mindegy ki folytatja a játékot.
     * @param boardsize - pálya mérete
     * @param aktplayer - aktuális játékos beállítása
     * @param gep - beállítja a cpu karakterét (alapértelmezett '.' = nincs cpu)
     */
    Game(int boardSize, char gep, char aktplayer) :palya(Palya(boardSize, boardSize)), palya_meret(boardSize), jatek_vege(false), passz(0), cpu(gep) {
        akt_jatekos = aktplayer;
        if (aktplayer == 'B')
            ellenfel = 'W';
        else
            ellenfel = 'B';
    }

    /**
     * Ha a reversi játéknak megfelelõ a pálya mérete, akkor beállítja a pályán a kezdõ bábukat
     */
    void initGame();


    /**
     * Bekéri a következõ lépés koordinátáit, vagy a kilépéshez a 0 0-t
     * Ellenõrzi a bemenetet.
     * Kilépés esetén rákérdez a mentésre.
     * Szabályos lépés esetén átforgatja a bábukat.
     */
    void lepes();


    /**
     * Bejárja a táblát és az aktuális játékosnak megfelelõen megkeresi a szabályos lépéseket.
     * A szabályos lépés helyein a bábut 'X'-re állítja.
     * Visszatérési értéke jelzi, hogy van-e valid lépés
     */
    bool validLepes();

    /**
     * Ellenõrzi, hogy a kiindulási sor és oszlop értéktõl kezdve egy dx és dy irányba haladva szabályos lépést kielégítõ feltételek vannak-e
     * @param row - kezdeti sor érték
     * @param col - kezdeti oszlop érték
     * @param dx - x-tengely mentén (oszlopot értéket) változtat
     * @param dy - y-tengely mentén (sor értéket) változtat
     */
    bool validIrany(int row, int col, int dx, int dy);

    /**
     * Futtatja a játék függvényeit, amíg a játéknak nincs vége, vagy nem lép ki a játékos
     */
    void update_game();

    /**
     * Megjeleníti a pályát
     */
    void kiir();

    /**
     * Egy adott pozícióból ellenõrzi, hogy milyen irányban lehet átforgatni a bábukat.
     * A szabályos irányokban átforgatja a bábukat.
     * @param row - kiindulási sor
     * @param col - kiindulási oszlop
     */
    void atforgat(int row, int col);


    /**
     * Elmenti az aktuális pályát és állást.
     */
    bool jatekSave(const char* savefile) const;


    /**
     * Beolvassa egy jatek allasat.
     */
    bool jatekLoad(const char* savefile);


     /**
     * A játékból való kilépés esetén megkérdezi a játékost, hogy szeretné-e menteni a játékot.
     */
    void kilepes();


    /**
     * Megszámolja az azonos színû bábukat, és kiírja a játék eredményét.
     */
    void gameover() const;

    /**
     * Gép elleni játék esetén a rand függvény segítségével beállít egy random értéket a cpu-nak
     */
    void randomKezdet();

    /**
     * CPU ellenfél lépését irányító függvény.
     */
    void gepLep();


    /**
     * Az X-el jelölt szabályos lépés helyeket visszaállítja '.' mezõre.
     */
    void validTorol();

    /**
     * Az aktuális és az ellenfél játékos szerepét felcseréli
     */
    void jatekosCsere();


    bool gameTeszt();

};


#endif // GAME_H_INCLUDED
