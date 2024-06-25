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
     * Nulla-, egy- vagy k�t param�teres konstruktor
     * �j j�t�k kezd�s�n�l be�ll�tja az adattagok alap�rtelmezett �rt�k�t.
     * Amennyiben a cpu nem semleges karakter, �gy a cpu ellenf�l l�trehoz�s ir�ny�ba tereli a programot.
     * @param boardsize - megadhat� vele a l�trehozand� p�lya m�ret�t
     * @param gep - be�ll�tja a cpu ellenf�l karakter�t (alap�rtelmezetten '.')
     */
    Game(int boardSize = 8, char gep = '.') :palya(Palya(boardSize, boardSize)), akt_jatekos('B'), ellenfel('W'), palya_meret(boardSize), jatek_vege(false), passz(0), cpu(gep) {
        initGame();
        if(cpu != '.')
            randomKezdet();
    }

    /**
     * H�romparam�teres konstrukor
     * A p�lya l�trehoz�sa mellett be�ll�tja a cpu �s a kezd� j�t�kos karakter�t.
     * A f�jlb�l beolvas�sn�l fontos, amikor nem mindegy ki folytatja a j�t�kot.
     * @param boardsize - p�lya m�rete
     * @param aktplayer - aktu�lis j�t�kos be�ll�t�sa
     * @param gep - be�ll�tja a cpu karakter�t (alap�rtelmezett '.' = nincs cpu)
     */
    Game(int boardSize, char gep, char aktplayer) :palya(Palya(boardSize, boardSize)), palya_meret(boardSize), jatek_vege(false), passz(0), cpu(gep) {
        akt_jatekos = aktplayer;
        if (aktplayer == 'B')
            ellenfel = 'W';
        else
            ellenfel = 'B';
    }

    /**
     * Ha a reversi j�t�knak megfelel� a p�lya m�rete, akkor be�ll�tja a p�ly�n a kezd� b�bukat
     */
    void initGame();


    /**
     * Bek�ri a k�vetkez� l�p�s koordin�t�it, vagy a kil�p�shez a 0 0-t
     * Ellen�rzi a bemenetet.
     * Kil�p�s eset�n r�k�rdez a ment�sre.
     * Szab�lyos l�p�s eset�n �tforgatja a b�bukat.
     */
    void lepes();


    /**
     * Bej�rja a t�bl�t �s az aktu�lis j�t�kosnak megfelel�en megkeresi a szab�lyos l�p�seket.
     * A szab�lyos l�p�s helyein a b�but 'X'-re �ll�tja.
     * Visszat�r�si �rt�ke jelzi, hogy van-e valid l�p�s
     */
    bool validLepes();

    /**
     * Ellen�rzi, hogy a kiindul�si sor �s oszlop �rt�kt�l kezdve egy dx �s dy ir�nyba haladva szab�lyos l�p�st kiel�g�t� felt�telek vannak-e
     * @param row - kezdeti sor �rt�k
     * @param col - kezdeti oszlop �rt�k
     * @param dx - x-tengely ment�n (oszlopot �rt�ket) v�ltoztat
     * @param dy - y-tengely ment�n (sor �rt�ket) v�ltoztat
     */
    bool validIrany(int row, int col, int dx, int dy);

    /**
     * Futtatja a j�t�k f�ggv�nyeit, am�g a j�t�knak nincs v�ge, vagy nem l�p ki a j�t�kos
     */
    void update_game();

    /**
     * Megjelen�ti a p�ly�t
     */
    void kiir();

    /**
     * Egy adott poz�ci�b�l ellen�rzi, hogy milyen ir�nyban lehet �tforgatni a b�bukat.
     * A szab�lyos ir�nyokban �tforgatja a b�bukat.
     * @param row - kiindul�si sor
     * @param col - kiindul�si oszlop
     */
    void atforgat(int row, int col);


    /**
     * Elmenti az aktu�lis p�ly�t �s �ll�st.
     */
    bool jatekSave(const char* savefile) const;


    /**
     * Beolvassa egy jatek allasat.
     */
    bool jatekLoad(const char* savefile);


     /**
     * A j�t�kb�l val� kil�p�s eset�n megk�rdezi a j�t�kost, hogy szeretn�-e menteni a j�t�kot.
     */
    void kilepes();


    /**
     * Megsz�molja az azonos sz�n� b�bukat, �s ki�rja a j�t�k eredm�ny�t.
     */
    void gameover() const;

    /**
     * G�p elleni j�t�k eset�n a rand f�ggv�ny seg�ts�g�vel be�ll�t egy random �rt�ket a cpu-nak
     */
    void randomKezdet();

    /**
     * CPU ellenf�l l�p�s�t ir�ny�t� f�ggv�ny.
     */
    void gepLep();


    /**
     * Az X-el jel�lt szab�lyos l�p�s helyeket vissza�ll�tja '.' mez�re.
     */
    void validTorol();

    /**
     * Az aktu�lis �s az ellenf�l j�t�kos szerep�t felcser�li
     */
    void jatekosCsere();


    bool gameTeszt();

};


#endif // GAME_H_INCLUDED
