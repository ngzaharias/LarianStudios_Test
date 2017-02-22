#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderWindow;
	class Window;
}

class Screen
{
public:
	static sf::RenderWindow* GetWindow();
	static void SetWindow(sf::RenderWindow* window);
	static sf::Vector2i AdjustToFullscreenPosition(const sf::Window& window, sf::Vector2i position);

public:
	static unsigned int width;
	static unsigned int height;

private:
	static sf::RenderWindow* s_window;

};
#endif