#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <string>
#include "Map.h" 

class Snake
{
public:
    std::vector<sf::Vector2i> p;  // Single vector to represent the snake's body
    int snake_size;
    int direction;
    sf::RectangleShape headCircle;
    sf::RectangleShape bodyCircle;
    int speed = 200;
    int score = 0;
    // Textures
    sf::Texture currentHead;
    sf::Texture headTextures[4];
    sf::Texture currentBody;
    sf::Texture bodyTextures[10];
    sf::Clock clock;
    // Private method to load textures
    void setTextures();
    bool zombi = false;

    // Constructor
    Snake();
    void drawSnake(sf::RenderWindow& window);
    bool isPositionOnSnake();
    void movesnake();
    void checkInput(sf::RenderWindow& window);
    void sethead(sf::RenderWindow& window);
    sf::Vector2i getBodyPart(int index);
    sf::Vector2i getHeadPosition();
    void zombisnake(sf::RenderWindow& window);
    void resetZombiStatus();
};
