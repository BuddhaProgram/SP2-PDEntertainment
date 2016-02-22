#include "Application.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneStart.h"
#include "SceneEnd.h"
#include "CutSceneOne.h"



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

Scene* Application::scene;
Scene* Application::Start;
Scene* Application::End;
Scene* Application::LevelOneA;
Scene* Application::LevelOneB;
Scene* Application::CutScene1;

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
	//m_window = glfwCreateWindow(1920, 1080, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);
	//m_window = glfwCreateWindow(1920, 1080, "Computer Graphics", NULL, NULL);
	m_window = glfwCreateWindow(800, 600, "Computer Graphics", NULL, NULL);
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
	Start = new SceneStart();
	Start->Init();
    CutScene1 = new CutSceneOne();
    CutScene1->Init();
	LevelOneA = new SceneLevelOneA();
	LevelOneA->Init();
    LevelOneB = new SceneLevelOneB();
    LevelOneB->Init();
	//Main Loop
	//SceneStart *scene = new SceneStart();
	//scene->Init();
	scene = Start;
	

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
	delete Start;
	delete End;
	delete CutScene1;
    delete LevelOneA;
    delete LevelOneB;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::StartingScene()
{
    scene = Start;
}

void Application::FirstCutScene()
{
    scene = CutScene1;
}
void Application::SceneLevel1A()
{
	scene = LevelOneA;
}

void Application::SceneLevel1B()
{
	scene = LevelOneB;
}

void Application::EndingScene()
{
    scene = End;
}