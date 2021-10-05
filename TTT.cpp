
#include <iostream>

//Luke Trombatore
//GAME-2303 AI

using namespace std;

class TicTacToe
{
public:
    // TTT board, empty by default
    char board[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // used for keeping track what's in each space, and what value each player has
    enum Entry
    {
        EMPTY = ' ',
        PLAYER_ONE = 'x',
        PLAYER_TWO = 'o'
    };

    // has the board been completely filled?
    bool isFull()
    {
        bool result = true;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Entry::EMPTY)
                    result = false;
            }
        }

        return result;
    }

    // has someone won?
    bool isVictory(Entry e)
    {

        // first col
        if (board[0][0] == (char)e && board[0][1] == (char)e && board[0][2] == (char)e)
        {
            return true;
        }

        // second col
        else if (board[1][0] == (char)e && board[1][1] == (char)e && board[1][2] == (char)e)
        {
            return true;
        }

        // third col
        else if (board[2][0] == (char)e && board[2][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // first row
        else if (board[0][0] == (char)e && board[1][0] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        // second row
        else if (board[0][1] == (char)e && board[1][1] == (char)e && board[2][1] == (char)e)
        {
            return true;
        }

        // third row
        else if (board[0][2] == (char)e && board[1][2] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 1
        else if (board[0][0] == (char)e && board[1][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 2
        else if (board[0][2] == (char)e && board[1][1] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        return false;
    }

    // return size of the board; mostly just in case I wanted to make the board expandable
    int getSize()
    {
        return 3;
    }


    void dump()
    {
        std::cout << "----------------------------------------" << endl << endl;
        for (int i = 0; i < getSize(); i++)
        {
            for (int j = 0; j < getSize(); j++)
            {
                std::cout << " | " << board[i][j] << " | ";
            }

            std::cout << endl;
        }
        std::cout << "----------------------------------------" << endl << endl;
    }

};

static bool getHumanMove(int maxValue, TicTacToe::Entry human, TicTacToe& t)
{
    // check if player is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    int rowChoice = 0;
    int colChoice = 0;

    do {

        do {

            std::cout << "Enter column number (x) : 0 ... 2 : ";
            cin >> colChoice;
            std::cout << endl;

        } while (colChoice > maxValue || colChoice < 0);

        do {

            std::cout << "Enter row number (y) : 0 ... 2 : ";
            cin >> rowChoice;
            std::cout << endl;

        } while (rowChoice > maxValue || rowChoice < 0);


        if (t.board[rowChoice][colChoice] == t.EMPTY)
        {
            t.board[rowChoice][colChoice] = (char)human;

            return false;
        }

        else
        {
            std::cout << "Not a valid option! Please try again..." << endl;
        }
        

    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    // move complete
    return false;
}
//Function to take the Center
bool takeCenter(TicTacToe& t)
{

    if (t.board[1][1] == ' ')
    {
        t.board[1][1] = 'o';
        return true;
    }
    else
    {
        return false;
    }
}
// Function to take the corners
bool takeCorner(TicTacToe& t)
{
    if (t.board[0][0] == ' ')
    {
        t.board[0][0] = 'o';

        return true;
    }
    else if (t.board[0][2] == ' ')
    {
        t.board[0][2] = 'o';
        return true;
    }
    else if (t.board[2][0] == ' ')
    {
        t.board[2][0] = 'o';
        return true;
    }
    else if (t.board[2][2] == ' ')
    {
        t.board[2][2] = 'o';
        return true;
    }
    else
    {
        return false;
    }
}

//Fuction to block
static bool checkForPotentialvictory(int x, int y, char mark, TicTacToe& t)
{
    if (t.board[x][y] != ' ')
    {
        return false;
    }
    //Top left
    if (x == 0 && y == 0)
    {
        if (t.board[1][0] == mark && t.board[2][0] == mark)
        {
            t.board[0][0] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[2][2] == mark)
        {
            t.board[0][0] = 'o';
            return true;
        }
        else if (t.board[0][1] == mark && t.board[0][2] == mark)
        {
            t.board[0][0] = 'o';
            return true;
        }
        else
        {
            return false;
        }

    }
    //Top Middle
    if (x == 1 && y == 0)
    {
        if (t.board[1][0] == mark && t.board[2][0] == mark)
        {
            t.board[1][0] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[0][2] == mark)
        {
            t.board[1][0] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[1][2] == mark)
        {
            t.board[1][0] = 'o';
            return true;
        }
        else
        {
            return false;
        }

    }
    //Top Right
    if (x == 2 && y == 0)
    {
        if (t.board[1][1] == mark && t.board[0][2] == mark)
        {
            t.board[2][0] = 'o';
            return true;
        }
        else if (t.board[0][0] == mark && t.board[1][0] == mark)
        {
            t.board[2][0] = 'o';
            return true;
        }
        else if (t.board[2][1] == mark && t.board[2][2] == mark)
        {
            t.board[2][0] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }
    //Left middle
    if (x == 0 && y == 1)
    {
        if (t.board[0][0] == mark && t.board[0][2] == mark)
        {
            t.board[0][1] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[2][1] == mark)
        {
            t.board[0][1] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }
    //Bottom Left
    if (x == 0 && y == 2)
    {
        if (t.board[0][0] == mark && t.board[0][1] == mark)
        {
            t.board[0][2] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[2][0] == mark)
        {
            t.board[0][2] = 'o';
            return true;
        }
        else if (t.board[1][2] == mark && t.board[2][2] == mark)
        {
            t.board[0][2] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }
    //Center
    if (x == 1 && y == 1)
    {
        if (t.board[0][0] == mark && t.board[0][1] == mark)
        {
            t.board[1][1] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[2][0] == mark)
        {
            t.board[1][1] = 'o';
            return true;
        }
        else if (t.board[1][2] == mark && t.board[2][2] == mark)
        {
            t.board[1][1] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }
    //Bottom Middle
    if (x == 1 && y == 2)
    {
        if (t.board[0][2] == mark && t.board[2][2] == mark)
        {
            t.board[1][2] = 'o';
            return true;
        }
        else if (t.board[1][1] == mark && t.board[1][0] == mark)
        {
            t.board[1][2] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }
    //Middle Right
    if (x == 2 && y == 1)
    {
        if (t.board[1][1] == mark && t.board[0][1] == mark)
        {
            t.board[2][1] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }
    //Bottom Right
    if (x == 2 && y == 2)
    {
        if (t.board[0][1] == mark && t.board[1][1] == mark)
        {
            t.board[2][2] = 'o';
            return true;
        }
        else if (t.board[1][2] == mark && t.board[0][2] == mark)
        {
            t.board[2][2] = 'o';
            return true;
        }
        //Diagnol
        else if (t.board[2][1] == mark && t.board[2][0] == mark)
        {
            t.board[2][2] = 'o';
            return true;
        }
        else
        {
            return false;
        }
    }



    //Ends the statement, Don't remove
    return false;
}

        bool getComputerMove(TicTacToe::Entry computer, TicTacToe& t)
            {
            // check if computer is able to move
            if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
                return true;

            int rowChoice = 0;
            int colChoice = 0;

            // handle computer's move

            //loop to check if there is a potential win to block

            for (int i = 0; i < t.getSize(); i++)
            {
                for (int j = 0; j < t.getSize(); j++)
                {
                    if (checkForPotentialvictory(i, j, 'o', t))
                    {
                        t.board[i][j] = 'o';
                        return false;
                    }

                }
            }

            for (int i = 0; i < t.getSize(); i++)
            {
                for (int j = 0; j < t.getSize(); j++)
                {
                    if (checkForPotentialvictory(i, j, 'x', t))
                    {
                        t.board[i][j] = 'o';
                        return false;
                    }
                }
            }
            // attempt to get center

            if (takeCenter(t))
            {
                return false;
            }
            // attempt to get corner

            else if (takeCorner(t))
            {
                return false;
            }
        }
    // move complete

// ----------------------------
// main
// ----------------------------

int main()
{
    TicTacToe t;
    TicTacToe::Entry human = TicTacToe::PLAYER_ONE;
    TicTacToe::Entry computer = TicTacToe::PLAYER_TWO;

    int maxValue = t.getSize();

    cout << "----------------------------------------" << endl;

    cout << "You are '" << (char)human << "', " <<
        "the computer is: '" << (char)computer << "'" << endl;

    cout << "----------------------------------------" << endl << endl;

    // run the game until one player isn't able to go again
    do
    {
        // show board
        t.dump();
    } while (!getHumanMove(maxValue, human, t) && !getComputerMove(computer, t));


    t.dump();

    std::cout << endl;

    if (t.isVictory(human))
        cout << "Human Victory" << endl;

    else if (t.isVictory(computer))
        cout << "Computer Victory" << endl;

    else if (t.isFull())
        cout << "Tie" << endl;

    return(0);
}





