#ifndef BABU_H_INCLUDED
#define BABU_H_INCLUDED

class Babu
{
    char szin;

public:

    /**
     * Egy vagy nulla param�teres konstruktor
     * Be�ll�tja a b�bu sz�n�t
     * @param color - b�bu sz�ne (alap�rtelmez�se '.')
     */
    Babu(char color = '.');

    /**
     * Visszat�r�si �rt�ke a b�bu sz�ne char
     */
    char getSzin() const;


    /**
     * M�dos�tja a b�bu sz�n�t
     * @param color - be�ll�tand� sz�n
     */
    void setSzin(char color);

};
#endif // BABU_H_INCLUDED
