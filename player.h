#pragma once
class player
{
private:
	int posx, posy;
public:
	player();
	player(int posx, int posy);
	void movment(char move , int enviromentSize);
	void setposX(int x);
	void setposY(int y);
	int getposX();
	int getposY();
};

