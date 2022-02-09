
#include "iostream"
#include "time.h"
#include "conio.h"
#include "windows.h"
using namespace std;

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};
void sysClear() {
    // Use Direct implementation of "cls" to clear screen without flickering!
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
class cBall{
private:
    int x, y;
    int originalX, originalY;
    eDir direction;
public:
    cBall(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }
    void Reset() {
        x = originalX;
        y = originalY;
        direction = STOP;
    }
    void ChangeDirection(eDir _dir) {
        direction = _dir;
    }
    void RandomDirection() {
        direction = (eDir) ((rand() % 6) + 1);  // from 1 to 6
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }
    void Move() {
        switch (direction) {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--; y--;
                break;
            case DOWNLEFT:
                x--; y++;
                break;
            case UPRIGHT:
                x++; y--;
                break;
            case DOWNRIGHT:
                x++; y++;
                break;
            default:
                break;
        }
    }
    friend ostream & operator<<(ostream & output, cBall ball) {
        output << "Ball [" << ball.x << "," << ball.y << "][" << ball.direction << "]";
        return output;
    }
};
class cPaddle{
private:
    int x, y;
    int originalX, originalY;
public:
    cPaddle(){
        x = 0; y = 0;
    }
    cPaddle(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    inline void Reset() { x = originalX; y = originalY; }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUP() { y--; }
    inline void moveDown() { y++; }
    friend ostream & operator<<(ostream & output, cPaddle paddle) {
        output << "Paddle [" << paddle.x << "," << paddle.y << "]";
        return output;
    }
};
class cGameManager{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;
public:
    cGameManager(int _width, int _height) {
        width = _width;
        height = _height;

        srand(time(NULL));
        quit = false;
        up1 = 'w'; up2 = 'i';
        down1 = 's'; down2 = 'k';
        score1 = score2 = 0;
        ball = new cBall(_width / 2, _height / 2);
        player1 = new cPaddle(1, _height / 2 - 3);
        player2 = new cPaddle(_width - 2, _height / 2 - 3);
    }
    ~cGameManager(){
        delete ball;
        delete player1;
        delete player2;
    }
    void ScoreUp(cPaddle *player) {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball -> Reset();
        player1 -> Reset();
        player2 -> Reset();
    }
    void Draw() {
        sysClear();
        for (int i = 0; i < width + 2; ++i) {
            cout << "\xB2";
        } cout << endl;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int ballX = ball -> getX();
                int ballY = ball -> getY();
                int player1X = player1 -> getX();
                int player1Y = player1 -> getY();
                int player2X = player2 -> getX();
                int player2Y = player2 -> getY();

                if (j == 0) {
                    cout << "\xB2";
                }

                if (ballX == j && ballY == i) {
                    cout << "O";
                } else if (player1X == j && player1Y == i) {
                    cout << "\xDB";
                } else if (player2X == j && player2Y == i) {
                    cout << "\xDB";
                } else if (player1X == j && player1Y + 1 == i) {
                    cout << "\xDB";
                } else if (player1X == j && player1Y + 2 == i) {
                    cout << "\xDB";
                } else if (player1X == j && player1Y + 3 == i) {
                    cout << "\xDB";
                } else if (player2X == j && player2Y + 1 == i) {
                    cout << "\xDB";
                } else if (player2X == j && player2Y + 2 == i) {
                    cout << "\xDB";
                } else if (player2X == j && player2Y + 3 == i) {
                    cout << "\xDB";
                } else {
                    cout << " ";
                }

                if (j == width - 1) {
                    cout << "\xB2";
                }
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; ++i) {
            cout << "\xB2";
        } cout << endl;

//         cout << "Score1 : " << score1 << endl;
//         cout << "Score2 : " << score2 << endl;
    }
    void Input() {
        ball -> Move();

        int ballX = ball -> getX();
        int ballY = ball -> getY();
        int player1X = player1 -> getX();
        int player1Y = player1 -> getY();
        int player2X = player2 -> getX();
        int player2Y = player2 -> getY();

        if (_kbhit()) {
            char current = _getch();
            if (current == up1){
                if (player1Y > 0)
                    player1 -> moveUP();
            }
            if (current == up2){
                if (player2Y > 0)
                    player2 -> moveUP();
            }
            if (current == down1){
                if (player1Y + 4 < height)
                    player1 -> moveDown();
            }
            if (current == down2){
                if (player2Y + 4 < height)
                    player2 -> moveDown();
            }

            if (ball -> getDirection() == STOP)
                ball -> RandomDirection();

            if (current == 'q')
                quit = true;
        }
    }
    void Logic() {
        int ballX = ball -> getX();
        int ballY = ball -> getY();
        int player1X = player1 -> getX();
        int player1Y = player1 -> getY();
        int player2X = player2 -> getX();
        int player2Y = player2 -> getY();

        // left paddle
        for (int i = 0; i < 4; ++i) {
            if ((ballX == player1X + 1) && (ballY = player1Y + i))
                ball -> ChangeDirection((eDir) ((rand() % 3) + 4));
        }
        // right paddle
        for (int i = 0; i < 4; ++i) {
            if ((ballX == player2X - 1) && (ballY = player2Y + i))
                ball -> ChangeDirection((eDir) ((rand() % 3) + 1));
        }

        //bottom wall
        if (ballY == height - 1) {
            ball -> ChangeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }
        //top wall
        if (ballY == 0) {
            ball -> ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        }
        // right wall
        if (ballX == width - 1)
            ScoreUp(player1);
        // left wall
        if (ballX == 0)
            ScoreUp(player2);
    }
    void Run() {
        while (!quit) {
            Draw();
            Input();
            Logic();
        }
    }
};
int main() {
    cGameManager c(40, 20);
    c.Run();

    return 0;
}
