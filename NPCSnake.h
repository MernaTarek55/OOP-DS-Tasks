#pragma once
#include "Snake.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class NPCSnake : public Snake {
public:
    
    NPCSnake();

    void moveRandomly(const Map& gameMap);
    bool checkCollisionWithPlayer(Snake& player);
    bool checkCollisionWithHead( Snake& player);
    bool checkCollisionWithBody( Snake& player, size_t playerPartIndex);
};