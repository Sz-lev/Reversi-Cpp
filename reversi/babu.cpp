#include "babu.h"

Babu::Babu(char color) :szin(color) {}

char Babu::getSzin() const
{
    return szin;
}

void Babu::setSzin(char color)
{
    szin = color;
}
