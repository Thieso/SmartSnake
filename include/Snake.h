#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std; 

class Snake {
    private: 
        vector<sf::RectangleShape> elements; // elements of the snake
        vector<sf::Vector2f> newPos;         // new positions of the elements after moving
        unsigned int length;                 // length of the snake
        sf::RenderWindow* win;               // window to draw in
        unsigned const int xSize = 20;       // size of each element in x direction
        unsigned const int ySize = 20;       // size of each element in y direction
        const int step = 20;                 // step size of the snake

    public: 
        Snake(sf::RenderWindow*); 
        ~Snake(); 
        unsigned int getLength(); 
        sf::Vector2f getHead(); 
        void addElement(); 
        void moveSnake(const int, const int); 
        int checkCollision(); 
};
