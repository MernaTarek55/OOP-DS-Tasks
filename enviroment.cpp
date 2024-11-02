#include "enviroment.h"

enviroment::enviroment()
{
	this->enviromentsize = 20;
}

void enviroment::setsize(int size)
{
	this->enviromentsize = size;
}

int enviroment::getsize()
{
	return this->enviromentsize;
}

void enviroment::createnviroment(char environment[50][50]) {
    for (int i = 0; i < this->enviromentsize; i++) {
        for (int j = 0; j < this->enviromentsize; j++) {
            if (i == 0 || i == this->enviromentsize - 1 || j == 0 || j == this->enviromentsize - 1) {
                environment[i][j] = 'X';
            }
            else {
                environment[i][j] = ' ';
            }
        }
    }
}
