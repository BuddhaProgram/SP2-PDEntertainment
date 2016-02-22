#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "Scene.h"
#include "GlobalVariables.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//memory leak checks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
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

	static void SceneOne();
	static void SceneTwo();
	static void FirstCutScene();

	static Scene *scene;
	static Scene *sceneOne;
	static Scene *sceneTwo;
	static Scene *CutScene1;
private:

	//Declare a window object
	StopWatch m_timer;
	GlobalVariables Variables;
};

#endif