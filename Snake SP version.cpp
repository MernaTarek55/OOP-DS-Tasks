#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;
using namespace sf;
int game = 0, dir = 0, speed = 100, snake_size = 1, score = 0;
int randomx = 0, randomy = 0;
int rx = 0, ry = 0;
int scorex = 0, scorey = 0;
const int MAX_ROWS = 30, MAX_COLS = 40;
char environment[MAX_ROWS][MAX_COLS];
const int GRID_SIZE = 20;
const int WALL_SIZE = 20;
int environmentRows = 0;
int environmentCols = 0;
int windowWidth = 800, windowHeight = 600;
struct Point {
    int x = 0;
    int y = 0;
} p[100];


bool isPositionOnSnake(int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        if (p[i].x == x && p[i].y == y) {
            return true;
        }
    }
    return false;
}

bool isPositionOnWall(int x, int y) {
    int gridX = x / GRID_SIZE;
    int gridY = y / GRID_SIZE;

    if (gridX >= 0 && gridX < environmentCols && gridY >= 0 && gridY < environmentRows) {

        if (environment[gridY][gridX] == 'x') {
            return true;
        }
    }
    return false;

}

Texture loadTexture(const string& fileName) {
    Texture texture;
    if (!texture.loadFromFile(fileName)) {
        cerr << "Error: Could not load texture " << fileName << endl;
    }
    return texture;
}

bool readFile(char environment[MAX_ROWS][MAX_COLS], int& rows, int& cols, const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    rows = 0;
    string line;
    while (getline(file, line) && rows < MAX_ROWS) {

        cols = line.size();
        for (int col = 0; col < cols && col < MAX_COLS; ++col) {
            environment[rows][col] = line[col];
        }
        for (int col = cols; col < MAX_COLS; ++col) {
            environment[rows][col] = ' ';
        }
        ++rows;
    }
    file.close();
    return true;
}
void makeTheWalls(RenderWindow& window, int windowWidth, int windowHeight) {

    RectangleShape wall(Vector2f(WALL_SIZE, WALL_SIZE));
    Texture wallTexture = loadTexture("Graphics/outer_border.png");
    //wall.setFillColor(Color(255, 0, 0));
    wall.setTexture(&wallTexture);

    for (int i = 0; i < environmentRows; i++) {
        for (int j = 0; j < environmentCols; j++) {
            if (environment[i][j] == 'x') {
                wall.setPosition(j * GRID_SIZE, i * GRID_SIZE);
                window.draw(wall);

            }
        }
    }
}
void randomizColectable(int& x, int& y) {
    while (isPositionOnSnake(x, y, snake_size) || isPositionOnWall(x, y)) {
        x = GRID_SIZE * (rand() % (windowWidth / GRID_SIZE));
        y = GRID_SIZE * (rand() % (windowHeight / GRID_SIZE));
    }
}
void resetGame() {
    // Reset all game variables to their initial state
    string fileName = "walls.txt";

    if (!readFile(environment, environmentRows, environmentCols, fileName)) {
        return;
    }
    for (int i = 0; i < environmentRows; i++) {
        for (int j = 0; j < environmentCols; j++) {
            cout << environment[i][j];
        }
        cout << endl;
    }

    game = 0;
    dir = 0;
    speed = 200;
    snake_size = 2;
    score = 0;
    p[0] = { GRID_SIZE, GRID_SIZE }; // Initial position

    randomizColectable(randomx, randomy);
    randomizColectable(rx, ry);
    randomizColectable(scorex, scorey);


}
struct Obstacle {
    int x;
    int y;
    int directionX;
    int directionY;
};

Obstacle movingObstacle = { GRID_SIZE * 5, GRID_SIZE * 5, 1, 1 }; // Initial position and direction

void updateMovingObstacle() {
    movingObstacle.x += movingObstacle.directionX * GRID_SIZE;
    movingObstacle.y += movingObstacle.directionY * GRID_SIZE;

    if (movingObstacle.x < 0 || movingObstacle.x >= windowWidth) {
        movingObstacle.directionX = -movingObstacle.directionX;
    }
    if (movingObstacle.y < 0 || movingObstacle.y >= windowHeight) {
        movingObstacle.directionY = -movingObstacle.directionY;
    }

    if (isPositionOnWall(movingObstacle.x, movingObstacle.y)) {
        movingObstacle.directionX = -movingObstacle.directionX;
        movingObstacle.directionY = -movingObstacle.directionY;
    }

    if (isPositionOnSnake(movingObstacle.x, movingObstacle.y, snake_size)) {

        game = 0;
    }
}

