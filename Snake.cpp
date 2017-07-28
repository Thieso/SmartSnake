#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "include/Snake.h"

using namespace std;

Snake::Snake(sf::RenderWindow* window) {
		length = 1;
		win = window;
		elements.resize(length);
		elements[0].setSize(sf::Vector2f(xSize, ySize));
		elements[0].setFillColor(sf::Color(0, 0, 255));
		newPos.resize(length-1);
}

Snake::~Snake() {
		delete win;
}

unsigned int Snake::getLength(){
		return length;
}
void Snake::addElement(){
		length += 1;
		elements.resize(length);
		elements[length-1].setSize(sf::Vector2f(xSize, ySize));
		elements[length-1].setFillColor(sf::Color(0, 255, 0));
		newPos.resize(length-1);

}


void Snake::moveSnake(const int x, const int y){
		// get window size
		sf::Vector2u winSize = win->getSize();

		//DEBUG
		//cout << "x = " << x << " y = " << y << endl;

		for (int i = 1; i < length; i++){
				sf::Vector2f prevPos = elements[i-1].getPosition();
				newPos[i-1] = prevPos;
		}

		for (int i = 0; i < length - 1; i++){

				elements[i+1].setPosition(newPos[i]);
				//DEBUG
				//cout << "Drawing element " << i+1 << " at " << newPos[i].x << " " <<  newPos[i].y << endl;

				win->draw(elements[i]);
		}


		// move the head
		elements[0].move(x * step, y*step);
		// check if it is within the window
		sf::Vector2f headPos = elements[0].getPosition();
		sf::Vector2f headSize = elements[0].getSize();

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

		// Draw the head
		win->draw(elements[0]);
		//DEBUG
		//headPos = elements[0].getPosition();
		//cout << "Drawing head "<< " at " << headPos.x << " " <<  headPos.y << endl;
}

sf::Vector2f Snake::getHead() {
		return elements[0].getPosition();
}

int Snake::checkCollision() {
		for (int i = 1; i < length; i++){
				if (elements[0].getPosition() == elements[i].getPosition()){
						return 1;
				}
		}
		return 0;
}
