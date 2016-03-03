/**************************************************************************/
/*!
\file			Credits.cpp
\author			Matsuda Kenichi
\par			email: 150450F\@mymail.nyp.edu.sg
\brief
File containing function to make animation of the Credits
*/
/**************************************************************************/

#include "Credits.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "LoadTGA.h"
#include "Utility.h"
#include <sstream>
#include "GlobalVariables.h"

/****************************************************************************/
/*!
\brief	Default Constructor definitions for Credits
*/
/****************************************************************************/

Credits::Credits()
{
	bool move1 = true;

	bool first = true;
	bool second = false;

	bool timer = false;
}


/****************************************************************************/
/*!
\brief	Default destructor for Credits
*/
/****************************************************************************/

Credits::~Credits()
{
}

/****************************************************************************/
/*!
\brief	Initializer definitions for Credits, including light, camera positions etc.
*/
/****************************************************************************/

void Credits::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1.0f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(30));
	light[0].cosInner = cos(Math::DegreeToRadian(15));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));

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
	camera.Init(Vector3(0, 10, 0), Vector3(0, 10, -1), Vector3(0, 1, 0));

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TEXTBACKGROUND] = MeshBuilder::GenerateQuad("text background", Color(1, 1, 1));

	meshList[GEO_NAME1] = MeshBuilder::GenerateQuad("Benny", Color(1, 1, 1));
	meshList[GEO_NAME1]->textureID = LoadTGA("Image//Benny.tga");
	meshList[GEO_NAME2] = MeshBuilder::GenerateQuad("Kewpie", Color(1, 1, 1));
	meshList[GEO_NAME2]->textureID = LoadTGA("Image//Kewpie.tga");
	meshList[GEO_NAME3] = MeshBuilder::GenerateQuad("Lyk", Color(1, 1, 1));
	meshList[GEO_NAME3]->textureID = LoadTGA("Image//Lyk.tga");
	meshList[GEO_NAME4] = MeshBuilder::GenerateQuad("Kenichi", Color(1, 1, 1));
	meshList[GEO_NAME4]->textureID = LoadTGA("Image//Kenichi.tga");

	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("Title", Color(1, 1, 1));
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//Title.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

}

static float LSPEED = 10.f;


void Credits::Reset()
{
}

/**************************************************************************/
/*!
\brief
Function for reading credits text and image

\bool first, second, third, fourth, fifth, last
	if True, text and image will render.

*/
/**************************************************************************/

void Credits::RenderCredits()
{

	if (first)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "GAME", Color(1, 1, 1), 15, 6.6f+firstcredits, 2);
		RenderTextOnScreen(meshList[GEO_TEXT], "COMPLETED", Color(1, 1, 1), 15, 5.5f+firstcredits, 1);
	}

	if (second)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_NAME1], 70.f, 70.f, 10.f, 90, 1, 0, 0, 1.56f+secondcredits, 0.4f, 1.0f, false);
		modelStack.PopMatrix();

	}

	if (third)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_NAME2], 70.f, 70.f, 10.f, 90, 1, 0, 0, 1.56f+thirdcredits, 0.4f, 1.0f, false);
		modelStack.PopMatrix();
	}

	if (fourth)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_NAME3], 70.f, 70.f, 10.f, 90, 1, 0, 0, 1.56f+fourthcredits, 0.4f, 1.0f, false);
		modelStack.PopMatrix();
	}


	if (fifth)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_NAME4], 70.f, 70.f, 10.f, 90, 1, 0, 0, 1.56f+fifthcredits, 0.4f, 1.0f, false);
		modelStack.PopMatrix();
	}

	if (last)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_TITLE], 70.f, 15.f, 10.f, 90, 1, 0, 0, 1.7f +lastcredits, 2.f, 1.0f, false);
		modelStack.PopMatrix();

	}

}

/**************************************************************************/
/*!
\brief
Function for setting speed for variable to be use foranimation
\param dt
	dt = delta time
\bool
	timer, move1, move2, move3, move4, move5, move6

	if true, function will run.

\float countdown, firstcredits, secondcredits, thirdcredits, fourthcredits, fifthcredits, lastcredits

	variable to hold speed for animation.

*/
/**************************************************************************/

