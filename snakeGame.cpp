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
                cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; ++i) {
        cout << "$";
    }
    cout << endl;
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

    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;
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
    }

    return 0;
}
