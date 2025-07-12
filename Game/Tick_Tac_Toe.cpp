#include "All_Functions.c"
#include "GameFiles/includeSDL/SDL2/SDL.h"
#include "GameFiles/includeTTF/SDL2/SDL_ttf.h"
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <cmath>

int mid = 0;
int *middle = &mid;
int f = 0;
int *first = &f;

#undef main

using namespace std;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 700
#define CELL_SIZE (SCREEN_WIDTH / 3)


typedef enum
{
    MAIN_MENU,
    IN_GAME
} GameState;

bool isPlayerXTurn = true;
bool gameRunning = true;
GameState currentState = MAIN_MENU;
bool playWithComputer = false;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Button rectangles

const SDL_Rect playWithPlayerButton = {(SCREEN_WIDTH - 300) / 2, (SCREEN_HEIGHT - 50) / 2 - 60, 300, 50};
const SDL_Rect playWithComputerButton = {(SCREEN_WIDTH - 300) / 2, (SCREEN_HEIGHT - 50) / 2 + 60, 300, 50};
const SDL_Rect restartButton = {10, 10, 100, 50};
const SDL_Rect mainMenuButton = {SCREEN_WIDTH - 110, 10, 100, 50};

// Function to initialize SDL
bool initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

//It will render the text
void renderText(const char *text, int x, int y, SDL_Color textColor, TTF_Font *font) //
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
    if (!textSurface)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// Function to reset the game
void resetGame()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = EMPTY;
        }
    }
    *middle = 0;
    *first = 0;
    isPlayerXTurn = true;
    gameRunning = true;
}

// Function to draw a button with a label
void drawButton(const SDL_Rect &button, const char *label, SDL_Color buttonColor, SDL_Color textColor, TTF_Font *font)
{
    // Draw the button background
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &button);

    // Render the label text
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, label, textColor);
    if (!textSurface)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Center the text on the button
    int textX = button.x + (button.w - textSurface->w) / 2;
    int textY = button.y + (button.h - textSurface->h) / 2;
    SDL_Rect textRect = {textX, textY, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// Function to draw the grid
void drawGrid()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < 3; i++)
    {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 100, i * CELL_SIZE, SCREEN_HEIGHT + 100);    // Vertical lines
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE + 100, SCREEN_WIDTH, i * CELL_SIZE + 100); // Horizontal lines
    }
}

bool isBoardFull() // Checks if the board is full
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

// Function to draw X or O
void drawSymbol(int row, int col, Cell symbol)
{
    if (symbol == EMPTY)
        return;
    int x = col * CELL_SIZE + CELL_SIZE / 2;
    int y = row * CELL_SIZE + CELL_SIZE / 2 + 100;

    if (symbol == X)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for X
        SDL_RenderDrawLine(renderer, x - 50, y - 50, x + 50, y + 50);
        SDL_RenderDrawLine(renderer, x - 50, y + 50, x + 50, y - 50);
    }
    else if (symbol == O)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for O
        int radius = 50;
        for (int angle = 0; angle < 360; angle++)
        {
            double rad = angle * M_PI / 180.0;
            int dx = static_cast<int>(radius * cos(rad));
            int dy = static_cast<int>(radius * sin(rad));
            SDL_RenderDrawPoint(renderer, x + dx, y + dy);
        }
    }
}

// Function to render the board
void renderBoard()
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            drawSymbol(row, col, board[row][col]);
        }
    }
}

// Function to check who is the winner
Cell checkWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2];
    return EMPTY;
}

