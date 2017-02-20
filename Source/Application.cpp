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
	while (isRunning == true && m_isForceQuitting == false)
	{
		isRunning = Update();
		isRunning = Draw();
	}
	Destroy();
}

void Application::Quit()
{
	m_isForceQuitting = true;
}