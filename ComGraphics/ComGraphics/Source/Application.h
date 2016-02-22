#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "GlobalVariables.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static int mouse_scroll;
private:

	//Declare a window object
	StopWatch m_timer;
	GlobalVariables Variables;
};

#endif