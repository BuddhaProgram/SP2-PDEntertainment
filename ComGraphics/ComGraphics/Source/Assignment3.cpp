#include "Assignment3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "LoadTGA.h"
#include "Utility.h"
#include <sstream>


Assignment3::Assignment3()
{
}

Assignment3::~Assignment3()
{
}

void Assignment3::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(37.5, 35, 100);
	light[0].color.Set(1, 1, 1);
	light[0].power = 3.0;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.0f, 1.0f, 0.0f);

	// Pass information
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	//Initialize camera settings
	camera.Init(Vector3(0, 10, 0), Vector3(1, 10, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

    meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
    meshList[GEO_FRONT]->textureID = LoadTGA("Image//SkyBox1_front.tga");
    meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
    meshList[GEO_LEFT]->textureID = LoadTGA("Image//SkyBox1_left.tga");
    meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
    meshList[GEO_RIGHT]->textureID = LoadTGA("Image//SkyBox1_right.tga");
    meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
    meshList[GEO_TOP]->textureID = LoadTGA("Image//SkyBox1_up.tga");
    meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("SkyBox1_down", Color(1, 1, 1));
    meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//SkyBox1_down.tga");
    meshList[GEO_BACK] = MeshBuilder::GenerateQuad("SkyBox1_back", Color(1, 1, 1));
    meshList[GEO_BACK]->textureID = LoadTGA("Image//SkyBox1_back.tga");

	meshList[GEO_PICKAXE] = MeshBuilder::GenerateOBJ("Pickaxe", "OBJ//Pickaxe.obj");
	meshList[GEO_PICKAXE]->textureID = LoadTGA("Image//Pickaxe.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_EARTH] = MeshBuilder::GenerateOBJ("Earth", "OBJ//Earth.obj");
	meshList[GEO_EARTH]->textureID = LoadTGA("Image//Earth.tga");
	meshList[GEO_MOON] = MeshBuilder::GenerateOBJ("Moon", "OBJ//Moon.obj");
	meshList[GEO_MOON]->textureID = LoadTGA("Image//Moon.tga");
	meshList[GEO_PLANET] = MeshBuilder::GenerateOBJ("Planet", "OBJ//Planet.obj");
	meshList[GEO_PLANET]->textureID = LoadTGA("Image//Planet.tga");
	meshList[GEO_ASTEROID1] = MeshBuilder::GenerateOBJ("Asteroid1", "OBJ//Asteroid1.obj");
	meshList[GEO_ASTEROID1]->textureID = LoadTGA("Image//Asteroid1.tga");
	meshList[GEO_ASTEROID2] = MeshBuilder::GenerateOBJ("Asteroid2", "OBJ//Asteroid2.obj");
	meshList[GEO_ASTEROID2]->textureID = LoadTGA("Image//Asteroid1.tga");

	meshList[GEO_MAINDOORLEFT] = MeshBuilder::GenerateOBJ("MainDoorLeft", "OBJ//MDLeft.obj");
	meshList[GEO_MAINDOORRIGHT] = MeshBuilder::GenerateOBJ("MainDoorRight", "OBJ//MDRight.obj");
	meshList[GEO_RUBBLE] = MeshBuilder::GenerateOBJ("Rubble", "OBJ//Rubble.obj");
	meshList[GEO_PORTRAIT] = MeshBuilder::GenerateOBJ("Portrait", "OBJ//Portrait.obj");
	meshList[GEO_PORTRAIT]->textureID = LoadTGA("Image//Scream.tga");

    meshList[GEO_GHOST1] = MeshBuilder::GenerateOBJ("ghost placeholder", "OBJ//GhostPlaceholder.obj");
    meshList[GEO_GHOST1]->textureID = LoadTGA("Image//Ghostplaceholder.tga");


	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

    //scene changer inits.............
    numScene = 1;
    //scene changer init end.............

    //ghost test variables
    Ghost1X = 0;
    Ghost1Y = 6;
    Ghost1Z = 15;
    SpawnGhost = false;

    TargetDetectX = 0;
    TargetDetectZ = 0;
    timeCount = 0;
	SlotIndex = 1;
}

static float LSPEED = 10.f;

float RotateX = 0.0f;
bool b_LockSwing = false;
bool b_LockSwingDebounce = false;
bool start_Animation = false;

void Assignment3::checkTarget()
{
    TargetDetectX = camera.position.x;
    TargetDetectZ = camera.position.z;
}

void Assignment3::Reset()
{
}

void Assignment3::Update(double dt)
{
	FPS = 1.f / (float)dt;
	if (Application::IsKeyPressed('J'))
	{
		Inventory.SlotOne = ToolUI(ToolUI::Pickaxe);
	}
	
	if (Application::IsKeyPressed(VK_LBUTTON) && b_LockSwing == false && b_LockSwingDebounce == false && PlayerStat::instance()->stamina>=20)
	{
		b_LockSwing = true;
		b_LockSwingDebounce = true;
		PlayerStat::instance()->stamina-=20;
	}

	if (b_LockSwingDebounce == true)
	{
		RotateX -= 180.0f * (float)dt;

		if (RotateX <= -45.0f)
		{
			RotateX = -45.0f;
			b_LockSwingDebounce = false;
		}
	}

	if (b_LockSwingDebounce == false && b_LockSwing == true && RotateX <= 0.0f)
	{
		RotateX += 180.0f * (float)dt;

		if (RotateX >= 0.0f)
		{
			RotateX = 0.0f;
			b_LockSwing = false;
		}
	}

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode


	camera.Update(dt);

	anima.Collapsing(dt);
	anima.OBJAnimation(dt);
	anima.OpenMainDoor(dt);
	if (camera.position.z <= -1 && camera.position.x <= 1 && camera.position.x >= -1)
	{
		start_Animation = true;
	}

	if (start_Animation)
	{
		anima.Portraits(dt);
	}


	//Reset();

    //scene changer codes..............
    if (Application::IsKeyPressed('P'))
    {
        numScene = 2;
    }
    if (Application::IsKeyPressed('O'))
    {
        numScene = 1;
    }
    //scenechanger end.................

    //jumpscare test
    if (Application::IsKeyPressed('J'))
    {
        SpawnGhost = true;
    }

    if (SpawnGhost)
    {
        moveGhost(dt);
    }
}

void Assignment3::RenderMesh(Mesh*mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();

		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load materials
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Assignment3::RenderScene1()
{
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -500);
    modelStack.Scale(10, 10, 10);
	modelStack.Rotate(anima.PlanetRotate, 0, 1, 0);
    RenderMesh(meshList[GEO_EARTH], false); // Earth
    modelStack.PushMatrix();
    modelStack.Translate(10, 0, 0);
	modelStack.Rotate(anima.PlanetRotate, 0, 1, 0);
    RenderMesh(meshList[GEO_MOON], false); // Moon
    modelStack.PopMatrix();
    modelStack.PopMatrix();


    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 50);
	modelStack.Rotate(anima.PlanetRotate, 0, 1, 0);
    RenderMesh(meshList[GEO_PLANET], false); // Planet
    modelStack.PopMatrix();

    //Asteroids
    modelStack.PushMatrix();
    modelStack.Translate(anima.AsteroidMove - 50, 0, 0);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID1], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(anima.AsteroidMove, 6, anima.AsteroidMove + 10);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID1], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(0, -anima.AsteroidMove, anima.AsteroidMove + 10);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID1], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(0, anima.AsteroidMoveS + 23, anima.AsteroidMoveS - 56);
	modelStack.Rotate(anima.AsteroidRotateF, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID1], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMove, -anima.AsteroidMove, 0);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID2], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMoveS, anima.AsteroidMoveS, anima.AsteroidMoveS);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID2], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMoveS, -anima.AsteroidMoveS + 40, anima.AsteroidMoveS - 36);
	modelStack.Rotate(anima.AsteroidRotateF, 0, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID2], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(anima.AsteroidMoveS, anima.AsteroidMoveS + 32, -anima.AsteroidMoveS - 98);
	modelStack.Rotate(anima.AsteroidRotateF, 1, 0, 1);
    RenderMesh(meshList[GEO_ASTEROID2], false);
    modelStack.PopMatrix();
    modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMoveS - 36, 0, anima.AsteroidMoveS + 11);
	modelStack.Rotate(anima.AsteroidRotateF, 0, 1, 0);
    RenderMesh(meshList[GEO_ASTEROID2], false);
    modelStack.PopMatrix();


    //skybox..................................................................................
    modelStack.PushMatrix();//skybox start
    modelStack.Scale(500, 500, 500);


    //front
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -10);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_FRONT], false);
    modelStack.PopMatrix();

    //right
    modelStack.PushMatrix();
    modelStack.Translate(10, 0, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_RIGHT], false);
    modelStack.PopMatrix();

    //left
    modelStack.PushMatrix();
    modelStack.Translate(-10, 0, 0);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_LEFT], false);
    modelStack.PopMatrix();

    //back
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 10);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_BACK], false);
    modelStack.PopMatrix();

    //bottom
    modelStack.PushMatrix();
    modelStack.Translate(0, -10, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_BOTTOM], false);
    modelStack.PopMatrix();

    //top
    modelStack.PushMatrix();
    modelStack.Translate(0, 10, 0);
    modelStack.Rotate(180, 0, 0, 1);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_TOP], false);
    modelStack.PopMatrix();

    modelStack.PopMatrix();//skybox end

}

