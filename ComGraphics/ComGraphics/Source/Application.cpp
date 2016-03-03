#include "Application.h"


//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneOpening.h"
#include "SceneStart.h"
#include "SceneEnd.h"
#include "CutSceneOne.h"
#include "SceneLevelOneA.h"
#include "SceneLevelOneB.h"
#include "SceneLevelTwo.h"
#include "OpeningCutScene.h"
#include "OpeningCutScene2.h"
#include "SceneEndCutScene.h"
#include "Credits.h"




const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
GLFWwindow* m_window;
int Application::mouse_scroll = 0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{

}

Application::~Application()
{
}
Music* Application::musics;

Scene* Application::scene;
Scene* Application::IntroScene;
Scene* Application::IntroScene2;
Scene* Application::Opening;
Scene* Application::Start;
Scene* Application::End;
Scene* Application::LevelOneA;
Scene* Application::LevelOneB;
Scene* Application::LevelTwo;
Scene* Application::CutScene1;
Scene* Application::EndScene;
Scene* Application::EndCredits;

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

void scroll_callback(GLFWwindow *m_window, double xoffset, double yoffset)
{
	Application::mouse_scroll = (int)yoffset;
}

void Application::Init()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context

	m_window = glfwCreateWindow(1920, 1080, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);


	//m_window = glfwCreateWindow(1920, 1080, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);

	//m_window = glfwCreateWindow(1920, 1080, "Computer Graphics", NULL, NULL);
   // m_window = glfwCreateWindow(800, 600, "Computer Graphics", NULL, NULL);
	glfwSetScrollCallback(m_window, scroll_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	glfwSetWindowSizeCallback(m_window, resize_callback);

	//Set the error callback
	glfwSetErrorCallback(error_callback);
}

void Application::Run()
{
	musics = new Music();
	musics->init();

	Opening = new SceneOpening();
	IntroScene = new OpeningCutScene();
	IntroScene2 = new OpeningCutScene2();
	Start = new SceneStart();
    CutScene1 = new CutSceneOne();
	LevelOneA = new SceneLevelOneA();
    LevelOneB = new SceneLevelOneB();
    LevelTwo = new SceneLevelTwo();
	End = new SceneEnd();
	EndScene = new SceneEndCutScene();
	EndCredits = new Credits();


	scene = LevelOneB;
	scene->Init();


	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);

		if (Application::IsKeyPressed(WM_MOUSEWHEEL))
			glfwSetScrollCallback(m_window, scroll_callback);

		else
			Application::mouse_scroll = 0;

		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();

	delete musics;
	delete IntroScene;
	delete IntroScene2;
	delete Opening;
	delete Start;
	delete End;
	delete CutScene1;
    delete LevelOneA;
    delete LevelOneB;
	delete EndScene;
	delete EndCredits;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	glfwWindowShouldClose(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
	exit(EXIT_FAILURE);
}

void Application::OpenGame()
{
	scene = Opening;
	scene->Init();
}

void Application::StartingScene()
{
    scene = Start;
	scene->Init();
}

void Application::FirstCutScene()
{
    scene = CutScene1;
	scene->Init();
}
void Application::SceneLevel1A()
{
	scene = LevelOneA;
	scene->Init();
}

void Application::SceneLevel1B()
{
	scene = LevelOneB;
	scene->Init();
}

void Application::SceneLevel2()
{
    scene = LevelTwo;
	scene->Init();
}

void Application::EndingScene()
{
    scene = End;
	scene->Init();
}

void Application::OpenCutScene()
{
	scene = IntroScene;
	scene->Init();
}

void Application::OpenCutScene2()
{
	scene = IntroScene2;
	scene->Init();
}

void Application::EndingCutScene()
{
	scene = EndScene;
	scene->Init();
}

void Application::End_Credits()
{
	scene = EndCredits;
	scene->Init();
}

void Application::MusicWillPlay(int index, bool loop)
{
	musics->OpeningMusic(index, loop);
}

void Application::DropOneMusic(int index)
{
	musics->BackGround[index]->drop();
	musics->BackGround[index] = 0;
}