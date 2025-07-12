#include  <stdio.h>
#include "GameFiles/includeSDL/SDL2/SDL.h"

#undef main

typedef enum
{
    EMPTY,
    X,
    O
} Cell;


Cell board[3][3]; // Game board
void computerWin(void)
{
    // Horizontal win conditions
    if (board[0][0] == O && board[0][1] == O && board[0][2] == EMPTY)
    {
        board[0][2] = O;
    }
    else if (board[0][0] == O && board[0][1] == EMPTY && board[0][2] == O)
    {
        board[0][1] = O;
    }
    else if (board[0][0] == EMPTY && board[0][1] == O && board[0][2] == O)
    {
        board[0][0] = O;
    }
    else if (board[1][0] == EMPTY && board[1][1] == O && board[1][2] == O)
    {
        board[1][0] = O;
    }
    else if (board[1][0] == O && board[1][1] == EMPTY && board[1][2] == O)
    {
        board[1][1] = O;
    }
    else if (board[1][0] == O && board[1][1] == O && board[1][2] == EMPTY)
    {
        board[1][2] = O;
    }
    else if (board[2][0] == EMPTY && board[2][1] == O && board[2][2] == O)
    {
        board[2][0] = O;
    }
    else if (board[2][0] == O && board[2][1] == EMPTY && board[2][2] == O)
    {
        board[2][1] = O;
    }
    else if (board[2][0] == O && board[2][1] == O && board[2][2] == EMPTY)
    {
        board[2][2] = O;
    }
    // Vertical win conditions
    else if (board[0][0] == EMPTY && board[1][0] == O && board[2][0] == O)
    {
        board[0][0] = O;
    }
    else if (board[0][0] == O && board[1][0] == EMPTY && board[2][0] == O)
    {
        board[1][0] = O;
    }
    else if (board[0][0] == O && board[1][0] == O && board[2][0] == EMPTY)
    {
        board[2][0] = O;
    }
    else if (board[0][1] == EMPTY && board[1][1] == O && board[2][1] == O)
    {
        board[0][1] = O;
    }
    else if (board[0][1] == O && board[1][1] == EMPTY && board[2][1] == O)
    {
        board[1][1] = O;
    }
    else if (board[0][1] == O && board[1][1] == O && board[2][1] == EMPTY)
    {
        board[2][1] = O;
    }
    else if (board[0][2] == EMPTY && board[1][2] == O && board[2][2] == O)
    {
        board[0][2] = O;
    }
    else if (board[0][2] == O && board[1][2] == EMPTY && board[2][2] == O)
    {
        board[1][2] = O;
    }
    else if (board[0][2] == O && board[1][2] == O && board[2][2] == EMPTY)
    {
        board[2][2] = O;
    }
    // Diagonal win conditions
    else if (board[0][0] == EMPTY && board[1][1] == O && board[2][2] == O)
    {
        board[0][0] = O;
    }
    else if (board[0][0] == O && board[1][1] == EMPTY && board[2][2] == O)
    {
        board[1][1] = O;
    }
    else if (board[0][0] == O && board[1][1] == O && board[2][2] == EMPTY)
    {
        board[2][2] = O;
    }
    else if (board[0][2] == EMPTY && board[1][1] == O && board[2][0] == O)
    {
        board[0][2] = O;
    }
    else if (board[0][2] == O && board[1][1] == EMPTY && board[2][0] == O)
    {
        board[1][1] = O;
    }
    else if (board[0][2] == O && board[1][1] == O && board[2][0] == EMPTY)
    {
        board[2][0] = O;
    }
}

