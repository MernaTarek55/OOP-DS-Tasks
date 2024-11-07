#include "Collectable.h"
#include "Snake.h"
#include "Game.h"
#include <iostream>

Collectable::Collectable()
{
    collectable.setSize(sf::Vector2f(Map::GRID_SIZE, Map::GRID_SIZE));
    collectable.setPosition(randomX, randomY);
}
void Collectable::loadtexture(std::string filename) {
    if (!collectableTexture.loadFromFile(filename)) {
        // Handle texture loading error
        std::cout << "Error loading texture" << std::endl;
    }
    collectable.setTexture(&collectableTexture);
}
void Collectable::randomizeCollectablePosition(Snake s)
{

    do {
        randomX = Map::GRID_SIZE * (rand() % (Game::windowWidth / Map::GRID_SIZE));
        randomY = Map::GRID_SIZE * (rand() % (Game::windowHeight / Map::GRID_SIZE));
    } while (isPositionOnSnake(s) || Game::isPositionOnWall(randomX, randomY));

    collectable.setPosition(static_cast<float>(randomX), static_cast<float>(randomY));
}
bool Collectable::isPositionOnSnake(Snake s) {
    for (int i = 1; i < s.snake_size; i++) {
        if (s.p[i].x == randomX && s.p[i].y == randomY) {
            return true;
        }
    }
    return false;
}
bool Collectable::collideWithSnake(Snake snake) {
    if (snake.p[0].x == randomX && snake.p[0].y == randomY) {
        randomizeCollectablePosition(snake);
        return true;
    }
    else return false;
}