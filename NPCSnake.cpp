#include "NPCSnake.h"
#include <iostream>
#include "Map.h"

NPCSnake::NPCSnake() : Snake() { // Call the base class constructor
    this->snake_size = 5;

    // Random starting position for the head
    int startX = 400; // X coordinate for head
    int startY = 400; // Y coordinate for head

    // Initialize the vector for snake body
    p = std::vector<sf::Vector2i>();

    // Initialize the head and body segments
    p.push_back(sf::Vector2i(startX, startY)); // Head at (startX, startY)

    // Now add the body segments in a line, to the left of the head for example
    for (int i = 1; i < snake_size; ++i) {
        p.push_back(sf::Vector2i(startX - i * Map::GRID_SIZE, startY)); // Each body part behind the head
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    direction = rand() % 4; // 0 = left, 1 = right, 2 = up, 3 = down
    (this->headCircle).setFillColor(sf::Color::Red);
    (this->bodyCircle).setFillColor(sf::Color::Red);
}

bool NPCSnake::checkCollisionWithPlayer(Snake& player) {
    if (checkCollisionWithHead(player)) {
        return true;
    }

    for (size_t i = 1; i < player.p.size(); ++i) {
        if (checkCollisionWithBody(player, i)) {
            return true;
        }
    }

    return false;
}

bool NPCSnake::checkCollisionWithHead(Snake& player) {
    if (p[0] == player.getHeadPosition()) {
        return true;
    }
    return false;
}

bool NPCSnake::checkCollisionWithBody(Snake& player, size_t playerPartIndex) {
    if (p[0] == player.getBodyPart(playerPartIndex)) {
        return true;
    }
    return false;
}

void NPCSnake::moveRandomly(const Map& gameMap) {
    // Generate a random direction
    int newDirection = rand() % 4;

    // Update direction
    direction = newDirection;

    // Calculate the new position based on the direction
    sf::Vector2i newPosition = p[0]; // Assume p[0] is the head of the snake
    switch (direction) {
    case 0: newPosition.x -= Map::GRID_SIZE; break; // Move left
    case 1: newPosition.x += Map::GRID_SIZE; break; // Move right
    case 2: newPosition.y -= Map::GRID_SIZE; break; // Move up
    case 3: newPosition.y += Map::GRID_SIZE; break; // Move down
    }

    // Check for collisions with walls and boundaries
    if (newPosition.x >= 0 && newPosition.x < gameMap.environmentCols * Map::GRID_SIZE &&
        newPosition.y >= 0 && newPosition.y < gameMap.environmentRows * Map::GRID_SIZE &&
        !(Map::isPositionOnWall(newPosition.x, newPosition.y))) {

        // Move the snake to the new position if it's valid
        for (int i = snake_size - 1; i > 0; --i) {
            p[i] = p[i - 1]; // Shift the body positions
        }
        p[0] = newPosition; // Update the head position
    }
    else {
        // If the new position is invalid, pick another random direction next move
        direction = rand() % 4;
    }
}
