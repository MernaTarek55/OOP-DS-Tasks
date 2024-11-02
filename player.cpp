#include "player.h"

player::player()
{
    this->posx = 1;
    this->posy = 1;
}

player::player(int posx, int posy)
{
    this->posx = posx;
    this->posy = posy;
}

void player::movment(char move , int enviromentSize)
{
    switch (move) {
    case 'a':
        if (this->posy > 1) this->posy--;
        break;
    case 'd':
        if (this->posy < enviromentSize - 2) this->posy++;
        break;
    case 's':
        if (this->posx < enviromentSize - 2) this->posx++;
        break;
    case 'w':
        if (this->posx > 1) this->posx--;
        break;
    default:
        break;
    }
}

void player::setposX(int x)
{
    this->posx = x;
}

void player::setposY(int y)
{
    this->posy = y;
}

int player::getposX()
{
    return this->posx;
}

int player::getposY()
{
    return this->posy;
}
