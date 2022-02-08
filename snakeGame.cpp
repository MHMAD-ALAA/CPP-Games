#include "iostream"
#include "conio.h"
#include "windows.h"

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int tailX[100], tailY[100];
int nTail;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void fruitPos() {
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitPos();
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width; ++i) {
        cout << "$";
    }
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0 || j == width - 1) {
                cout << "$";
            }
            else if (i == y && j == x) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }
            else {
                bool print = false;
                for(int k = 0; k < nTail; ++k) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout <<"o";
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; ++i) {
        cout << "$";
    }
    cout << endl;
    cout << "Score : " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
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
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; ++i) {
        swap(prevX, tailX[i]);
        swap(prevY, tailY[i]);
    }
    switch (dir) {
        Sleep(200);
        case LEFT:
            x--;
            Sleep(50);
            break;
        case RIGHT:
            x++;
            Sleep(50);
            break;
        case UP:
            y--;
            Sleep(50);
            break;
        case DOWN:
            y++;
            Sleep(50);
            break;
        default:
            break;
    }

 //   if (x > width || x < 0 || y > height || y < 0)
 //       gameOver = true;
    if(x >= width) x = 0;
    else if(x < 0) x = width - 1;
    if(y >= height) y = 0;
    else if(y < 0) y = height - 1;

    for (int i = 0; i < nTail; ++i) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    if (fruitX == x && fruitY == y) {
        nTail++;
        score += 10;
        fruitPos();
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }

    return 0;
}
