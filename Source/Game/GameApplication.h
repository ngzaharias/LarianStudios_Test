#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "Application.h"

namespace sf
{
	class RenderWindow;
}

class GameApplication : public Application
{
public:
	GameApplication();
	virtual ~GameApplication() override;

protected:
	virtual bool Initialise(int agrc, char* argv[]) override;
	virtual void Destroy() override;

	virtual bool Update() override;
	virtual bool Draw() override;

protected:
	sf::RenderWindow* m_window;
};
#endif
//EOF