void Credits::RenderMovingCredits(double dt)
{
	if (timer)
	{
		countdown += 1;
	}

	if (move1)
	{
		firstcredits -= (float)(3 * dt);
	}
	if (move2)
	{
		secondcredits -= (float)(0.5f * dt);
	}
	if (move3)
	{
		thirdcredits -= (float)(0.5f * dt);
	}
	if (move4)
	{
		fourthcredits -= (float)(0.5f * dt);
	}
	if (move5)
	{
		fifthcredits -= (float)(0.5f * dt);
	}
	if (move6)
	{
		lastcredits -= (float)(0.5f * dt);
	}


	if (first)
	{
		move1 = true;
		if (firstcredits <= -5)
		{
			move1 = false;
			timer = true;
			if (countdown >= 200)
			{
				timer = false;
				move1 = true;
				if (firstcredits <= -11)
				{
					first = false;
					second = true;
					countdown = 0;
				}
			}
		}
	}

	if (second)
	{
		move2 = true;
		if (secondcredits <= -1)
		{
			move2 = false;
			timer = true;
			if (countdown >= 200)
			{
				timer = false;
				move2 = true;
				if (secondcredits <= -2.3f)
				{
					second = false;
					third = true;
					countdown = 0;
				}
			}
		}
	}

	if (third)
	{
		move3 = true;
		if (thirdcredits <= -1)
		{
			move3 = false;
			timer = true;
			if (countdown >= 200)
			{
				timer = false;
				move3 = true;
				if (thirdcredits <= -2.3f)
				{
					third = false;
					fourth = true;
					countdown = 0;
				}
			}
		}
	}

	if (fourth)
	{
		move4 = true;
		if (fourthcredits <= -1)
		{
			move4 = false;
			timer = true;
			if (countdown >= 200)
			{
				timer = false;
				move4 = true;
				if (fourthcredits <= -2.3f)
				{
					fourth = false;
					fifth = true;
					countdown = 0;
				}
			}
		}
	}

	if (fifth)
	{
		move5 = true;
		if (fifthcredits <= -1)
		{
			move5 = false;
			timer = true;
			if (countdown >= 200)
			{
				timer = false;
				move5 = true;
				if (fifthcredits <= -2.3f)
				{
					fifth = false;
					last = true;
					countdown = 0;
				}
			}
		}
	}

	if (last)
	{
		move6 = true;
		if (lastcredits <= -1.1f)
		{
			move6 = false;
			timer = true;
			if (countdown >= 200)
			{
				Application::OpenGame();
			}
		}
	}
}

/****************************************************************************/
/*!
\brief
This Function is the main Update function of the Level, which houses all other functions.

\param dt
To slow down animations or other relevant variables
*/
/****************************************************************************/

void Credits::Update(double dt)
{
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[0].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));

	/*-------------------------[End of Tool UI Functions]-------------------------------*/

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode


	RenderMovingCredits(dt);
}

/****************************************************************************/
/*!
\brief
This Function renders the mesh of specified object with or without light

\param Mesh* mesh
pointer to mesh to render

\param enableLight
Whether to account for light
*/
/****************************************************************************/


void Credits::RenderMesh(Mesh*mesh, bool enableLight)
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

/****************************************************************************/
/*!
\brief
This Function renders text at a coordinate on cameraspace

\param Mesh* mesh
pointer to mesh to render

\param text
text to render

\param color
color of the text to render

\param size
size of the text to render

\param x
x coordinate of text to render

\param y
y coordinate of text to render
*/
/****************************************************************************/

void Credits::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

/****************************************************************************/
/*!
\brief
This Function renders an OBJ at a coordinate on cameraspace

\param Mesh* mesh
pointer to mesh to render

\param Sx,Sy,Sz
Scaling by x,y,z

\param Rotate
angle to rotate by

\param rx,ry,rz
rotation to be done on x,y,or z axis

\param tx,ty,tz
translation of model on the x,y,z axis

\param LightYN
to account for Light
*/
/****************************************************************************/

void Credits::RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float Tx, float Ty, float Tz, bool LightYN)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -50, 50); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(Sx, Sy, Sz);
	modelStack.Translate(Tx, Ty, Tz);
	modelStack.Rotate(Rotate, (float)rX, (float)rY, (float)rZ);

	RenderMesh(mesh, LightYN);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

/****************************************************************************/
/*!
\brief
This Function is the main function for all rendercalls
*/
/****************************************************************************/

void Credits::Render()
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

	RenderCredits();
}

/****************************************************************************/
/*!
\brief
This Function deletes openGL based stuff
*/
/****************************************************************************/

void Credits::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}