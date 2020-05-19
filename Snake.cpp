#include "include/Snake.h"

// constructor
Snake::Snake() {
    // initialize parameters
    direction << 1, 0;
    length = 1;
    elements.resize(2, length);
    // set initial position in the middle of the field
    Vector2d initialPos((int) x / 2, (int) y / 2);
    elements.col(0) = initialPos;
    // set inital position of the food
    this->setFood();
}

void Snake::reset() {
    // reinitialize parameters
    direction << 1, 0;
    length = 1;
    elements.resize(2, length);
    // set initial position in the middle of the field
    Vector2d initialPos((int) x / 2, (int) y / 2);
    elements.col(0) = initialPos;
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
    // resize the matrix holding the elements (old_element matrix is necessary
    // since a resizing deletes the components of a matrix)
    MatrixXd old_elements(elements);
    elements.resize(2, length);
    elements.leftCols(length - 1) = old_elements;
}

// move the snake
void Snake::moveSnake(){
    // move everything but the head
    for (int i = length - 1; i > 0; i--){
        elements.col(i) = elements.col(i - 1);
    }
    // move the head
    elements.col(0) = elements.col(0) + direction;
}

// check for collisions in the snake itself or with the wall of the given
// position on the grid
// return 1 if a collision is there, otherwise return zero
int Snake::checkCollision(Vector2d pos) {
    // compare the position of the head with the position of each element and if
    // the coincide there is a collision
    for (unsigned int i = 1; i < length; i++){
        if (pos == elements.col(i)){
            return 1;
        }
    }

    // check for collision of the head with the wall
    if (pos(0) > x - 1 || pos(0) < 0 || pos(1) > y - 1 || pos(1) < 0){
        return 1;
    }
    return 0;
}

// return the position of the head of the snake
Vector2d Snake::getHead() {
    return (Vector2d) elements.col(0);
}

// checks wheter or not the snake is eating the food
// returns 1 if it is eating, otherwise 0
int Snake::checkFood() {
    if (elements.col(0) == food)
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
        food(0) = randX;
        food(1) = randY;
        // check if the position is on the snake body
        badPosition = false;
        for (unsigned int i = 0; i < length; i++){
            if (food == elements.col(0)){
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
    Vector2d headPos = this->getHead();
    Vector2d headPos_straight, headPos_left, headPos_right;
    headPos_straight = headPos + direction;
    if (direction(0) != 0) {
        headPos_left = headPos + Vector2d(0, -direction(0));
        headPos_right = headPos + Vector2d(0, direction(0));
    } else if (direction(1) != 0) {
        headPos_left = headPos + Vector2d(direction(1), 0);
        headPos_right = headPos + Vector2d(-direction(1), 0);
    }
    front_blocked = this->checkCollision(headPos_straight);
    left_blocked = this->checkCollision(headPos_left);
    right_blocked = this->checkCollision(headPos_right);

    // relative position of food to snake head
    Vector2d relPos = food - headPos;
    float normFactor = sqrt(relPos(0) * relPos(0) + relPos(1) * relPos(1));

    // set input vector
    VectorXd inputs(7);
    // blocking information
    inputs(0) = front_blocked;
    inputs(1) = left_blocked;
    inputs(2) = right_blocked;
    // position of the food relative to position of the head (normalized)
    inputs(3) = relPos(0) / normFactor;
    inputs(4) = relPos(1) / normFactor;
    // direction of movement (normalized)
    inputs(5) = direction(0);
    inputs(6) = direction(1);

    return inputs;
}

// set direction of the snake
void Snake::setDirection(Vector2d newDirection) {
    direction = newDirection;
}

// return drawing shape for the snake body element with given idx
sf::RectangleShape Snake::getSnakeDrawingShape(int xSize, int ySize, int idx) {
    sf::Vector2f pos;
    sf::RectangleShape drawingShape;
    // set size and color of element
    // position
    drawingShape.setPosition(sf::Vector2f(elements(0, idx) * xSize, elements(1, idx) * ySize));
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

    // set position, color, and size of shape
    drawingShape.setPosition(sf::Vector2f(food(0) * xSize, food(1) * ySize));
    drawingShape.setFillColor(sf::Color(255, 0, 0));
    drawingShape.setSize(sf::Vector2f(xSize, ySize));

    // return the shape
    return drawingShape;
}
