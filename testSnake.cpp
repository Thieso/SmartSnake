#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Snake.h"

using namespace std;
using Eigen::Vector2d;

int main() {
    // define window 
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake");

    // set size of the rectangles
    int xSize = 20;
    int ySize = 20;

    // create a new Snake object
    Snake snake;

    // create initial direction
    random_device rd;
    uniform_int_distribution<int> distribution(1, 4);
    int int_dir = distribution(rd);
    Vector2d dir;
    if (int_dir == 1)
        dir << 1, 0;
    else if (int_dir == 2)
        dir << -1, 0;
    else if (int_dir == 3)
        dir << 0, 1;
    else if (int_dir == 4)
        dir << 0, -1;
    snake.setDirection(dir);

    // set framerate
    window.setFramerateLimit(30);

    // set speed
    int speed = 50;

    // create clock
    sf::Clock clock;

    // var for game over
    int gameOver = 0;

    // run program as long as the window is open
    while (window.isOpen() && gameOver == 0) {
        sf::Event event;
        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // get keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir(0) == 0) {
            dir(0) = -1;
            dir(1) = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir(0) == 0) {
            dir(0) = 1;
            dir(1) = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir(1) == 0) {
            dir(0) = 0;
            dir(1) = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir(1) == 0) {
            dir(0) = 0;
            dir(1) = 1;
        }

        // check for collision
        if (snake.checkCollision(snake.getHead()) == 1) {
            gameOver = 1;
        }
        
        // check if the food got eaten, if so set food to new location and grow
        // the snake
        if (snake.checkFood() == 1) {
            snake.addElement();
            snake.setFood();
        }

        // if a certain time elapsed, move and draw the snake
        if (clock.getElapsedTime().asMilliseconds() >= speed){
            window.clear();
            clock.restart();
            snake.setDirection(dir);
            snake.moveSnake();
            // get food location and draw the food
            sf::RectangleShape drawingShape = snake.getFoodDrawingShape(xSize, ySize);
            window.draw(drawingShape);
            // get snake location and draw it
            for (int i = 0; i < snake.getLength(); i++) {
                drawingShape = snake.getSnakeDrawingShape(xSize, ySize, i);
                window.draw(drawingShape);
            }
        }

        // Display all the changes on the screen
        window.display();
    }
    return 0;
}
