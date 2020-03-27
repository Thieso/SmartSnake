#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std; 

class Food{
		private: 
				sf::RenderWindow* win; 
				sf::RectangleShape rect; 
				unsigned const int xSize = 20; 
				unsigned const int ySize = 20; 

		public: 
				Food(sf::RenderWindow*); 
				~Food(); 
				void setPos(const int, const int); 
				void drawFood(); 
};
