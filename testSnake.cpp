#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Snake.h"

using namespace std;

struct direction {
    int x;
    int y;
};

int main() {
    // define window 
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");

    // set size of the rectangles
    int xSize = 20;
    int ySize = 20;

    // create a new Snake object
    Snake snake;

    // create the direction struct with initial moving to the right
    struct direction dir;
    dir.x = 1;
    dir.y = 0;

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir.x == 0) {
            dir.x = -1;
            dir.y = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir.x == 0) {
            dir.x = 1;
            dir.y = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir.y == 0) {
            dir.x = 0;
            dir.y = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir.y == 0) {
            dir.x = 0;
            dir.y = 1;
        }

        // check for collision
        if (snake.checkCollision() == 1) {
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
            snake.setDirection(dir.x, dir.y);
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
