#include "include/Snake.h"

// constructor
Snake::Snake() {
    // initialize parameters
    xDirection = 1;
    yDirection = 0;
    length = 1;
    elements.resize(length);
    // set initial position in the middle of the field
    elements[0].setPosition(sf::Vector2f(int(x / 2), int(y / 2)));
    // set inital position of the food
    this->setFood();
}

void Snake::reset() {
    // reinitialize parameters
    xDirection = 1;
    yDirection = 0;
    length = 1;
    elements.resize(length);
    // set initial position in the middle of the field
    elements[0].setPosition(sf::Vector2f(int(x / 2), int(y / 2)));
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

// move the snake
void Snake::moveSnake(){
    // move everything but the head
    for (int i = length; i > 0; i--){
        elements[i].setPosition(elements[i-1].getPosition());
    }
    // move the head
    elements[0].move(xDirection, yDirection);
}

// check for collisions in the snake itself or with the wall of the given
// position on the grid
// return 1 if a collision is there, otherwise return zero
int Snake::checkCollision(sf::Vector2f pos) {
    // compare the position of the head with the position of each element and if
    // the coincide there is a collision
    for (unsigned int i = 1; i < length; i++){
        if (pos == elements[i].getPosition()){
            return 1;
        }
    }

    // check for collision of the head with the wall
    if (pos.x > x - 1 || pos.x < 0 || pos.y > y - 1 || pos.y < 0){
        return 1;
    }
    return 0;
}

// return drawing shape for the snake body element with given idx
sf::RectangleShape Snake::getSnakeDrawingShape(int xSize, int ySize, int idx) {
    sf::Vector2f pos;
    sf::RectangleShape drawingShape;
    // set size and color of element
    // position
    pos = elements[idx].getPosition();
    drawingShape.setPosition(sf::Vector2f(pos.x * xSize, pos.y * ySize));
    drawingShape.setSize(sf::Vector2f(xSize, ySize));
    // color (color of head is different from the rest)
    if (idx > 0){
        drawingShape.setFillColor(sf::Color(0, 255, 0));
    } else {
        drawingShape.setFillColor(sf::Color(0, 0, 255));
    }
    return drawingShape;
}

// return drawable shape of the food
sf::RectangleShape Snake::getFoodDrawingShape(int xSize, int ySize) {
    sf::RectangleShape drawingShape;
    sf::Vector2f pos;

    // set position, color, and size of shape
    pos = food.getPosition();
    drawingShape.setPosition(sf::Vector2f(pos.x * xSize, pos.y * ySize));
    drawingShape.setFillColor(sf::Color(255, 0, 0));
    drawingShape.setSize(sf::Vector2f(xSize, ySize));

    // return the shape
    return drawingShape;
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
    random_device rd;
    uniform_int_distribution<int> distributionX(0, x - 1);
    uniform_int_distribution<int> distributionY(0, y - 1);
    int randX, randY;

    // set position such that the food is never on the body of the snake
    bool badPosition = true;
    while (badPosition) {
        // set position randomly
        randX = distributionX(rd);
        randY = distributionY(rd);
        food.setPosition(sf::Vector2f(randX, randY));
        // check if the position is on the snake body
        badPosition = false;
        for (unsigned int i = 0; i < length; i++){
            if (food.getPosition() == elements[i].getPosition()){
                badPosition = true;
            }
        }
    }
}

// returns the inputs needed to train the neural network, the return vector
// contains information of the current game state
VectorXd Snake::getInputs() {
    // check which directions the snake can go from its current position and
    // which are blocked
    int front_blocked, left_blocked, right_blocked; 
    sf::Vector2f headPos = this->getHead();
    sf::Vector2f headPos_straight, headPos_left, headPos_right;
    headPos_straight = headPos + sf::Vector2f(xDirection, yDirection);
    if (xDirection != 0) {
        headPos_left = headPos + sf::Vector2f(0, -xDirection);
        headPos_right = headPos + sf::Vector2f(0, xDirection);
    } else if (yDirection != 0) {
        headPos_left = headPos + sf::Vector2f(yDirection, 0);
        headPos_right = headPos + sf::Vector2f(-yDirection, 0);
    }
    front_blocked = this->checkCollision(headPos_straight);
    left_blocked = this->checkCollision(headPos_left);
    right_blocked = this->checkCollision(headPos_right);

    // relative position of food to snake head
    sf::Vector2f foodPos = food.getPosition();
    sf::Vector2f relPos = foodPos - headPos;
    float normFactor = sqrt(relPos.x * relPos.x + relPos.y * relPos.y);

    // set input vector
    VectorXd inputs(7);
    // blocking information
    inputs(0) = front_blocked;
    inputs(1) = left_blocked;
    inputs(2) = right_blocked;
    // position of the food relative to position of the head (normalized)
    inputs(3) = relPos.x / normFactor;
    inputs(4) = relPos.y / normFactor;
    // direction of movement (normalized)
    inputs(5) = xDirection;
    inputs(6) = yDirection;

    return inputs;
}

// set direction of the snake
void Snake::setDirection(int x, int y) {
    xDirection = x;
    yDirection = y;
}
