#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
	Application();
	virtual ~Application();

	void Run(int agrc, char* argv[]);
	void Quit();

protected:
	virtual bool Initialise(int agrc, char* argv[]) = 0;
	virtual void Destroy() = 0;

	virtual bool Update() = 0;
	virtual bool Draw() = 0;

protected:
	bool m_isForceQuitting = false;
};
#endif

