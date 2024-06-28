#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

// arrow keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

// variables
bool gameOver;
const int width = 50;
const int height = 25;
int x, y, fruitX, fruitY, score;
int const tailMax = 20;
int tailX[tailMax], tailY[tailMax];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// functions
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2; 
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case KEY_LEFT:
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case KEY_RIGHT:
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case KEY_UP:
                if (dir != DOWN)
                    dir = UP;
                break;
            case KEY_DOWN:
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
                gameOver = false;
                dir = STOP;
                x = width / 2;
                y = height / 2; 
                fruitX = rand() % width;
                fruitY = rand() % height;
                score = 0;
                break;
        }
    }
    
}

void Logic()
{
    for(int i=nTail-1;i>0;i--)
    {
        tailX[i]=tailX[i-1];
        tailY[i]=tailY[i-1];
    }
    tailX[0]=x;
    tailY[0]=y;

    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default: 
            break;
    }

    if ( x > width || x < 0  || y > height || y < 0)
        gameOver = false;

    for ( int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if ( x == fruitX && y == fruitY )
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        if(nTail < tailMax)
            nTail++;
    }
}

void Draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    string output;
    for (int i = 0; i < width+2; i++)
        output.append("#");
    output.append("\n!");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ( j == 0 )
            {
                output.append("#");
            }
            if ( i == y && j == x)
            {
                output.append("O");
            }
            else if ( i == fruitY && j == fruitX)
            {
                output.append("F");
            } 
            else 
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        output.append("o");
                        print = true;
                    }
                }
                if (!print)
                {
                    output.append(" ");
                }
            }

            if (j == (width - 1))
            {
                output.append("#");   
            }
        }
        output.append("\n!");
    }

    for (int i = 0; i < width+2; i++)
        output.append("#");
    output.append("\n!");
    output.append("Score:");
    cout << output << score << endl;
}

int main()
{
    srand(time(NULL));
    Setup();
    while(!gameOver)
    {
        Input();
        Logic();
        Draw();
        Sleep(50);
    }
    return 0;
}