#ifndef SCREEN_H
#define SCREEN_H

namespace sf
{
	class RenderWindow;
}

class Screen
{
public:
	static int width;
	static int height;

private:
	static sf::RenderWindow* s_window;

public:
	static sf::RenderWindow* GetWindow();
	static void SetWindow(sf::RenderWindow* window);

};

#endif