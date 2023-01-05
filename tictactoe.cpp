// tictactoe.cpp
#include <iostream>

using namespace std;

const int didFindWinner = 1;

class Player
{
private:
    string m_userName;

public:
    Player(string name)
    {
        m_userName = name;
    }

    string getUsername()
    {
        return m_userName;
    }
};

class Board
{
private:
    int m_numOfProcess;
    int m_board[3][3];

public:
    Board()
    {
        doInitialize();
    }
    ~Board()
    {
    }

    void doInitialize()
    {
        m_numOfProcess = 0;

        // initialize square
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                m_board[i][j] = 0;
            }
        }
    }

    char convertNumberToOX(int input)
    {
        if (input == 1)
            return 'O';
        else if (input == -1)
            return 'X';
        else if (input == 0)
            return ' ';
        else
        {
            cout << "Invalid format to convert" << endl;
            return 'N';
        }
    }

    void showCurrentBoard()
    {
        for (int i = 0; i < 5; i++)
        {
            if (i % 2 == 0)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (j % 2 == 1)
                    {
                        cout << "|\t";
                    }
                    else
                    {
                        cout << " " << convertNumberToOX(m_board[i / 2][j / 2]) << "\t";
                    }
                }
                cout << endl;
            }
            else
            {
                for (int j = 0; j < 5; j++)
                    cout << "-\t";
                cout << endl;
            }
        }
    }

    // return didFindWinner: game is finished
    // return 0: keep playing
    // return -1: try again
    // return -2: Unable to play anymore
    int updateBoard(int x, int y)
    {
        if (x < 0 || x >= 3 || y < 0 || y >= 3)
        {
            cout << "Out of index on the board. index: " << x << " " << y << endl;
            cout << "Please try again" << endl;
            return -1;
        }

        if (m_board[x][y] == 1 || m_board[x][y] == -1)
        {
            cout << "Unable to draw on " << x << " " << y << endl;
            cout << "Please try again" << endl;
            return -1;
        }

        if (m_numOfProcess > 9)
        {
            cout << "Unable to play anymore" << endl;
            return -2;
        }

        if (m_numOfProcess % 2 == 0)
            m_board[x][y] = 1;
        else
            m_board[x][y] = -1;

        if (didWin() == didFindWinner)
            return didFindWinner;

        m_numOfProcess++;
        return 0;
    }

    // return 1: win
    // return 0: keep playing
    int didWin()
    {
        for (int i = 0; i < 3; i++)
        {
            if (m_board[i][0] != 0 && m_board[i][0] == m_board[i][1] && m_board[i][1] == m_board[i][2])
                return didFindWinner;
        }

        for (int i = 0; i < 3; i++)
        {
            if (m_board[0][i] != 0 && m_board[0][i] == m_board[1][i] && m_board[1][i] == m_board[2][i])
                return didFindWinner;
        }

        if (m_board[0][0] != 0 && m_board[0][0] == m_board[1][1] && m_board[1][1] == m_board[2][2])
            return didFindWinner;

        if (m_board[0][2] != 0 && m_board[0][2] == m_board[1][1] && m_board[1][1] == m_board[2][0])
            return didFindWinner;

        return 0;
    }

    int getNumOfProcess()
    {
        return m_numOfProcess;
    }
};

class Controller
{
private:
    Board *m_board;
    Player *m_p1;
    Player *m_p2;

public:
    Controller()
    {
        cout << "Welcome to tic tac toe game world!" << endl;
        doInitilize();
    }
    ~Controller()
    {
        cout << "See you later!" << endl;
        delete m_board;
        delete m_p1;
        delete m_p2;
    }

    void doInitilize()
    {
        string p1Username;
        string p2Username;
        cout << "Please enter 1P user name" << endl;
        cin >> p1Username;

        m_p1 = new Player(p1Username);

        cout << "Please enter 2P user name" << endl;
        cin >> p2Username;

        m_p2 = new Player(p2Username);

        m_board = new Board();
    }

    string getCurrentUsername()
    {
        if (m_board->getNumOfProcess() % 2 == 0)
            return m_p1->getUsername();
        else
            return m_p2->getUsername();
    }

    void startPlay()
    {
        int x, y, ret = 0;
        while (true)
        {
            m_board->showCurrentBoard();
            cout << "Now " << getCurrentUsername() << "'s turn" << endl;
            cin >> x >> y;

            ret = m_board->updateBoard(x, y);
            if (ret == didFindWinner)
                break;
        }

        cout << "CONGRATULATION! " << getCurrentUsername() << " Won!" << endl;

        m_board->showCurrentBoard();
    }
};

int main()
{
    Controller *c = new Controller();
    c->startPlay();

    delete c;
}