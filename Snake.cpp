#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "include/Snake.h"

using namespace std;

// constructor
Snake::Snake(sf::RenderWindow* window) {
    // initialize parameters
    length = 1;
    win = window;
    elements.resize(length);
    elements[0].setSize(sf::Vector2f(xSize, ySize));
    elements[0].setFillColor(sf::Color(0, 0, 255));
    newPos.resize(length-1);
}

// destructor
Snake::~Snake() {
    delete win;
}

// returns the length of the snake
unsigned int Snake::getLength(){
    return length;
}

// adds an element to the snake
void Snake::addElement(){
    length += 1;
    elements.resize(length);
    elements[length-1].setSize(sf::Vector2f(xSize, ySize));
    elements[length-1].setFillColor(sf::Color(0, 255, 0));
    newPos.resize(length-1);
}

// move the snake in direction x and y
void Snake::moveSnake(const int x, const int y){
    // get window size
    sf::Vector2u winSize = win->getSize();

    // set the new position of the elements by setting it to the previous
    // position of the element before it (works for all element except the
    // head)
    for (int i = 0; i < length-1; i++){
        sf::Vector2f prevPos = elements[i].getPosition();
        newPos[i] = prevPos;
    }


    // move the head
    elements[0].move(x * step, y * step);
    // get position of the head
    sf::Vector2f headPos = elements[0].getPosition();
    // get size of the head
    sf::Vector2f headSize = elements[0].getSize();

    // move through the wall and appear at the other side if necessary
    if (headPos.x + headSize.x > winSize.x && x == 1){
        elements[0].setPosition(0, headPos.y);
    }
    if (headPos.x < 0 && x == -1) {
        elements[0].setPosition(winSize.x - headSize.x, headPos.y);
    }
    if (headPos.y + headSize.y > winSize.y && y == 1) {
        elements[0].setPosition(headPos.x, 0);
    }
    if (headPos.y < 0 && y == -1) {
        elements[0].setPosition(headPos.x, winSize.y - headSize.y);
    }

    // draw the head
    win->draw(elements[0]);

    // draw the elements
    for (int i = 0; i < length - 1; i++){
        elements[i+1].setPosition(newPos[i]);
        win->draw(elements[i+1]);
    }
}

// return the position of the head of the snake
sf::Vector2f Snake::getHead() {
    return elements[0].getPosition();
}

// check for collisions in the snake itself
// return 1 if a collision is there, otherwise return zero
int Snake::checkCollision() {
    // compare the position of the head with the position of each element and if
    // the coincide there is a collision
    for (int i = 1; i < length; i++){
        if (elements[0].getPosition() == elements[i].getPosition()){
            return 1;
        }
    }
    return 0;
}