void Assignment3::RenderScene2()
{


	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -500);
	modelStack.Scale(10, 10, 10);
	modelStack.Rotate(anima.PlanetRotate, 0, 1, 0);
	RenderMesh(meshList[GEO_EARTH], false); // Earth
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 0);
	modelStack.Rotate(anima.PlanetRotate, 0, 1, 0);
	RenderMesh(meshList[GEO_MOON], false); // Moon
	modelStack.PopMatrix();
	modelStack.PopMatrix();


    //skybox..................................................................................
    modelStack.PushMatrix();//skybox start
    modelStack.Scale(500, 500, 500);


    //front
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -10);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_FRONT], false);
    modelStack.PopMatrix();

    //right
    modelStack.PushMatrix();
    modelStack.Translate(10, 0, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_RIGHT], false);
    modelStack.PopMatrix();

    //left
    modelStack.PushMatrix();
    modelStack.Translate(-10, 0, 0);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_LEFT], false);
    modelStack.PopMatrix();

    //back
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 10);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_BACK], false);
    modelStack.PopMatrix();

    //bottom
    modelStack.PushMatrix();
    modelStack.Translate(0, -10, 0);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_BOTTOM], false);
    modelStack.PopMatrix();

    //top
    modelStack.PushMatrix();
    modelStack.Translate(0, 10, 0);
    modelStack.Rotate(180, 0, 0, 1);
    modelStack.Scale(20, 0, 20);
    RenderMesh(meshList[GEO_TOP], false);
    modelStack.PopMatrix();

    modelStack.PopMatrix();//skybox end


	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 50);
	modelStack.Rotate(anima.PlanetRotate, 0, 1, 0);
	RenderMesh(meshList[GEO_PLANET], false); // Planet
	modelStack.PopMatrix();

	//Asteroids
	modelStack.PushMatrix();
	modelStack.Translate(anima.AsteroidMove - 50, 0, 0);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID1], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(anima.AsteroidMove, 6, anima.AsteroidMove + 10);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID1], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, -anima.AsteroidMove, anima.AsteroidMove + 10);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID1], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, anima.AsteroidMoveS + 23, anima.AsteroidMoveS - 56);
	modelStack.Rotate(anima.AsteroidRotateF, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMove, -anima.AsteroidMove, 0);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID2], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMoveS, anima.AsteroidMoveS, anima.AsteroidMoveS);
	modelStack.Rotate(anima.AsteroidRotate, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID2], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMoveS, -anima.AsteroidMoveS + 40, anima.AsteroidMoveS - 36);
	modelStack.Rotate(anima.AsteroidRotateF, 0, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID2], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(anima.AsteroidMoveS, anima.AsteroidMoveS + 32, -anima.AsteroidMoveS - 98);
	modelStack.Rotate(anima.AsteroidRotateF, 1, 0, 1);
	RenderMesh(meshList[GEO_ASTEROID2], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-anima.AsteroidMoveS - 36, 0, anima.AsteroidMoveS + 11);
	modelStack.Rotate(anima.AsteroidRotateF, 0, 1, 0);
	RenderMesh(meshList[GEO_ASTEROID2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 0);
	modelStack.Rotate(anima.OpenDoorL, 0, 1, 0);
	RenderMesh(meshList[GEO_MAINDOORLEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, 0);
	modelStack.Rotate(anima.OpenDoorR, 0, 1, 0);
	RenderMesh(meshList[GEO_MAINDOORRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.RubbleCollapse, 0);
	modelStack.Translate(0, 10, -2);
	RenderMesh(meshList[GEO_RUBBLE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.PortraitDrop, 0);
	modelStack.Translate(0, 5, -20);
	modelStack.Rotate(anima.PortraitFall, 1, 0, 0);
	RenderMesh(meshList[GEO_PORTRAIT], false);
	modelStack.PopMatrix();


}

void Assignment3::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

}

void Assignment3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderModelOnScreen(Mesh* mesh, float size, float Rotate, float x, float y, float z)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -50, 50); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, z);
	modelStack.Rotate(Rotate, 1, 0, 0);

	RenderMesh(mesh, true);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment3::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	modelStack.LoadIdentity();

	// Light Source 1
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}


	if (Inventory.GetToolType(SlotIndex) == ToolUI::Pickaxe)
	{
		modelStack.PushMatrix();
		modelStack.Rotate(90, 1, 0, 0);
		RenderModelOnScreen(meshList[GEO_PICKAXE], 15, RotateX, 4, 0, 0);
		modelStack.PopMatrix();
	}

	if (Inventory.GetToolType(SlotIndex) == ToolUI::Torchlight)
	{
		//benny pls
	}


    if (numScene == 1)
    {
        RenderScene1();
    }
    if (numScene == 2)
    {
        RenderScene2();
    }

    if (SpawnGhost)
    {
        modelStack.PushMatrix();
        modelStack.Translate(Ghost1X, Ghost1Y, Ghost1Z);
        //modelStack.Rotate(rotateYGhost, 0, 1, 0);
        RenderMesh(meshList[GEO_GHOST1], true);
        modelStack.PopMatrix();
    }

	RenderMesh(meshList[GEO_AXES], false);
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS :" + std::to_string(FPS), Color(0, 1, 0), 2, 0, 0);
	RenderTextOnScreen(meshList[GEO_TEXT], "POS (" + std::to_string(camera.position.x) + "," + std::to_string(camera.position.y) + "," + std::to_string(camera.position.z) + ")", Color(1, 0, 0), 2, 0, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "TAR (" + std::to_string(camera.target.x) + "," + std::to_string(camera.target.y) + "," + std::to_string(camera.target.z) + ")", Color(1, 0, 0), 2, 0, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0.25f, 0.9f, 0.82f), 4, 9.82f, 7);
}

void Assignment3::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}