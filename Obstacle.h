#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Snake.h"
#include <iostream>

class Obstacle {
public:
    Obstacle();
    int directionX, directionY, x ,y ;
    sf::RectangleShape obstacle;
    sf::Texture obstcaleTexture;
    void loadtexture(std::string filename);
    void updateMovingObstacle(Snake snake);
    bool isPositionOnSnake(Snake s);
    void drawMovingObstacle(sf::RenderWindow& window);
};
