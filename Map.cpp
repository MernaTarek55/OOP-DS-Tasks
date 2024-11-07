#include "Map.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

std::string Map::fileName = "walls.txt";
int Map::environmentRows = 0;
int Map::environmentCols = 0;
char Map::environment[Map::MAX_ROWS][Map::MAX_COLS] = { {0} };
Map::Map()
{
}
bool Map::isPositionOnWall(int x, int y) {
    // Check if the position is on a wall in the map
    int gridX = x / Map::GRID_SIZE;
    int gridY = y / Map::GRID_SIZE;

    if (gridX >= 0 && gridX < environmentCols && gridY >= 0 && gridY < environmentRows) {
        return environment[gridY][gridX] == 'x'; // Assuming 'x' represents a wall
    }
    return false;
}
bool Map:: ReadFile()
{

    std::ifstream file(Map::fileName);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << Map::fileName << std::endl;
        return false;
    }

    Map::environmentRows = 0;
    std::string line;
    while (getline(file, line) && Map::environmentRows < MAX_ROWS) {

        Map::environmentCols = line.size();
        for (int col = 0; col < Map::environmentCols && col < MAX_COLS; ++col) {
            Map::environment[Map::environmentRows][col] = line[col];
        }
        for (int col = Map::environmentCols; col < MAX_COLS; ++col) {
            Map::environment[Map::environmentRows][col] = ' ';
        }
        ++(Map::environmentRows);
    }
    file.close();
    return true;
}
sf::Texture Map::loadTexture(const std::string& fileName) {
    sf::Texture texture;
    if (!texture.loadFromFile(fileName)) {
        std::cout << "Error: Could not load texture " << fileName << std::endl;
    }
    return texture;
}
void  Map::drawMap(sf::RenderWindow& window) {
    sf::RectangleShape wall(sf::Vector2f(Map::WALL_SIZE, Map::WALL_SIZE));
    sf::Texture wallTexture = loadTexture("Graphics/outer_border.png");
    wall.setTexture(&wallTexture);

    for (int i = 0; i < Map::environmentRows; i++) {
        for (int j = 0; j < Map::environmentCols; j++) {
            if (Map::environment[i][j] == 'x') {
                wall.setPosition(j * Map::GRID_SIZE, i * Map::GRID_SIZE);
                window.draw(wall);
            }
        }
    }
}
