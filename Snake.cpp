#include "include/Snake.h"

// constructor
Snake::Snake() {
    // initialize parameters
    length = 1;
    elements.resize(length);
    // set initial position in the middle of the field
    elements[0].setPosition(sf::Vector2f(12, 12));
}

// destructor
Snake::~Snake() {
}

// returns the length of the snake
unsigned int Snake::getLength(){
    return length;
}

// adds an element to the snake
void Snake::addElement(){
    length += 1;
    elements.resize(length);
    //elements[length-1].setSize(sf::Vector2f(xSize, ySize));
    //elements[length-1].setFillColor(sf::Color(0, 255, 0));
}

// move the snake in direction x and y
void Snake::moveSnake(const int x, const int y){
    // move everything but the head
    for (int i = length; i > 0; i--){
        elements[i].setPosition(elements[i-1].getPosition());
    }
    // move the head
    elements[0].move(x, y);
}

// check for collisions in the snake itself or with the wall
// return 1 if a collision is there, otherwise return zero
int Snake::checkCollision() {
    // compare the position of the head with the position of each element and if
    // the coincide there is a collision
    for (int i = 1; i < length; i++){
        if (elements[0].getPosition() == elements[i].getPosition()){
            return 1;
        }
    }

    // get position of the head
    sf::Vector2f headPos = elements[0].getPosition();
    // get size of the head
    sf::Vector2f headSize = elements[0].getSize();

    // check for collision with the wall
    if (headPos.x > x || headPos.x < 0 || headPos.y > y || headPos.y < 0){
        return 1;
    }
    return 0;
}

// draw snake on the screen
void Snake::drawSnake(sf::RenderWindow* win, int xSize, int ySize) {
    sf::Vector2f pos;
    sf::RectangleShape drawingShape;
    // set size and color of elements and draw it
    for (int i = 0; i < length; i++){
        // position
        pos = elements[i].getPosition();
        drawingShape.setPosition(sf::Vector2f(pos.x * xSize, pos.y * ySize));
        // color (color of head is different from the rest)
        if (i > 0){
            drawingShape.setFillColor(sf::Color(0, 255, 0));
        } else {
            drawingShape.setFillColor(sf::Color(0, 0, 255));
        }
        win->draw(drawingShape);
    }
    // set size and color of food and draw it
    pos = food.getPosition();
    drawingShape.setPosition(sf::Vector2f(pos.x * xSize, pos.y * ySize));
    drawingShape.setFillColor(sf::Color(255, 0, 0));
    win->draw(drawingShape);
}

// return the position of the head of the snake
sf::Vector2f Snake::getHead() {
    return elements[0].getPosition();
}

// checks wheter or not the snake is eating the food
// returns 1 if it is eating, otherwise 0
int Snake::checkFood() {
    if (elements[0].getPosition() == food.getPosition())
        return 1;
    return 0;
}

void Snake::setFood() {
    // generate random number
    srand(time(NULL));
    int randX = rand() % x;
    int randY = rand() % y;

    // set position of food
    food.setPosition(sf::Vector2f(randX, randY));
}
