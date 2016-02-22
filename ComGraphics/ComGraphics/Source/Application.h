#ifndef APPLICATION_H
#define APPLICATION_H

#include "SceneLevelOneA.h"
#include "SceneLevelOneB.h"

#include "timer.h"
#include "Scene.h"
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

	static void SceneLevel1A();
	static void SceneLevel1B();
	static void FirstCutScene();
    static void StartingScene();
    static void EndingScene();

    static Scene *scene;
	static Scene *Start;
	static Scene *LevelOneA;
    static Scene *LevelOneB;
	static Scene *End;
	static Scene *CutScene1;
private:

	//Declare a window object
	StopWatch m_timer;
};

#endif