#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "include/Food.h"

using namespace std;

Food::Food(sf::RenderWindow* window) {
		win = window;

		rect.setSize(sf::Vector2f(xSize, ySize));
		rect.setFillColor(sf::Color(255, 0, 0));
}

Food::~Food() {
		delete win;
}

void Food::setPos(const int x, const int y) {
		rect.setPosition(sf::Vector2f(x, y));
}

void Food::drawFood() {
		win->draw(rect);
}
