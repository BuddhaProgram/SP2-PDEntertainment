#ifndef APPLICATION_H
#define APPLICATION_H

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

	static void OpenGame();
	static void SceneLevel1A();
	static void SceneLevel1B();
    static void SceneLevel2();
	static void FirstCutScene();
    static void StartingScene();
    static void EndingScene();

    static Scene *scene;
	static Scene *Opening;
	static Scene *Start;
	static Scene *LevelOneA;
    static Scene *LevelOneB;
    static Scene *LevelTwo;
	static Scene *End;
	static Scene *CutScene1;
private:

	//Declare a window object
	StopWatch m_timer;
};

#endif