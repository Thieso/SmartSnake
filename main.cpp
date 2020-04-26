#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Snake.h"
#include "include/Food.h"

using namespace std;


void drawMatrix(sf::RenderWindow*, int, int);

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(500, 500), "Snake");

struct direction {
    int x;
    int y;
};

int main(){
    // set size of the rectangles
    int xSize = 20;
    int ySize = 20;

    // create a new Snake object
    Snake* snake = new Snake();


    // create the direction struct with initial moving to the right
    struct direction dir;
    dir.x = 1;
    dir.y = 0;

    // set framerate
    window->setFramerateLimit(30);

    // set speed
    int speed = 50;

    // create clock
    sf::Clock clock;

    // var for game over
    int gameOver = 0;

    // run program as long as the window is open
    while (window->isOpen() && gameOver == 0) {
        sf::Event event;


        while(window->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
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
        if (snake->checkCollision() == 1) {
            gameOver = 1;
        }
        
        // check if the food got eaten, if so set food to new location and grow
        // the snake
        if (snake->checkFood() == 1) {
            snake->addElement();
            snake->setFood();
        }

        // if a certain time elapsed, move and draw the snake
        if (clock.getElapsedTime().asMilliseconds() >= speed){
            window->clear();
            clock.restart();
            snake->moveSnake(dir.x, dir. y);
            snake->drawSnake(window, xSize, ySize);
        }

        // draw a Matrix
        drawMatrix(window, xSize, ySize);

        // Display all the changes on the screen
        window->display();
    }


    return 0;
}

void drawMatrix(sf::RenderWindow* window, int xSize, int ySize) {
    // color of matrix lines
    int grey = 50;
    sf::Color color(grey, grey, grey);

    // get window size
    sf::Vector2u wSize = window->getSize();

    // draw matrix
    for (int i = xSize; i < wSize.x; i += xSize) {
        sf::Vertex lineV[] =
        {
            sf::Vertex(sf::Vector2f(i, 0), color),
            sf::Vertex(sf::Vector2f(i, wSize.x), color)
        };
        window->draw(lineV, 2, sf::Lines);
    }
    for (int i = ySize; i < wSize.y; i += ySize) {
        sf::Vertex lineH[] =
        {
            sf::Vertex(sf::Vector2f(0, i), color),
            sf::Vertex(sf::Vector2f(wSize.y, i),color)
        };
        window->draw(lineH, 2, sf::Lines);
    }
}
