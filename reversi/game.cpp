#include "game.h"
#include <fstream>
#include <limits>
#include <time.h>
#include <cstdlib>

#include "memtrace.h"

void Game::initGame()
{
    palya.palya_alaphelyzet();

    if (palya_meret == 8)
    {
        palya.getBabu(3, 3).setSzin('B');
        palya.getBabu(3, 4).setSzin('W');
        palya.getBabu(4, 3).setSzin('W');
        palya.getBabu(4, 4).setSzin('B');
    }
}


void Game::lepes()
{
    bool lepett = false;
    while(!lepett && !jatek_vege)
        {
            try
            {
                int sor;
                char col;
                int oszlop;

                std::cout << "Az aktualis jatekos: " << akt_jatekos << "\n\n[sor oszlop] Kovetkezo lepes koordinatai\n" << "[0 0] Kilepes a jatekbol\n";
                std::cout << "Valasz: ";
                if ((std::cin >> sor >> col).fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    throw "Ervenytelen lepes!";
                }

                // (0 0) Megadásával ki lehet lépni a jelenlegi játékból
                if (sor == 0 && col == '0')
                {
                    kilepes();
                    return;
                }

                oszlop = atvalt(col, palya_meret);

                //Ellenõrizzük, hogy jó-e az input
                if (sor >= 0 && sor < palya_meret && oszlop >= 0 && oszlop < palya_meret && palya.getBabu(sor, oszlop).getSzin() == 'X')
                    {
                        lepett = true;
                        palya.getBabu(sor, oszlop).setSzin(akt_jatekos);

                        //Szabályos irányokban átforgatjuk a bábukat
                        atforgat(sor, oszlop);

                        //Azért itt hívjuk meg, mert csak a lépés esetén cserélünk szerepet. Ha kilépés van nem szeretnénk.
                        jatekosCsere();

                        lepett = true;

                    }
                else
                {
                    throw ("Ervenytelen lepes!");
                }

                } catch(char const* hiba){
                    std::cout << hiba << std::endl;
                }
                lepett = true;
        }
}


bool Game::validLepes()
{
    bool vanlep = false;
    int pointCnt = 0;

    //Bejárja a táblát
    for (int i = 0; i < palya_meret; i++)
    {
        for (int j = 0; j < palya_meret; j++)
        {
            bool megfelel = false;

            //Minden mezõnek megnézi van-e valid lépése
            if (palya.getBabu(i, j).getSzin() == '.')
            {
                pointCnt++;
                for (int dx = -1; dx <= 1 && !megfelel; dx++)
                {
                    for (int dy = -1; dy <= 1 && !megfelel; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;

                        else if (validIrany(i, j, dx, dy))
                        {
                            megfelel = true;
                            vanlep = true;
                            palya.getBabu(i, j).setSzin('X');
                            passz = 0;
                        }
                    }
                }
            }
        }
    }
    //Ha elfogytak a mezõk
    if (pointCnt == 0)
    {
        passz = 2;
        jatek_vege = true;
    }

    return vanlep;
}


bool Game::validIrany(int row, int col, int dx, int dy)
{
        int temp_i = row;
        int temp_j = col;

        //Addig növeljük a jelenlegi helyzetet amíg a következõ mezõ pályán beüli és ellenfél van ott.
        while (temp_j+dx < palya_meret && temp_j+dx >= 0 && temp_i+dy < palya_meret && temp_i+dy >= 0 && palya.getBabu(temp_i+dy, temp_j+dx).getSzin() == ellenfel)
            {
                temp_i += dy;
                temp_j += dx;
            }

        //Megvizsgáljuk miért állt le az elõzõ ciklus
        if (temp_j+dx < palya_meret && temp_j+dx >= 0 && temp_i+dy < palya_meret && temp_i+dy >= 0 && palya.getBabu(temp_i+dy, temp_j+dx).getSzin() == akt_jatekos && (temp_i != row || temp_j != col))
            return true;

        return false;
}


