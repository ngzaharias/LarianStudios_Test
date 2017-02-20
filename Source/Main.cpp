#include "Application.h"
#include "Game/GameApplication.h"

int main(int agrc, char* argv[])
{
	Application* game = new GameApplication();
	game->Run(agrc, argv);
	return 0;
}
//EOF