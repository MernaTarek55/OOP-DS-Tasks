#include "Game.h"
#include "Obstacle.h"
#include "Collectable.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
// Static member initialization
int Game::windowWidth = 800;
int Game::windowHeight = 600;
int Game::game = 0;

// Constructor
Game::Game()
{

    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    creatBG();
}
void Game::creatBG() {
    if (!bgTex.loadFromFile("Graphics/background.png")) {
        std::cout << "Error loading textures!" << std::endl;
        return ;
    }
    background.setSize(sf::Vector2f(Game::windowWidth, Game::windowHeight)); 
    background.setTexture(&bgTex);
}
void Game::startGame() {
    gameMap.drawMap(window);
}

bool Game::isPositionOnWall(int x , int y) {
    int gridX = x / Map::GRID_SIZE;
    int gridY = y / Map::GRID_SIZE;

    if (gridX >= 0 && gridX < Map::environmentCols && gridY >= 0 && gridY < Map::environmentRows) {
        if (Map::environment[gridY][gridX] == 'x') {
            return true;
        }
    }
    return false;
}


void Game::update( ) {
    npcSnake.moveRandomly(gameMap);
    obstacle.updateMovingObstacle(*snake);
    snake->movesnake();
    snake->checkInput(window);

    if (Game::isPositionOnWall(snake->p[0].x, snake->p[0].y)) {
        game = 0; // Game over, return to menu
    }

    if (npcSnake.checkCollisionWithPlayer(*snake)) {
        std::cout << "Player collided with NPC Snake!" << std::endl;
        snake->zombisnake(window);
    }

    if (snake->zombi) {
        snake->resetZombiStatus();
    }

    for (int i = 1; i < snake->snake_size; i++) {
        if (snake->p[0] == snake->p[i]) {
            game = 0; // Game over, return to menu
        }
    }

    // Handle collectibles
    if (apple.collideWithSnake(*snake)) {
        snake->snake_size++;
        snake->p.push_back((snake->p.back()) + (snake->p[snake->p.size() - 1] - snake->p[snake->p.size() - 2]));
        if (snake->speed > 100) snake->speed -= 20;
        snake->score++;
    }

    if (coin.collideWithSnake(*snake)) {
        snake->score += 10;
    }

    if (poison.collideWithSnake(*snake)) {
        snake->snake_size = std::max(2, snake->snake_size / 2);
        while (snake->p.size() > snake->snake_size) {
            snake->p.pop_back();
        }
    }
    
}

void Game::render() {
    
    window.clear(sf::Color::Black);
    window.draw(background);
    // Draw game map and obstacles
    gameMap.drawMap(window);
    obstacle.drawMovingObstacle(window);

    // Draw NPC snake
    npcSnake.sethead(window);
    npcSnake.drawSnake(window);

    // Draw collectibles
    apple.draw(window);
    poison.draw(window);
    coin.draw(window);

    // Draw score
    sf::Text scoreText("Score: " + std::to_string(snake->score), font, 18);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(5, 10);
    window.draw(scoreText);

    // Draw player snake
    window.draw(snake->headCircle);
    snake->drawSnake(window);

    window.display();
    sf::sleep(sf::milliseconds(snake->speed));
}
void Game::updateMainMenu() {
    
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
        return ;
    }
    startText.setString("Press Enter to Start");
    startText.setFont(font);
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(180, 200);

    exitText.setString("Press Esc to Exit");
    exitText.setFont(font);
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(210, 250);
}
void Game::renderMainMenu() {
    window.draw(background);
    window.draw(startText);
    window.draw(exitText);
    window.display();
}
void Game::ListenToEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (Game::game == 0) {
                if (event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    Game::game = 1; // Start the game
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    window.close(); // Exit the game
                }
            }
            else if (Game::game == 1) {
                // Handle snake movement direction
                if (event.key.code == sf::Keyboard::Right && snake->direction != 1) {
                    snake->direction = 0;
                    if (snake->zombi) {
                        snake->direction = 1;
                    }
                }
                else if (event.key.code == sf::Keyboard::Left && snake->direction != 0) {
                    snake->direction = 1;
                    if (snake->zombi) {
                        snake->direction = 0;
                    }
                }
                else if (event.key.code == sf::Keyboard::Down && snake->direction != 3) {
                    snake->direction = 2;
                    if (snake->zombi) {
                        snake->direction = 3;
                    }
                }
                else if (event.key.code == sf::Keyboard::Up && snake->direction != 2)
                {
                    snake->direction = 3;
                    if (snake->zombi) {
                        snake->direction = 2;
                    }
                }

            }
        }
    }
}
void Game::resetGame() {
    creatBG();
    if (!gameMap.ReadFile()) {
        std::cout << "Failed to read map file!" << std::endl;
        return;
    }
    snake = new Snake();
    Game::game = 0;
    snake->direction = 0;
    snake->speed = 200;
    //snake.snake_size = 1;
    snake->score = 0;
    //snake.p[0] = { Map::GRID_SIZE, Map::GRID_SIZE }; // Initial position
    apple.loadtexture("Graphics/apple.png");
    coin.loadtexture("Graphics/coin.png");
    poison.loadtexture("Graphics/poison.png");
    obstacle.loadtexture("Graphics/outer_border.png");
    apple.randomizeCollectablePosition(*snake);
    coin.randomizeCollectablePosition(*snake);
    poison.randomizeCollectablePosition(*snake);
}

void Game::gameLoop() {
    
    updateMainMenu();
    srand(static_cast<unsigned>(time(NULL)));
    //resetGame();
    resetGame();
    window.clear(sf::Color::Black);
    window.draw(background);
    while (window.isOpen()) {
        ListenToEvents();

        if (Game::game == 0) {
        mainmenu:
            renderMainMenu();
        }
        else if (Game::game == 1) {
            update();
            if (Game::game == 0)goto mainmenu;
            render();
        }
    }

}