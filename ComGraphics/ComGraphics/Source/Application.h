#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "GlobalVariables.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
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