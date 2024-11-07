#pragma once
#include "Map.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "NPCSnake.h"
#include "Collectable.h"
#include "Obstacle.h"
#include "NPCSnake.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

class Game
{
public:
    // Constructor
    Game();
    static int game ;
    
    // Public methods
    void startGame();

    // Static members
    static int windowWidth, windowHeight;

    // Public members
    
    static bool isPositionOnWall(int x , int y);
    void update();
    void render();
    void updateMainMenu();
    void renderMainMenu();
    void ListenToEvents();
    void resetGame();
    void creatBG();
    void gameLoop();
private:
    // Private members
    sf::RectangleShape background;
    sf::RenderWindow window;
    sf::ContextSettings settings;
    Map gameMap;
    sf::Text startText;
    sf::Text exitText;
    sf::Texture bgTex;
    sf::Font font;
    sf::Event event;
    Snake* snake;
    NPCSnake npcSnake;
    Collectable apple;
    Collectable coin;
    Collectable poison;
    Obstacle obstacle;
};