#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/GA.h"
#include "include/Individual.h"

using namespace std;

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(500, 500), "Snake");

int main(){
    GA* ga = new GA();
    ga->evaluate_fitness();
    ga->show_game(window, 0);

    return 0;
}