int playerbreak(void)
{
    // Horizontal block conditions
    if (board[0][0] == X && board[0][1] == X && board[0][2] == EMPTY)
    {
        board[0][2] = O;
        return 1;
    }
    else if (board[0][0] == X && board[0][1] == EMPTY && board[0][2] == X)
    {
        board[0][1] = O;
        return 1;
    }
    else if (board[0][0] == EMPTY && board[0][1] == X && board[0][2] == X)
    {
        board[0][0] = O;
        return 1;
    }
    else if (board[1][0] == EMPTY && board[1][1] == X && board[1][2] == X)
    {
        board[1][0] = O;
        return 1;
    }
    else if (board[1][0] == X && board[1][1] == EMPTY && board[1][2] == X)
    {
        board[1][1] = O;
        return 1;
    }
    else if (board[1][0] == X && board[1][1] == X && board[1][2] == EMPTY)
    {
        board[1][2] = O;
        return 1;
    }
    else if (board[2][0] == EMPTY && board[2][1] == X && board[2][2] == X)
    {
        board[2][0] = O;
        return 1;
    }
    else if (board[2][0] == X && board[2][1] == EMPTY && board[2][2] == X)
    {
        board[2][1] = O;
        return 1;
    }
    else if (board[2][0] == X && board[2][1] == X && board[2][2] == EMPTY)
    {
        board[2][2] = O;
        return 1;
    }
    // Vertical block conditions
    else if (board[0][0] == EMPTY && board[1][0] == X && board[2][0] == X)
    {
        board[0][0] = O;
        return 1;
    }
    else if (board[0][0] == X && board[1][0] == EMPTY && board[2][0] == X)
    {
        board[1][0] = O;
        return 1;
    }
    else if (board[0][0] == X && board[1][0] == X && board[2][0] == EMPTY)
    {
        board[2][0] = O;
        return 1;
    }
    else if (board[0][1] == EMPTY && board[1][1] == X && board[2][1] == X)
    {
        board[0][1] = O;
        return 1;
    }
    else if (board[0][1] == X && board[1][1] == EMPTY && board[2][1] == X)
    {
        board[1][1] = O;
        return 1;
    }
    else if (board[0][1] == X && board[1][1] == X && board[2][1] == EMPTY)
    {
        board[2][1] = O;
        return 1;
    }
    else if (board[0][2] == EMPTY && board[1][2] == X && board[2][2] == X)
    {
        board[0][2] = O;
        return 1;
    }
    else if (board[0][2] == X && board[1][2] == EMPTY && board[2][2] == X)
    {
        board[1][2] = O;
        return 1;
    }
    else if (board[0][2] == X && board[1][2] == X && board[2][2] == EMPTY)
    {
        board[2][2] = O;
        return 1;
    }
    // Diagonal block conditions
    else if (board[0][0] == EMPTY && board[1][1] == X && board[2][2] == X)
    {
        board[0][0] = O;
        return 1;
    }
    else if (board[0][0] == X && board[1][1] == EMPTY && board[2][2] == X)
    {
        board[1][1] = O;
        return 1;
    }
    else if (board[0][0] == X && board[1][1] == X && board[2][2] == EMPTY)
    {
        board[2][2] = O;
        return 1;
    }
    else if (board[0][2] == EMPTY && board[1][1] == X && board[2][0] == X)
    {
        board[0][2] = O;
        return 1;
    }
    else if (board[0][2] == X && board[1][1] == EMPTY && board[2][0] == X)
    {
        board[1][1] = O;
        return 1;
    }
    else if (board[0][2] == X && board[1][1] == X && board[2][0] == EMPTY)
    {
        board[2][0] = O;
        return 1;
    }
    else
    {
        return 0;
    }
}

void lastdraw(void) //For last move
{
    if (board[0][0] == EMPTY)
    {
        board[0][0] = O;
    }
    else if (board[0][1] == EMPTY)
    {
        board[0][1] = O;
    }
    else if (board[0][2] == EMPTY)
    {
        board[0][2] = O;
    }
    else if (board[1][0] == EMPTY)
    {
        board[1][0] = O;
    }
    else if (board[1][1] == EMPTY)
    {
        board[1][1] = O;
    }
    else if (board[1][2] == EMPTY)
    {
        board[1][2] = O;
    }
    else if (board[2][0] == EMPTY)
    {
        board[2][0] = O;
    }
    else if (board[2][1] == EMPTY)
    {
        board[2][1] = O;
    }
    else if (board[2][2] == EMPTY)
    {
        board[2][2] = O;
    }
}

