#include <iostream>
#include "game.h"
#include "fomenu.h"
#include "gtest_lite.h"

#include "memtrace.h"


#ifndef TESZT
#define TESZT 1
#endif // TESZT

void Fomenu::menuMegjelenit() const
{
    std::cout << "[1] Jatek\n"
    << "[2] Szabalyok\n"
    << "[3] Teszt\n"
    << "[4] Kilepes\n" << std::endl;
}

void Fomenu::menu()
{
    int sel = 0;

    while (running)
    {

        #if TESZT >= 1
        switch(sel)
        {
        case 0:
            sel = 3;
            break;
        case 3:
            sel = 4;
            break;
        }
        #endif // TESZT

            try
            {

                headerRajzol();
                menuMegjelenit();
                #if TESZT < 1
                std::cout << "Kerem valasszon a menupontok kozul: ";
                std::cin >> sel;
                if (sel < 1 || sel > 4)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw "Ervenytelen erteket adott meg!";
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                #endif // TESZT

                switch (sel)
                {
                case 1:
                    jatek();
                    break;
                case 2:
                    szabalyok();
                    break;
                case 3:
                    test();
                    break;
                case 4:
                    running = false;
                    break;
                }

            } catch (const char* p) {
                std::cout << p << std::endl;
                }
    }
    std::cout << "Sikeresen kilepett." << std::endl;
    #if TESZT >= 1
        std::cout << "Ha nem szeretne, hogy csak a teszt fusson le, ugy allitsa a TESZT makrot 0-ra a fomenu.cpp fajlban.";
    #endif // TESZT


}

void Fomenu::jatek() const
{
    int jatekmod = 0;
    char valasz = 'n';
    #if TESZT < 1
    bool hiba = false;
    do
    {
        if (hiba)
            std::cout << "Ervenytelen karaktert adott meg!\n";
        std::cout << "Szeretne folytatni az elozo mentest?\n"
                        << "[i/I] Igen\n"
                        << "[n/N] Nem\n"
                        << "valasz: ";
        std::cin >> valasz;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        hiba = true;

    } while (valasz != 'i' && valasz != 'n' && valasz != 'N' && valasz != 'I');
    #endif // TESZ
    if (valasz == 'i' || valasz == 'I')
    {
        Game game;
        game.jatekLoad("reversi_save.txt");
        game.update_game();

    }

    else if (valasz == 'n' || valasz == 'N')
    {

        #if TESZT < 1
        hiba = false;
        do
        {
            if (hiba)
                std::cout << "Ervenytelen karaktert adott meg!\n";
            std::cout << "Kerem valasszon a jatekmodok kozul:\n"
                      << "[1] Jatekos vs. Jatekos\n"
                      << "[2] Jatekos vs. CPU\n"
                      << "Valasz: ";
            std::cin >> jatekmod;
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            hiba = true;

        } while (jatekmod != 1 && jatekmod != 2);
        #endif // TESZT

        if (jatekmod == 1)
        {
            Game game;
            game.update_game();
        }

        else
        {
            Game game(8, 'X');
            game.update_game();
        }
    }
}

void Fomenu::szabalyok() const
{
    std::cout << "A reversi jatekot egy 8x8 tablan szokas jatszani, ket kulonbozo szinu koronggal.\n"
    << "A jatek kezdeten a tabla kozepso 2x2 negyzetebe kerul jatekosonkent 2 korong ugy,\n "
    << "hogy az egyszinuek atlosan helyezkedjenek el.\n"
    << "A kovetkezo jatekos akkor helyezhet el korongot, ha az uj korong es egy mar ott levo (sajat szinu) korong"
    << "kozrefogja az ellenfelnek legalabb egy vonalat, vagyis sorat, vagy oszlopat.\n"
    << "Ha letette a jatekos a korongot akkor az osszes ilyen vonalat at kell forgatni.\n"
    << "Ha van szabalyos lepes, akkor kotelezo tenni, passzolni nem szabad.\n"
    << "Ha azonban nincs lehetoseg szabalyosan lepni, akkor passzolni kell.\n"
    << "A jateknak akkor van vege, ha egyik felnek sincs szabalyos lepese, ilyenkor az gyoz, akinek tobb korongja van.\n"
    << "Dontetlen kimenetel is lehetseges.\n\n";

    std::cout << "A visszalepeshez kerem usson egy entert." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Fomenu::test() const
{
    GTINIT(std::cin);


    TEST(Teszt1, Babu) {
        Babu piece1;
        EXPECT_EQ('.',piece1.getSzin());
        piece1.setSzin('W');
        EXPECT_EQ('W', piece1.getSzin());

        Babu piece2('B');
        EXPECT_EQ('B', piece2.getSzin());
        piece2.setSzin('W');
        EXPECT_EQ('W', piece2.getSzin());
    } END

    TEST(Teszt2, Palya)
    {
        Palya board;
        EXPECT_EQ(1, board.getSor());
        EXPECT_EQ(1, board.getOszlop());
        EXPECT_EQ('.', board.getBabu(0, 0).getSzin());
        board.getBabu(0, 0).setSzin('W');
        EXPECT_EQ('W', board.getBabu(0, 0).getSzin());
        board.palya_alaphelyzet();
        EXPECT_EQ('.', board.getBabu(0, 0).getSzin());

        Palya board2(4, 6);
        EXPECT_EQ(4, board2.getSor());
        EXPECT_EQ(6, board2.getOszlop());
        EXPECT_EQ('.', board2.getBabu(3, 5).getSzin());
        board2.getBabu(3, 5).setSzin('B');
        EXPECT_EQ('B', board2.getBabu(3, 5).getSzin());
        board2.palya_alaphelyzet();
        EXPECT_EQ('.', board2.getBabu(3, 5).getSzin());

        Palya board3(8, 8);
        Palya board4(2, 2);
        board4 = board3;
        EXPECT_EQ(8, board4.getSor());
        EXPECT_EQ(8, board4.getOszlop());
    }END

    TEST(Teszt3, Game)
    {
        Game game(8);
        EXPECT_TRUE(game.jatekSave("test.txt"));
        EXPECT_TRUE(game.jatekLoad("test.txt"));

        Game game2(4);
        EXPECT_TRUE(game2.jatekLoad("test2.txt"));
        EXPECT_TRUE(game2.validIrany(2, 6, -1, 0));
        game2.atforgat(2, 6);
        EXPECT_FALSE(game2.validIrany(2, 6, -1, 0));
        EXPECT_TRUE(game2.validLepes());

        Game game3(8, 'X');
        EXPECT_TRUE(game3.gameTeszt());

    }END

}

void Fomenu::headerRajzol() const
{
    std::cout << "BBB BBB BBB   WWW WWW WWW   BBB       BBB   WWW WWW WWW   BBB BBB BBB   WWW WWW WWW   BBB\n"
                   << " BBB     BBB   WWW           BBB      BBB    WWW           BBB     BBB   WWW           BBB\n"
                   << "  BBB BBB BBB   WWW WWW WWW    BBB     BB     WWW WWW WWW   BBB BBB BBB   WWW WWW WW    BBB\n"
                   << "   BBB   BBB     WWW WWW WWW    BBB    BB      WWW WWW WWW   BBB   BBB            WWW    BBB\n"
                   << "    BBB    BBB    WWW             BBB  BB       WWW           BBB    BBB   WW      WWW    BBB\n"
                   << "     BBB    BBB    WWW WWW WWW      BBB          WWW WWW WWW    BBB    BBB  WWW WWW WWW    BBB\n\n\n";
}

