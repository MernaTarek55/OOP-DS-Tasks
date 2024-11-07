
#include "Obstacle.h"
#include "Game.h"


Obstacle::Obstacle()
{
	x = Map::GRID_SIZE * 5;
	y = Map::GRID_SIZE * 5;
    directionX = 1;
    directionY = 1;
    obstacle.setSize(sf::Vector2f(Map::GRID_SIZE, Map::GRID_SIZE));
    obstacle.setPosition(0, 0);
}

void Obstacle::loadtexture(std::string filename)
{
    if (!obstcaleTexture.loadFromFile(filename)) {
        // Handle texture loading error
        std::cout << "Error loading texture" << std::endl;
    }
    obstacle.setTexture(&obstcaleTexture);
}

void Obstacle::updateMovingObstacle(Snake snake)
{
    x += directionX * Map::GRID_SIZE;
    y += directionY * Map::GRID_SIZE;

    if (x < 0 || x >= Game::windowWidth) {
        directionX = -directionX;
    }
    if (y < 0 || y >= Game::windowHeight) {
        directionY = -directionY;
    }

    if (Game::isPositionOnWall(x, y)) {
        directionX = -directionX;
        directionX = -directionY;
    }

    if (isPositionOnSnake(snake)) {
        Game::game = 0; // Game over if obstacle hits the snake
    }
}
bool Obstacle::isPositionOnSnake(Snake s) {
    for (int i = 1; i < s.snake_size; i++) {
        if (s.p[i].x == directionX && s.p[i].y == directionY) {
            return true;
        }
    }
    return false;
}
void Obstacle::drawMovingObstacle(sf::RenderWindow& window) {
    obstacle.setPosition(x, y);
    window.draw(obstacle);
}
