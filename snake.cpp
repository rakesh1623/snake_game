#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameover;

const int width = 20;
const int height = 20;
int x, y;
int score = 0;
int fruitx, fruity;
int tailx[100], taily[100];
int ntail=0;
enum direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
direction dir;
int printstat = 0;
void setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    fruitx = rand() % width;
    fruity = rand() % height;
}

void draw()
{
    system("cls");
    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
            {
                cout << "0";
            }
            else if (i == fruity && j == fruitx)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl;
    cout << "Your score is : " << score << endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void gameoverfun()
{
    // int arr[8] = {71, 65, 77, 69, 79, 86, 69, 82};
    // char ch;
    gameover = true;
    cout<<"GAME"<<endl<<"OVER"<<endl;

}
void logic()
{
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (dir)
    {
    case LEFT:
    {
        x--;
        break;
    }
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
    if(x>=width)
        x=0;
    else if(x<0)
        x=width-1;
    if(y>=height)
        y=0;
    else if(y<0)
        y=height-1;

    for (int i = 0; i < ntail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
        {
            gameover = true;
        }
    }

    // if(!tailx[0]==x && !taily[0]==y)
        // gameoverfun();

    if (x == fruitx && y == fruity)
    {
        ntail++;
        score = score + 10;
        fruitx = rand() % width;
        fruity = rand() % height;
    }
}
int main()
{
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        // cout<<"RUN"<<endl;
        Sleep(70);
        // printstat++;
        // cout << printstat << endl;
    }
}