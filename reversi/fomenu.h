#ifndef FOMENU_H_INCLUDED
#define FOMENU_H_INCLUDED

class Fomenu
{   bool running;
public:
    Fomenu() :running(true) {}

    void menuMegjelenit() const;

    void menu();

    void jatek() const;

    void szabalyok() const;

    void test() const;

    void headerRajzol() const;

};

#endif // FOMENU_H_INCLUDED
