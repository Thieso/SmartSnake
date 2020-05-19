#pragma once
#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Vector2d;

class Snake {
    private: 
        MatrixXd elements; // elements of the snake
        Vector2d food;             // food for the snake
        unsigned int length;                 // length of the snake
        unsigned const int x = 40;           // size of field in x
        unsigned const int y = 40;           // size of field in y
        Vector2d direction;                  // direction of movement in x

    public: 
        Snake(); 
        ~Snake(); 
        void reset(); 
        unsigned int getLength(); 
        Vector2d getHead(); 
        void addElement(); 
        void moveSnake(); 
        int checkCollision(Vector2d); 
        int checkFood();
        void setFood();
        VectorXd getInputs();
        void setDirection(Vector2d);
        sf::RectangleShape getFoodDrawingShape(int, int);
        sf::RectangleShape getSnakeDrawingShape(int, int, int);
};
