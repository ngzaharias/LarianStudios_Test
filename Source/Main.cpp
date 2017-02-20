#include "Application.h"
#include "Game/GameApplication.h"

Application* application = nullptr;

int main(int agrc, char* argv[])
{
	application = new GameApplication();
	application->Run(agrc, argv);
	return 0;
}
//EOF