#ifndef PALYA_H_INCLUDED
#define PALYA_H_INCLUDED

#include <iostream>
#include "babu.h"


class Palya
{
    Babu** board;
    int sor, oszlop;

public:

    /**
     * Nulla, egy- vagy k�tparam�teres konstruktor
     * Dinamikusan foglal mem�ri�t!
     * @param sor - sor �rt�k�t �ll�tja be, legal�bb 1 �rt�k�nek kell lennie (alapt�rtelmez�se 1)
     * @param oszlop - az oszlop �rt�k�t �ll�tja be, legal�bb 1 �rt�k�nek kell lennie (alap�rtelmez�se 1)
     */
    Palya(int sor = 1, int oszlop = 1);

    /**
     * Alaphelyzetbe �ll�tja a p�ly�t
     * Minden mez�/b�bu �rt�k�t '.'-ra �ll�tja
     */
    void palya_alaphelyzet();

    /**
     * Megjelen�ti a p�ly�t �s a b�buk sz�m�t
     */
    void megjelenit() const;

    int getSor() const;

    int getOszlop() const;

    /**
     * Visszat�r�si �rt�ke egy referencia a b�bura.
     * Hib�s indexel�s eset�n const char* kiv�telt dob.
     * @param row - El�rend� sor �rt�ke
     * @param col - El�rend� oszlop �rt�ke
     */
    Babu& getBabu(int row, int col);

    const Babu& getBabu(int row, int col) const;

    /**
     * �rt�kad� oper�tor
     * T�rli az el�z�leg l�trehozott p�ly�t �s az �jat �tm�solja.
     */
    Palya& operator=(const Palya& board2);

    /**
     * Felszabad�tja a p�ly�n dinamikusan foglalt mem�ri�t
     */
    ~Palya()
    {
        for (int i = 0; i < sor; i++)
        {
            delete[] board[i];
        }
        delete[]board;
    }
};

/**
 * Nyomtatott ABC bet�it v�ltja �t eg�sz sz�mm�, ahol A-t�l kezd�dik 0-val a sz�ml�l�s.
 * Az oszlop m�rete fels� hat�ra a param�terk�nt kapott karakternek.
 * Ha nem megfelel� karakter inputot kapott, akkor -1 �rt�kkel t�r vissza.
 * @param ch - az �tv�ltand� karakter
 * @param oszlop - az oszlopok m�rete
 */
int atvalt(char ch, int oszlop);



#endif // PALYA_H_INCLUDED