void drawMovingObstacle(RenderWindow& window, RectangleShape& obstacleShape) {
    obstacleShape.setPosition(movingObstacle.x, movingObstacle.y);
    window.draw(obstacleShape);
}
int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Snake Game", sf::Style::Default, settings);
    Event event;

    // Load textures
    Texture squaret;
    if (!squaret.loadFromFile("Graphics/apple.png")) {
        std::cerr << "Error loading apple.png" << std::endl;
        return -1;
    }

    // load snake textures
    Texture currentHead;
    Texture headTextures[4] = {
        loadTexture("Graphics/head_right.png"),
        loadTexture("Graphics/head_left.png"),
        loadTexture("Graphics/head_down.png"),
        loadTexture("Graphics/head_up.png")
    };
    Texture currentBody;
    Texture bodyTextures[10] = {
        loadTexture("Graphics/body_vertical.png"),      // 0
        loadTexture("Graphics/body_horizontal.png"),    // 1
        loadTexture("Graphics/body_bottomleft.png"),    // 2
        loadTexture("Graphics/body_bottomright.png"),   // 3
        loadTexture("Graphics/body_topleft.png"),       // 4
        loadTexture("Graphics/body_topright.png"),      // 5
        loadTexture("Graphics/tail_down.png"),          // 6
        loadTexture("Graphics/tail_left.png"),          // 7
        loadTexture("Graphics/tail_right.png"), 	    // 8
        loadTexture("Graphics/tail_up.png"),			// 9
    };

    RectangleShape headCircle(Vector2f(20, 20)); // Circle for the head
    //headCircle.setFillColor(Color(58, 116, 28)); // Head color

    RectangleShape bodyCircle(Vector2f(20, 20)); // Circle for the body
    //bodyCircle.setFillColor(Color(88, 245, 5)); // Body color

    RectangleShape obstacleShape(Vector2f(20, 20));
    Texture obstacleTex = loadTexture("Graphics/outer_border.png");
    obstacleShape.setTexture(&obstacleTex);

    RectangleShape poison(Vector2f(20, 20)); // Rectangle for the poison
    Texture poisonTex = loadTexture("Graphics/poison.png");
    poison.setTexture(&poisonTex);
    //poison.setFillColor(Color(0, 255, 0));
    RectangleShape coin(Vector2f(20, 20));
    Texture coinTex = loadTexture("Graphics/coin.png");
    coin.setTexture(&coinTex);
    //coin.setFillColor(Color(53, 250, 127));
    RectangleShape apple(Vector2f(20, 20)); // Rectangle for the food
    Texture appleTex = loadTexture("Graphics/apple.png");
    apple.setTexture(&appleTex);
    //apple.setFillColor(Color(150, 70, 210));
    srand(static_cast<unsigned>(time(NULL)));
    resetGame();

    // Load font
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    // Create menu text
    Text startText("Press Enter to Start", font, 30);
    startText.setFillColor(Color::White);
    startText.setPosition(180, 200);

    Text exitText("Press Esc to Exit", font, 30);
    exitText.setFillColor(Color::White);
    exitText.setPosition(210, 250);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (game == 0) {
                    if (event.key.code == Keyboard::Enter) {
                        resetGame();
                        game = 1;// Restart game from the beginning
                    }
                    else if (event.key.code == Keyboard::Escape) {
                        window.close(); // Exit the game
                    }
                }
                else if (game == 1) {
                    if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D && dir != 1) dir = 0;
                    else if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A && dir != 0) dir = 1;
                    else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S && dir != 3) dir = 2;
                    else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W && dir != 2) dir = 3;
                }
            }
        }

        window.clear(Color(0, 0, 0));
        Texture bg = loadTexture("Graphics/background.png");
        RectangleShape background(Vector2f(windowWidth, windowHeight));
        background.setTexture(&bg);
        window.draw(background);

        if (game == 0) {
            // Display main menu
        mainmenu:
            window.draw(startText);
            window.draw(exitText);
            window.display();

        }
        else if (game == 1) {

            // Gameplay logic
            updateMovingObstacle();
            drawMovingObstacle(window, obstacleShape);
            for (int i = snake_size; i > 0; i--) {
                p[i] = p[i - 1];
            }
            if (dir == 0) {
                p[0].x += 20;
                currentHead = headTextures[0];
                currentHead.setRepeated(false);
            }
            if (dir == 1) {
                p[0].x -= 20;
                currentHead = headTextures[1];
                currentHead.setRepeated(false);
            }
            if (dir == 2) {
                p[0].y += 20;
                currentHead = headTextures[2];
                currentHead.setRepeated(false);
            }
            if (dir == 3) {
                p[0].y -= 20;
                currentHead = headTextures[3];
                currentHead.setRepeated(false);
            }
            if (isPositionOnWall(p[0].x, p[0].y)) {
                game = 0; // Game over, return to menu
                goto mainmenu;
            }

            makeTheWalls(window, windowWidth, windowHeight);
            for (int i = 1; i < snake_size; i++) {
                if (p[0].x == p[i].x && p[0].y == p[i].y) {
                    game = 0; // Game over, return to menu
                }
            }

            if (p[0].x == randomx && p[0].y == randomy) {
                snake_size++;
                if (speed > 100) speed -= 20;
                score++;
                randomizColectable(randomx, randomy);
            }



            if (p[0].x == scorex && p[0].y == scorey) {
                score += 10;

                randomizColectable(scorex, scorey);
            }

            if (p[0].x == rx && p[0].y == ry) {
                snake_size = std::max(2, snake_size / 2);

                randomizColectable(rx, ry);
            }

            Text scoreText("Score : " + std::to_string(score), font, 18);
            scoreText.setFillColor(Color::White);
            scoreText.setPosition(5, 10);
            window.draw(scoreText);
            // Draw red food
            apple.setPosition(randomx, randomy);
            window.draw(apple);

            // Draw poison food
            poison.setPosition(rx, ry);
            window.draw(poison);

            coin.setPosition(scorex, scorey);
            window.draw(coin);
            // Draw snake with the head in a different color
            headCircle.setPosition(p[0].x, p[0].y);
            headCircle.setTexture(&currentHead);
            window.draw(headCircle);

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

            window.display();
            sf::sleep(sf::milliseconds(speed));
        }
    }
    return 0;
}
