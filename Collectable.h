#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Snake.h"
#include <iostream>
class Game;
class Collectable {
public:
    Collectable();
    int randomX, randomY;
    sf::RectangleShape collectable;
    sf::Texture collectableTexture;
    void draw(sf::RenderWindow& window) {
        window.draw(collectable);
    }
    void loadtexture(std::string filename);
    void randomizeCollectablePosition(Snake s);
    bool isPositionOnSnake(Snake s);
    
    bool collideWithSnake(Snake snake);
};
