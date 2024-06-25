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
     * Nulla, egy- vagy kétparaméteres konstruktor
     * Dinamikusan foglal memóriát!
     * @param sor - sor értékét állítja be, legalább 1 értékûnek kell lennie (alaptértelmezése 1)
     * @param oszlop - az oszlop értékét állítja be, legalább 1 értékûnek kell lennie (alapértelmezése 1)
     */
    Palya(int sor = 1, int oszlop = 1);

    /**
     * Alaphelyzetbe állítja a pályát
     * Minden mezõ/bábu értékét '.'-ra állítja
     */
    void palya_alaphelyzet();

    /**
     * Megjeleníti a pályát és a bábuk számát
     */
    void megjelenit() const;

    int getSor() const;

    int getOszlop() const;

    /**
     * Visszatérési értéke egy referencia a bábura.
     * Hibás indexelés esetén const char* kivételt dob.
     * @param row - Elérendõ sor értéke
     * @param col - Elérendõ oszlop értéke
     */
    Babu& getBabu(int row, int col);

    const Babu& getBabu(int row, int col) const;

    /**
     * Értékadó operátor
     * Törli az elõzõleg létrehozott pályát és az újat átmásolja.
     */
    Palya& operator=(const Palya& board2);

    /**
     * Felszabadítja a pályán dinamikusan foglalt memóriát
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
 * Nyomtatott ABC betûit váltja át egész számmá, ahol A-tól kezdõdik 0-val a számlálás.
 * Az oszlop mérete felsõ határa a paraméterként kapott karakternek.
 * Ha nem megfelelõ karakter inputot kapott, akkor -1 értékkel tér vissza.
 * @param ch - az átváltandó karakter
 * @param oszlop - az oszlopok mérete
 */
int atvalt(char ch, int oszlop);



#endif // PALYA_H_INCLUDED
