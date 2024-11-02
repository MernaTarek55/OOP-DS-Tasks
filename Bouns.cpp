#include <iostream>
#include "player.h"
#include "enviroment.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void clearConsole() {
    system("CLS");
}

void findTreasure() {
    bool notwen = true;
    player p;
    p.setposX(1);
    p.setposY(1);

    enviroment env;
    env.setsize(20);
    const int environmentSize = env.getsize();

    srand(static_cast<unsigned>(time(0)));

    int treasurePosX = rand() % (environmentSize - 2) + 1;
    int treasurePosY = rand() % (environmentSize - 2) + 1;

    char character;
    cout << "Welcome to Find the Treasure game\nPlease enter your Character: ";
    cin >> character;

    char environment[50][50];
    env.createnviroment(environment); 

    environment[treasurePosX][treasurePosY] = 'O';
    environment[p.getposX()][p.getposY()] = character;

    while (notwen) {
        clearConsole();

        for (int i = 0; i < environmentSize; i++) {
            for (int j = 0; j < environmentSize; j++) {
                cout << environment[i][j];
            }
            cout << endl;
        }

        cout << "Use WASD to move. Find the treasure (O)! Press 'q' to quit.\n";

        if (_kbhit()) {
            char move = _getch();
            environment[p.getposX()][p.getposY()] = ' ';
            p.movment(move, environmentSize);
            environment[p.getposX()][p.getposY()] = character;

            if (p.getposX() == treasurePosX && p.getposY() == treasurePosY) {
                notwen = false;
                clearConsole();
                cout << "########################## Congratulations! You WON! #########################" << endl;
            }
        }
    }
}
