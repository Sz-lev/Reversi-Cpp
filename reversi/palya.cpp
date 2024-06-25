    #include "palya.h"

    #include "memtrace.h"

    Palya::Palya(int sor, int oszlop) :sor(sor), oszlop(oszlop)
    {
        board = new Babu*[sor];

        for (int i = 0; i < sor; i++)
        {
            board[i] = new Babu[oszlop];
        }

        palya_alaphelyzet();
    }


    void Palya::palya_alaphelyzet()
    {
        for (int i = 0; i < sor; i++)
        {
            for (int j = 0; j < oszlop; j++)
            {
                board[i][j].setSzin('.');
            }
        }
    }


    void Palya::megjelenit() const
    {
        int feher = 0;
        int fekete = 0;

        std::cout << " ";
        for (int i = 0; i < oszlop; i++)
        {
            char ch = 'A' + i;
            std::cout << " " << ch;
        }
        std::cout << std::endl;
        for (int i = 0; i < sor; i++)
        {
            std::cout << i;
            for (int j = 0; j < oszlop; j++)
            {
                char szin = board[i][j].getSzin();
                std::cout << " " << szin;
                if (szin == 'W')
                    feher++;
                else if (szin == 'B')
                    fekete++;
            }
            std::cout << std::endl;
        }
        std::cout << "\nfekete babu: " << fekete << std::endl;
        std::cout << "feher babu: " << feher << "\n\n";
    }


    Babu& Palya::getBabu(int row, int col)
    {
        if (row < sor && col < oszlop)
            return board[row][col];
        throw "Helytelen mezo indexeles";
    }


    const Babu& Palya::getBabu(int row, int col) const
    {
        if (row < sor && col < oszlop)
            return board[row][col];
        throw "Helytelen mezo indexeles";
    }


    int Palya::getSor() const
    {
        return sor;
    }


    int Palya::getOszlop() const
    {
        return oszlop;
    }


    Palya& Palya::operator=(const Palya& board2)
    {
        for (int i = 0; i < sor; i++)
        {
            delete[] board[i];
        }
        delete[]board;

        sor = board2.getSor();
        oszlop = board2.getOszlop();

        //Az új pálya létrehozása
        board = new Babu*[sor];

        for (int i = 0; i < sor; i++)
        {
            board[i] = new Babu[oszlop];
        }

        //Értékek átmásolása az új pályába
        for (int row = 0; row < sor; row++)
        {
            for (int col = 0; col < oszlop; col++)
            {
                getBabu(row, col) = board2.getBabu(row, col);
            }
        }

        return *this;
    }


    int atvalt(char ch, int oszlop)
    {
        int col = ch - 'A';
        if (col < oszlop && col >= 0)
        {
            return col;
        }
        return -1;
    }

