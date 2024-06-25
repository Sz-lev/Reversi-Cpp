#ifndef BABU_H_INCLUDED
#define BABU_H_INCLUDED

class Babu
{
    char szin;

public:

    /**
     * Egy vagy nulla paraméteres konstruktor
     * Beállítja a bábu színét
     * @param color - bábu színe (alapértelmezése '.')
     */
    Babu(char color = '.');

    /**
     * Visszatérési értéke a bábu színe char
     */
    char getSzin() const;


    /**
     * Módosítja a bábu színét
     * @param color - beállítandó szín
     */
    void setSzin(char color);

};
#endif // BABU_H_INCLUDED
