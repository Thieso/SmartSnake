#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std; 

class Snake {
		private: 
				vector<sf::RectangleShape> elements; 
				vector<sf::Vector2f> newPos; 
				unsigned int length; 
				sf::RenderWindow* win; 
				unsigned const int xSize = 20; 
				unsigned const int ySize = 20; 
				const int step = 20;

		public: 
				Snake(sf::RenderWindow*); 
				~Snake(); 
				unsigned int getLength(); 
				sf::Vector2f getHead(); 
				void addElement(); 
				void moveSnake(const int, const int); 
				int checkCollision(); 
};