void Game::update_game()
{

    while (!jatek_vege)
    {
        //std::cout << "\033[2J\033[1;1H";
        if (!validLepes())
        {
            if (!jatek_vege)
                std::cout << "Nincs szabalyos lepes a " << akt_jatekos << " szamara.\n\n";
            passz++;
            jatekosCsere();
        }
        else
        {
            palya.megjelenit();
            if (cpu == akt_jatekos)
                gepLep();
            else
                lepes();

            validTorol();
        }
        if (passz >= 2)
        {
            jatek_vege = true;
            gameover();
        }
    }
}


void Game::kiir()
{
    palya.megjelenit();
}


void Game::atforgat(int sor, int oszlop)
{
    int row, col;
    //megnézzük mely irányokban kell átforgatni
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {

            row = sor;
            col = oszlop;

            if (!(dx == 0 && dy == 0) && validIrany(sor, oszlop, dx, dy))
            {
                //valid iranyba atforgatja az ellenfel babujait
                row += dy;
                col += dx;

                while (palya.getBabu(row, col).getSzin() != akt_jatekos)
                {
                    palya.getBabu(row, col).setSzin(akt_jatekos);
                    row += dy;
                    col += dx;
                }
            }
        }
    }
}


bool Game::jatekSave(const char* savefile) const
{

    std::ofstream Fajl(savefile);

    if (Fajl.fail())
        return false;
    Fajl << akt_jatekos << std::endl;
    Fajl << palya_meret << std::endl;
    Fajl << cpu << std::endl;
    for (int sor = 0; sor < palya_meret; sor++)
    {
        for (int oszlop = 0; oszlop < palya_meret; oszlop++)
        {
            char c = palya.getBabu(sor, oszlop).getSzin();
            if (c == '.' || c == 'X')
                Fajl << '#';
            else
                Fajl << palya.getBabu(sor, oszlop).getSzin();

            if (oszlop < palya_meret-1)
                Fajl << ',';
        }
        Fajl << '\n';
    }

    Fajl.close();
    return true;
}


bool Game::jatekLoad(const char* savefile)
{
    std::ifstream Fajl(savefile);

    if (Fajl.fail())
        return false;

    char akt_p = '0';
    int boardSize = 0;
    char gep = '.';
    char c;

    int sorCounter = 0;
    while (sorCounter != 3 && Fajl.get(c))
    {
        if (c == '\n')
            sorCounter++;

        else if (sorCounter == 0 && (c == 'B' || c == 'W'))
            akt_p = c;

        else if (sorCounter == 1 && (c >= '0' && c <= '9'))
            boardSize = 10*boardSize + c - '0';

        else if (sorCounter == 2 && (c != '.' || c != 'B' || c != 'W'))
            gep = c;
    }


    //Az eddig begyûjtött adatok alapján létrehozzuk a táblát
    palya = Palya(boardSize, boardSize);
    palya_meret = boardSize;
    akt_jatekos = akt_p;
    if (akt_jatekos == 'B')
        ellenfel = 'W';
    else
        ellenfel = 'B';
    cpu = gep;

    //Beolvassuk a mezõ értékeket
    sorCounter = 0;
    int colCounter = 0;
    while (Fajl.get(c))
    {
        if (c == ',')
            colCounter++;

        else if (c == 'W' || c == 'B')
            palya.getBabu(sorCounter, colCounter).setSzin(c);

        else if(c == '\n')
        {
            sorCounter++;
            colCounter = 0;
        }

        else if (c != '#' && c != '\r')
        {
            Fajl.close();
            return false;
        }
    }
    Fajl.close();
    return true;
}


