#include "Snake.h"
#include "Map.h" 
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

Snake::Snake()
    : snake_size(2), direction(0)
{
    p.push_back(sf::Vector2i(Map::GRID_SIZE, Map::GRID_SIZE));
    p.push_back(sf::Vector2i(Map::GRID_SIZE - Map::GRID_SIZE, Map::GRID_SIZE - Map::GRID_SIZE));

    headCircle.setSize(sf::Vector2f(Map::GRID_SIZE, Map::GRID_SIZE));

    bodyCircle.setSize(sf::Vector2f(Map::GRID_SIZE, Map::GRID_SIZE));

    setTextures();
}

void Snake::drawSnake(sf::RenderWindow& window)
{
    for (int i = 1; i < snake_size; i++) {
#pragma region Snake Texture Setting
        if (i == snake_size - 1) {
            if (p[i].x == p[i - 1].x - 20)
                currentBody = bodyTextures[7];
            else if (p[i].x == p[i - 1].x + 20)
                currentBody = bodyTextures[8];
            else if (p[i].y == p[i - 1].y - 20)
                currentBody = bodyTextures[9];
            else if (p[i].y == p[i - 1].y + 20)
                currentBody = bodyTextures[6];
        }
        else {
            if (p[i].x == p[i - 1].x - 20) {
                if (p[i].y == p[i + 1].y - 20)
                    currentBody = bodyTextures[3];
                else if (p[i].y == p[i + 1].y + 20)
                    currentBody = bodyTextures[5];
                else
                    currentBody = bodyTextures[1];
            }
            else if (p[i].x == p[i - 1].x + 20) {
                if (p[i].y == p[i + 1].y - 20)
                    currentBody = bodyTextures[2];
                else if (p[i].y == p[i + 1].y + 20)
                    currentBody = bodyTextures[4];
                else
                    currentBody = bodyTextures[1];
            }
            else if (p[i].y == p[i - 1].y - 20) {
                if (p[i].x == p[i + 1].x - 20)
                    currentBody = bodyTextures[3];
                else if (p[i].x == p[i + 1].x + 20)
                    currentBody = bodyTextures[2];
                else
                    currentBody = bodyTextures[0];
            }
            else if (p[i].y == p[i - 1].y + 20) {
                if (p[i].x == p[i + 1].x - 20)
                    currentBody = bodyTextures[5];
                else if (p[i].x == p[i + 1].x + 20)
                    currentBody = bodyTextures[4];
                else
                    currentBody = bodyTextures[0];
            }
        }
#pragma endregion
        currentBody.setSmooth(true);
        currentBody.setRepeated(false);
        currentBody.setSrgb(true);
        bodyCircle.setTexture(&currentBody);
        bodyCircle.setPosition(p[i].x, p[i].y);

        window.draw(bodyCircle);
    }
}

void Snake::setTextures() {
    // Load head textures
    if (!headTextures[0].loadFromFile("Graphics/head_right.png") ||
        !headTextures[1].loadFromFile("Graphics/head_left.png") ||
        !headTextures[2].loadFromFile("Graphics/head_down.png") ||
        !headTextures[3].loadFromFile("Graphics/head_up.png")) {
        std::cout << "Error loading snake head textures!" << std::endl;
    }

    if (!bodyTextures[0].loadFromFile("Graphics/body_vertical.png") ||
        !bodyTextures[1].loadFromFile("Graphics/body_horizontal.png") ||
        !bodyTextures[2].loadFromFile("Graphics/body_bottomleft.png") ||
        !bodyTextures[3].loadFromFile("Graphics/body_bottomright.png") ||
        !bodyTextures[4].loadFromFile("Graphics/body_topleft.png") ||
        !bodyTextures[5].loadFromFile("Graphics/body_topright.png") ||
        !bodyTextures[6].loadFromFile("Graphics/tail_down.png") ||
        !bodyTextures[7].loadFromFile("Graphics/tail_left.png") ||
        !bodyTextures[8].loadFromFile("Graphics/tail_right.png") ||
        !bodyTextures[9].loadFromFile("Graphics/tail_up.png")) {
        std::cout << "Error loading snake body textures!" << std::endl;

    }
}

bool Snake::isPositionOnSnake() {
    for (int i = 1; i < this->snake_size; i++) {
        if (p[i].x == p[0].x && p[i].y == p[0].y) {
            return true;
        }
    }
    return false;
}


void Snake::movesnake()
{
    for (int i = snake_size - 1; i > 0; i--) {
        p[i] = p[i - 1];
    }
}

void Snake::checkInput(sf::RenderWindow& window)
{
    if (direction == 0) {
        p[0].x += 20;
        currentHead = headTextures[0];
        currentHead.setRepeated(false);
    }
    if (direction == 1) {
        p[0].x -= 20;
        currentHead = headTextures[1];
        currentHead.setRepeated(false);
    }
    if (direction == 2) {
        p[0].y += 20;
        currentHead = headTextures[2];
        currentHead.setRepeated(false);
    }
    if (direction == 3) {
        p[0].y -= 20;
        currentHead = headTextures[3];
        currentHead.setRepeated(false);
    }
    sethead(window);

}
void Snake::sethead(sf::RenderWindow& window) {
    headCircle.setPosition(p[0].x, p[0].y);
    headCircle.setTexture(&currentHead);
    window.draw(headCircle);
}
sf::Vector2i Snake::getHeadPosition() {
    return p[0];
}

void Snake::zombisnake(sf::RenderWindow& window)
{
    (this->headCircle).setFillColor(sf::Color::Red);
    (this->bodyCircle).setFillColor(sf::Color::Red);
    zombi = true;
    speed = 100;
    clock.restart();
}
void Snake::resetZombiStatus() {
    // Check if 5 seconds have passed
    if (clock.getElapsedTime().asSeconds() >= 10) {
        zombi = false; 
        headCircle.setFillColor(sf::Color::White);
        bodyCircle.setFillColor(sf::Color::White);
        speed = 200;

    }
}
// Accessor function for a specific body part
sf::Vector2i Snake::getBodyPart(int index) {
    return p[index];
}