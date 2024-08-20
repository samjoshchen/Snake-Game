#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib> 
#include <ctime>

// Dimensions of map
const int height = 20;
const int width = 40;

// Enum for directions
enum Direction { STOP, LEFT, RIGHT, DOWN, UP }; 
Direction snakeDir;

// Game state
bool gameOver = false;

// Player Score
int score;

// Positions
int x, y, fruitX, fruitY;

// Snake body position
int tailX[100], tailY[100];
int length = 0;

void hideCursor()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;

    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}

void gameStart()
{
    gameOver = false;
    score = 0;
    snakeDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    length = 0;
}

void gameRender() 
{
    system("cls"); // clear screen
    
    // Print top wall
    for (int i = 0; i < width + 2; i++) 
    {
        printf("#");
    }
    printf("\n");

    // Print map 
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (j == 0) 
            {
                printf("#"); // Left wall
            }

            bool print = false;

            if (i == y && j == x) 
            {
                printf("O"); // Snake head
                print = true;
            } 
            else if (i == fruitY && j == fruitX) 
            {
                printf("@"); // Fruit
                print = true;
            } 
            else 
            {
                for (int k = 0; k < length; k++) 
                {
                    if (tailX[k] == j && tailY[k] == i) 
                    {
                        printf("o"); // Snake body
                        print = true;
                    }
                }
            }

            if (!print) 
            {
                printf(" ");
            }

            if (j == width - 1)
            {
                printf("#"); // Right wall
            }
        }
        printf("\n");
    }

    // Print bottom wall
    for (int i = 0; i < width + 2; i++) 
    {
        printf("#");
    }
    printf("\n");

    printf("SCORE: %d\n", score);
}

void input()
{        
    if (_kbhit()) 
    { 
        // Getting Input 
        switch (_getch()) 
        { 
            case 'a': 
                snakeDir = LEFT; 
                break; 
            case 'd': 
                snakeDir = RIGHT; 
                break; 
            case 'w': 
                snakeDir = UP; 
                break; 
            case 's': 
                snakeDir = DOWN; 
                break;    
        }
    }
}

void logic()
{    
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < length; i++) 
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Collision Check
    if (x >= width || x < 0 || y >= height || y < 0) 
    {
        gameOver = true;
    }

    // Fruit Logic
    if (x == fruitX && y == fruitY) 
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        length++;
    }

    // Snake movement
    switch (snakeDir)
    {
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
}

int main() 
{
    srand(time(0));
    hideCursor();
    
    while (true)
    {
        gameStart();
        gameOver = false;
        
        while (!gameOver)
        {
            input();
            logic();
            gameRender();
            Sleep(100);
        }
        
        if (gameOver) 
        {
            system("cls");
                
            printf(" .d8888b.  8888888 88888888888       .d8888b.  888     888 8888888b.\n");
            printf("d88P  Y88b   888       888          d88P  Y88b 888     888 888  \"Y88b\n");
            printf("888    888   888       888          888    888 888     888 888    888 \n");
            printf("888          888       888          888        888     888 888    888\n");
            printf("888  88888   888       888          888  88888 888     888 888    888\n");
            printf("888    888   888       888          888    888 888     888 888    888\n");
            printf("Y88b  d88P   888       888          Y88b  d88P Y88b. .d88P 888  .d88P\n");
            printf(" \"Y8888P88 8888888     888           \"Y8888P88  \"Y88888P\"  8888888P\"\n \n \n");
                
            printf("Continue? (Y/N)");

            char r = _getch();
            if (r == 'n' || r == 'N') 
            {
                system("cls");        
                printf(" .d8888b.   .d88888b.   .d88888b.  8888888b.  888888b. Y88b   d88P 8888888888 \n");
                printf("d88P  Y88b d88P\" \"Y88b d88P\" \"Y88b 888  \"Y88b 888  \"88b Y88b d88P  888        \n");
                printf("888    888 888     888 888     888 888    888 888  .88P  Y88o88P   888        \n");
                printf("888        888     888 888     888 888    888 8888888K.   Y888P    8888888    \n");
                printf("888  88888 888     888 888     888 888    888 888  \"Y88b   888     888        \n");
                printf("888    888 888     888 888     888 888    888 888    888   888     888        \n");
                printf("Y88b  d88P Y88b. .d88P Y88b. .d88P 888  .d88P 888   d88P   888     888        \n");
                printf(" \"Y8888P88  \"Y88888P\"   \"Y88888P\"  8888888P\"  8888888P\"    888     8888888888 \n");

                return 0;
            }
        }
    }        
}