// Function to handle mouse clicks
void handleMouseClick(int x, int y)
{

    if (currentState == MAIN_MENU)
    {
        if (x >= playWithPlayerButton.x && x <= playWithPlayerButton.x + playWithPlayerButton.w &&
            y >= playWithPlayerButton.y && y <= playWithPlayerButton.y + playWithPlayerButton.h)
        {
            playWithComputer = false;
            currentState = IN_GAME;
            resetGame();
        }
        else if (x >= playWithComputerButton.x && x <= playWithComputerButton.x + playWithComputerButton.w &&
                 y >= playWithComputerButton.y && y <= playWithComputerButton.y + playWithComputerButton.h)
        {
            playWithComputer = true;
            currentState = IN_GAME;
            resetGame();
        }
    }
    else if (currentState == IN_GAME)
    {
        if (x >= restartButton.x && x <= restartButton.x + restartButton.w &&
            y >= restartButton.y && y <= restartButton.y + restartButton.h)
        {
            resetGame();
        }
        else if (x >= mainMenuButton.x && x <= mainMenuButton.x + mainMenuButton.w &&
                 y >= mainMenuButton.y && y <= mainMenuButton.y + mainMenuButton.h)
        {
            currentState = MAIN_MENU;
            // Clear the terminal screen
            #ifdef _WIN32
            system("cls"); // Windows
            #else
            system("clear"); // Linux/macOS
            #endif
        }
        else
        {
            int row = (y - 100) / CELL_SIZE;
            int col = x / CELL_SIZE;
            if (row < 3 && col < 3 && board[row][col] == EMPTY && gameRunning)
            {
                board[row][col] = isPlayerXTurn ? X : O;
                isPlayerXTurn = !isPlayerXTurn;

                Cell winner = checkWinner();
                if (winner != EMPTY)
                {
                    printf("Player %s wins!\n", winner == X ? "PlayerX" : "PlayerO");
                    gameRunning = false;
                }
                else if (isBoardFull())
                {
                    printf("It's a draw!\n");
                    gameRunning = false;
                    isPlayerXTurn = !isPlayerXTurn;
                }
                if (playWithComputer && gameRunning && !isPlayerXTurn)
                {

                    // Example logic: Find first empty cell for computer's move
                    if (board[1][1] == EMPTY && *(first) == 0)
                    {
                        *(first) = 1;
                        board[1][1] = O; // Assuming computer is 'O'
                        if (currentState == IN_GAME)
                        {
                            drawGrid();
                            renderBoard(); // This ensures all moves, including the computer's, are displayed.
                        }
                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                    }
                    else if (*(first) == 0)
                    {
                        *(first) = 2;
                        board[0][0] = O; // Assuming computer is 'O'
                        if (currentState == IN_GAME)
                        {
                            drawGrid();
                            renderBoard(); // This ensures all moves, including the computer's, are displayed.
                        }
                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                    }
                    else if (*(first) == 1)
                    {
                        computerWin();
                        Cell winner = checkWinner();
                        if (winner != EMPTY)
                        {
                            if (currentState == IN_GAME)
                            {
                                drawGrid();
                                renderBoard(); // This ensures all moves, including the computer's, are displayed.
                            }
                            isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                            printf("%s wins!\n", winner == X ? "Player" : "Computer");
                            gameRunning = false;
                        }
                        else if (isBoardFull())
                        {
                            printf("It's a draw!\n");
                            gameRunning = false;
                            isPlayerXTurn = !isPlayerXTurn;
                        }
                        if (!isPlayerXTurn)
                        {
                            int b = playerbreak();
                            if (currentState == IN_GAME && b == 1)
                            {
                                drawGrid();
                                renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                            }
                        }
                        if (!isPlayerXTurn)
                        {
                            if (board[0][1] == EMPTY && board[2][1] == EMPTY)
                            {
                                if (board[0][0] == X || board[0][2] == X)
                                {
                                    board[0][1] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if (board[2][0] == X || board[2][2] == X)
                                {
                                    board[2][1] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                            else if (board[1][0] == EMPTY && board[1][2] == EMPTY)
                            {
                                if (board[0][0] == X || board[2][0] == X)
                                {
                                    board[1][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if (board[0][2] == X || board[2][2] == X)
                                {
                                    board[1][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                        }
                        if (!isPlayerXTurn)
                        {
                            if (board[0][0] == EMPTY && board[0][1] == X && board[1][0] == X)
                            {
                                board[0][0] = O;
                                if (currentState == IN_GAME)
                                {
                                    drawGrid();
                                    renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                    isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                }
                            }
                            else if (board[0][2] == EMPTY && board[0][1] == X && board[1][2] == X)
                            {
                                board[0][2] = O;
                                if (currentState == IN_GAME)
                                {
                                    drawGrid();
                                    renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                    isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                }
                            }
                            else if (board[2][2] == EMPTY && board[1][2] == X && board[2][1] == X)
                            {
                                board[2][2] = O;
                                if (currentState == IN_GAME)
                                {
                                    drawGrid();
                                    renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                    isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                }
                            }
                            else if (board[2][0] == EMPTY && board[1][0] == X && board[2][1] == X)
                            {
                                board[2][0] = O;
                                if (currentState == IN_GAME)
                                {
                                    drawGrid();
                                    renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                    isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                }
                            }
                            else if (board[0][0] == EMPTY && board[2][2] == EMPTY)
                            {
                                if ((board[0][1] == X || board[1][0] == X))
                                {
                                    board[0][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if ((board[1][2] == X || board[2][1] == X))
                                {
                                    board[2][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                            else if (board[0][2] == EMPTY && board[2][0] == EMPTY)
                            {
                                if ((board[0][1] == X || board[1][2] == X))
                                {
                                    board[0][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if ((board[1][0] == X || board[2][1] == X))
                                {
                                    board[2][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                        }
                        if (!isPlayerXTurn)
                        {
                            lastdraw();
                            if (currentState == IN_GAME)
                            {
                                drawGrid();
                                renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                            }
                        }
                    }
                    else if (*(first) == 2)
                    {
                        computerWin();
                        Cell winner = checkWinner();
                        if (winner != EMPTY)
                        {
                            if (currentState == IN_GAME)
                            {
                                drawGrid();
                                renderBoard(); // This ensures all moves, including the computer's, are displayed.
                            }
                            isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                            printf("%s wins!\n", winner == X ? "Player" : "Computer");
                            gameRunning = false;
                        }
                        else if (isBoardFull())
                        {
                            printf("It's a draw!\n");
                            gameRunning = false;
                            isPlayerXTurn = !isPlayerXTurn;
                        }
                        if (!isPlayerXTurn)
                        {
                            int b = playerbreak();
                            if (currentState == IN_GAME && b == 1)
                            {
                                drawGrid();
                                renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                            }
                        }
                        if (!isPlayerXTurn)
                        {
                            if (board[0][0] == O && board[1][1] == X && board[2][2] == X)
                            {
                                if (board[0][2] == EMPTY)
                                {
                                    board[0][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if (board[2][0] == EMPTY)
                                {
                                    board[2][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                            else if (board[0][0] == X && board[1][1] == X && board[2][2] == O)
                            {
                                if (board[0][2] == EMPTY)
                                {
                                    board[0][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if (board[2][0] == EMPTY)
                                {
                                    board[2][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                            else if (board[0][2] == O && board[1][1] == X && board[2][0] == X)
                            {
                                if (board[0][0] == EMPTY)
                                {
                                    board[0][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if (board[2][2] == EMPTY)
                                {
                                    board[2][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                            else if (board[0][2] == X && board[1][1] == X && board[2][0] == O)
                            {
                                if (board[0][0] == EMPTY)
                                {
                                    board[0][0] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                                else if (board[2][2] == EMPTY)
                                {
                                    board[2][2] = O;
                                    if (currentState == IN_GAME)
                                    {
                                        drawGrid();
                                        renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                        isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                                    }
                                }
                            }
                        }
                        if (!isPlayerXTurn)
                        {
                            lastdraw();
                            if (currentState == IN_GAME)
                            {
                                drawGrid();
                                renderBoard();                  // This ensures all moves, including the computer's, are displayed.
                                isPlayerXTurn = !isPlayerXTurn; // Switch turn back to the player
                            }
                        }
                    }
                }
            }
        }
    }
}

// Function to render the main menu
void renderMainMenu(TTF_Font *headingFont, TTF_Font *buttonFont)
{
    SDL_Color headingColor = {0, 0, 0, 255};    // Black
    SDL_Color buttonColor = {0, 200, 0, 255};   // Green
    SDL_Color textColor = {255, 255, 255, 255}; // White

    // Render the heading
    renderText("TIC TAC TOE", SCREEN_WIDTH / 2 - 132, 50, headingColor, headingFont);

    // Render buttons with labels
    drawButton(playWithPlayerButton, "Play with Player", buttonColor, textColor, buttonFont);
    drawButton(playWithComputerButton, "Play with Computer", buttonColor, textColor, buttonFont);
}

// Main game loop
void gameLoop(TTF_Font *headingFont, TTF_Font *buttonFont)
{
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                handleMouseClick(e.button.x, e.button.y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (currentState == MAIN_MENU)
        {
            renderMainMenu(headingFont, buttonFont);
        }
        else if (currentState == IN_GAME)
        {
            drawButton(restartButton, "Restart", {0, 200, 0, 255}, {255, 255, 255, 255}, buttonFont);
            drawButton(mainMenuButton, "Main Menu", {200, 0, 0, 255}, {255, 255, 255, 255}, buttonFont);
            drawGrid();
            renderBoard();
        }

        SDL_RenderPresent(renderer);
    }
}

// Cleanup function
void closeSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Main function
int main()
{
    if (!initSDL())
    {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    // Load fonts
    TTF_Font *headingFont = TTF_OpenFont("GameFiles/fonts/Bageta400.ttf", 48);    // Heading font
    TTF_Font *buttonFont = TTF_OpenFont("GameFiles/fonts/Babyboggie400.ttf", 24); // Button font
    if (!headingFont || !buttonFont)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        closeSDL();
        return -1;
    }

    resetGame();
    gameLoop(headingFont, buttonFont);

    TTF_CloseFont(headingFont);
    TTF_CloseFont(buttonFont);
    closeSDL();
    return 0;
}