#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main(int agrc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Color colour(255, 0, 0, 255);
	sf::Vector2f size(200.0f, 80.0f);
	sf::RectangleShape rectangle(size);
	rectangle.setFillColor(colour);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(rectangle);
		window.display();
	}

	return 0;
}