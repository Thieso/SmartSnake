#include "include/Snake.h"

// constructor
Snake::Snake() {
    // initialize parameters
    length = 1;
    elements.resize(length);
    // set initial position in the middle of the field
    elements[0].setPosition(sf::Vector2f(12, 12));
    // set inital position of the food
    this->setFood();
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

    // check for collision of the head with the wall
    sf::Vector2f headPos = elements[0].getPosition();
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
        drawingShape.setSize(sf::Vector2f(xSize, ySize));
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
    drawingShape.setSize(sf::Vector2f(xSize, ySize));
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
    // initialize random number generator
    srand(time(NULL));
    int randX, randY;

    // set position such that the food is never on the body of the snake
    bool badPosition = true;
    while (badPosition) {
        // set position randomly
        randX = rand() % (this->x);
        randY = rand() % (this->y);
        food.setPosition(sf::Vector2f(randX, randY));
        // check if the position is on the snake body
        badPosition = false;
        for (int i = 0; i < length; i++){
            if (food.getPosition() == elements[i].getPosition()){
                badPosition = true;
            }
        }
    }
}
