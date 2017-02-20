#include "Application.h"

Application::Application() 
{ 
}

Application::~Application() 
{ 
}

void Application::Run(int agrc, char* argv[])
{
	bool isRunning = Initialise(agrc, argv);
	while (isRunning == true)
	{
		isRunning = Update();
		isRunning = Draw();
	}
	Destroy();
}