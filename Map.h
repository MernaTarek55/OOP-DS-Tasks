#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <fstream>
#include <SFML/Graphics/Color.hpp>
class Map
{
public:
	static std::string fileName ;
	const static int MAX_ROWS = 30, MAX_COLS = 40 , GRID_SIZE = 20, WALL_SIZE = 20;
	static char environment[MAX_ROWS][MAX_COLS];
	static int environmentRows  , environmentCols;

	Map();
	bool ReadFile();
	void drawMap(sf::RenderWindow& window);
	static sf::Texture loadTexture(const std::string& fileName); 
	static bool isPositionOnWall(int x, int y) ;
};

