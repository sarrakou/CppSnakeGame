#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int width=40;
int height=20;
int x, y, score, xTarget, yTarget;
enum Direction {STOP=0, RIGHT, LEFT, UP, DOWN};
Direction dir;
int xtail[100], ytail[100];
int ntail;
bool gameOver;

void setUp(){
    x= width/2;
    dir = STOP;
    y= height/2;
    gameOver= false;
    xTarget= rand() % width;
    yTarget= rand() % height;
    score=0;
}

void Draw(){
    system("cls");
    for(int i=0; i<width; i++){
        cout << '8';
    }
    cout << endl;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if ((j==0) || (j==width-1)){
                cout << "8";
            } else if ((i==y) && (j==x)){
                cout << 'O';
            } else if ((i==yTarget)&&(j==xTarget)){
                cout << 'X';
            } else {
                bool print= false;
                for (int k=0; k<ntail; k++){
                    if(xtail[k]==j && ytail[k]==i){
                        cout << 'o';
                        print= true;
                    }
                }
                if (!print)
                    cout << ' ';
            }

            if(j==width-1)
                cout << '8';
        }
        cout << endl;
    }

    for (int i=0; i<width;i++){
        cout << '8';
    }
    cout << endl;
    cout <<  "Score: " << score << endl;
}

void Input(){
    if (_kbhit()){
        switch (_getch()){
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir= RIGHT;
                break;
            case 'w':
                dir= UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver= true;
                break;
        }
    }
}

void Logic(){
    
    int xprev = xtail[0];
    int yprev = ytail[0];
    int xprev2, yprev2;
    xtail[0]= x;
    ytail[0]= y;

    for (int i=1; i<ntail; i++){
        xprev2= xtail[i];
        yprev2= ytail[i];
        xtail[i]= xprev;
        ytail[i]= yprev;
        xprev = xprev2;
        yprev = yprev2;
    }

    switch (dir){
        case LEFT:
            Sleep(10);
            x--;
            break;
        case RIGHT:
            Sleep(10);
            x++;
            break;
        case UP:
            Sleep(10);
            y--;
            break;
        case DOWN:
            Sleep(10);
            y++;
            break;
        default:
            break;
    }

    if ( x>= width ) x=0; else if (x<0) x= width-1;
    if ( y>= height) y=0; else if (y<0) y= height-1;

    for(int i=0; i<ntail; i++){
        if(xtail[i]==x && ytail[i]==y){
            gameOver = true;
        }
    }
    if (x == xTarget && y == yTarget){
        score += 10;
        xTarget = rand()%width;
        yTarget = rand()%height;
        ntail++;
    }

}

int main() {
    setUp();
    while (!gameOver){
        Draw();
        Input();
        Logic();
    }
    return 0;
}