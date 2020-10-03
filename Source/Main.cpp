#include "Application.h"
#include "Game/GameApplication.h"

#include <direct.h>

Application* application = nullptr;

int main(int agrc, char* argv[])
{
	_chdir("../../");

	application = new GameApplication();
	application->Run(agrc, argv);
	delete(application);
	application = nullptr;

	return 0;
}

