#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Snake.h"
#include "include/Food.h"

using namespace std;


void drawMatrix(sf::RenderWindow*);

sf::RenderWindow* window = new  sf::RenderWindow(sf::VideoMode(500, 500), "Snake");

struct direction {
    int x;
    int y;
};

int main(){

    // create a new Snake object
    Snake* snake = new Snake(window);


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

    // variable for food checking
    int avaiable = 0;

    // random location for food
    int randX, randY;

    // create the food
    Food* food = new Food(window);

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
        // if a certain time elapsed, move the snake
        if (clock.getElapsedTime().asMilliseconds() >= speed){
            window->clear();
            clock.restart();
            snake->moveSnake(dir.x, dir. y);
        }



        // place the food
        if (avaiable == 0){
            avaiable = 1;
            /* initialize random seed: */
            srand (time(NULL));


            // generate secret number between 1 and 10:
            randX = rand() % 24;
            randY = rand() % 24;
            randX *= 20;
            randY *= 20;

            food->setPos(randX, randY);
        }

        // check if food got eaten
        if (avaiable == 1 && snake->getHead() == sf::Vector2f(randX, randY)) {
            avaiable = 0;
            snake->addElement();
        }


        // check for collision
        if (snake->checkCollision() == 1) {
            gameOver = 1;
        }

        //DEBUG
        //sf::Vector2f h = snake->getHead();
        //cout << "snake at: x = " << h.x << " y = " << h.y << endl;
        //food

        // draw a Matrix
        drawMatrix(window);

        // draw the food
        food->drawFood();

        // Display all the changes on the screen
        window->display();
    }


    delete food;
    return 0;
}

void drawMatrix(sf::RenderWindow* window) {

    int grey = 50;
    bool x = true; 

    sf::Color color(grey, grey, grey);

    for (int i = 20; i < 800; i += 20){
        sf::Vertex lineV[] =
        {
            sf::Vertex(sf::Vector2f(i, 0), color),
            sf::Vertex(sf::Vector2f(i, 800), color)
        };
        window->draw(lineV, 2, sf::Lines);
        sf::Vertex lineH[] =
        {
            sf::Vertex(sf::Vector2f(0, i), color),
            sf::Vertex(sf::Vector2f(800, i),color)
        };
        window->draw(lineH, 2, sf::Lines);
    }
}