void Game::kilepes()
{
    //Kilépés elõtt megkérdezi, hogy legyen-e mentés
    char mentes;
    jatek_vege = true;

    bool hiba = false;
    do {
        if (hiba)
        {
            std::cout << "Ervenytelen bemenetet adott meg!\n";
        }
        //Ha a ciklus még egyszer visszalépne akkor az hiba miatt történt
        hiba = true;

        std::cout << "Szeretne elmenteni a jatekot?\n"
                        << "[i/I] Igen\n"
                        << "[n/N] Nem\n"
                        << "Valasz: " ;
        std::cin >> mentes;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (mentes != 'i' && mentes != 'n' && mentes != 'I' && mentes != 'N');

    if (mentes == 'i' || mentes == 'I')
    {
        if (jatekSave("reversi_save.txt"))
            std::cout << "Sikeres mentes!" << std::endl;
        else
            std::cout << "Hiba tortent mentes soran!" << std::endl;
    }

}


void Game::gameover() const
{
    int fekete = 0;
    int feher = 0;
    char color;

    for (int row = 0; row < palya_meret; row++)
    {
        for (int col = 0; col < palya_meret; col++)
        {
            if ((color = palya.getBabu(row, col).getSzin()) == 'B')
                fekete++;
            else if(color == 'W')
                feher++;
        }
    }
    if (fekete > feher)
        std::cout << "A fekete szinu jatekos nyert!\n\n";
    else if (fekete < feher)
        std::cout << "A feher szinu jatekos nyert!\n\n";
    else
        std::cout << "Dontetlen!\n\n";

}


void Game::randomKezdet()
{
    srand(time(0));
    if (rand() % 2 == 0)
        cpu = 'B';
    else
        cpu = 'W';
}


void Game::gepLep()
{
    //Megszámolja hány lehetséges lépés létezik
    int cnt = 0;
    for (int row = 0; row < palya_meret; row++)
    {
        for (int col = 0; col < palya_meret;col++)
        {
            if (palya.getBabu(row, col).getSzin() == 'X')
                cnt++;
        }
    }

    //Generál egy véletlen számot, ezt a sorszámú lehetséges lépést lépi majd
    int lepesCnt = 0;
    lepesCnt = rand() % cnt +1;
    bool kesz = false;

    cnt = 0;

    for (int row = 0; row < palya_meret && !kesz; row++)
    {
        for (int col = 0; col < palya_meret && !kesz;col++)
        {
            if (palya.getBabu(row, col).getSzin() == 'X')
            {
                cnt++;
                if(cnt == lepesCnt)
                {
                    palya.getBabu(row, col).setSzin(akt_jatekos);

                    //valid iranyba atforgatja az ellenfel babujait
                    atforgat(row, col);

                    jatekosCsere();

                    kesz = true;
                }
            }
        }
    }
}


void Game::validTorol()
{
    for (int i = 0; i < palya_meret; i++)
    {
        for (int j = 0; j < palya_meret; j++)
        {
            Babu& babu = palya.getBabu(i, j);
            if (babu.getSzin() == 'X')
                babu.setSzin('.');
        }
    }
}


void Game::jatekosCsere()
{
    char temp = akt_jatekos;
    akt_jatekos = ellenfel;
    ellenfel = temp;
}


bool Game::gameTeszt()
{
    cpu = akt_jatekos;
    while (!jatek_vege)
    {
        //std::cout << "\033[2J\033[1;1H";
        if (!validLepes())
        {
            if (!jatek_vege)
                std::cout << "Nincs szabalyos lepes a " << akt_jatekos << " szamara.\n\n";
            passz++;
            jatekosCsere();
        }
        else
        {
            if (cpu == akt_jatekos)
                gepLep();
            else
                std::cout << "Hiba van a Teszt játékban!" << std::endl;

            validTorol();
        }
        cpu = akt_jatekos;

        if (passz >= 2)
        {
            jatek_vege = true;
            gameover();
        }

    }
    if (passz >=  2 && jatek_vege)
    {
        palya.megjelenit();
        return true;
    }

    return false;
}

