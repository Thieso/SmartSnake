#pragma once
#include <eigen3/Eigen/Dense>
#include <vector>
#include <random>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd;

class Snake {
    private: 
        vector<sf::RectangleShape> elements; // elements of the snake
        sf::RectangleShape food;             // food for the snake
        unsigned int length;                 // length of the snake
        unsigned const int x = 40;           // size of field in x
        unsigned const int y = 40;           // size of field in y
        int xDirection;                      // direction of movement in x
        int yDirection;                      // direction of movement in y

    public: 
        Snake(); 
        ~Snake(); 
        void reset(); 
        unsigned int getLength(); 
        sf::Vector2f getHead(); 
        void addElement(); 
        void moveSnake(); 
        int checkCollision(sf::Vector2f); 
        int checkFood();
        void setFood();
        sf::RectangleShape getSnakeDrawingShape(int, int, int);
        sf::RectangleShape getFoodDrawingShape(int, int);
        VectorXd getInputs();
        void setDirection(int, int);
};
