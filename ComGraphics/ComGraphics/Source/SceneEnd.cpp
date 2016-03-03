/*************************************************************/
/*!
\file       SceneEnd.cpp
\author     Ng Jun Guo
\par        email: my.puny.brain@gmail.com
\brief
Function definitions for SceneEnd
*/
/*************************************************************/
#include "SceneEnd.h"
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
\brief	Default Constructor definitions for SceneEnd
*/
/****************************************************************************/

SceneEnd::SceneEnd()
{
	for (int i = 0; i < 3; ++i)
	{
		b_RepairDone[i] = false;
		b_startRepair[i] = false;
	}

	for (int i = 0; i < 2; ++i)
		f_RepairProcess[i] = 0.0f;

	f_rockY = 25.0f;

    spawnWaveOne = false;
    MobMS = 25;
    BossMS = 15;
    killCounter = 0;
    waveCounter = 0;
    CrosshairHit = false;
}
/****************************************************************************/
/*!
\brief	Default destructor for SceneEnd
*/
/****************************************************************************/
SceneEnd::~SceneEnd()
{
}
/****************************************************************************/
/*!
\brief	Initializer definitions for SceneEnd, including light, camera positions etc.
*/
/****************************************************************************/

void SceneEnd::Init()
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
	light[0].power = 2.0f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(20));
	light[0].cosInner = cos(Math::DegreeToRadian(1));
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

	/*--------------------[Inventory Interface and Tool Icons]--------------------*/
	meshList[GEO_TOOLUIONE] = MeshBuilder::GenerateOBJ("ToolUI", "OBJ//v2ToolUI.obj");
	meshList[GEO_TOOLUIONE]->textureID = LoadTGA("Image//ToolsUIBoxOne.tga");

	meshList[GEO_TOOLUITWO] = MeshBuilder::GenerateOBJ("ToolUI", "OBJ//v2ToolUI.obj");
	meshList[GEO_TOOLUITWO]->textureID = LoadTGA("Image//ToolsUIBoxTwo.tga");

	meshList[GEO_TOOLUITHREE] = MeshBuilder::GenerateOBJ("ToolUI", "OBJ//v2ToolUI.obj");
	meshList[GEO_TOOLUITHREE]->textureID = LoadTGA("Image//ToolsUIBoxThree.tga");

	meshList[GEO_TOOLUIFOUR] = MeshBuilder::GenerateOBJ("ToolUI", "OBJ//v2ToolUI.obj");
	meshList[GEO_TOOLUIFOUR]->textureID = LoadTGA("Image//ToolsUIBoxFour.tga");

	meshList[GEO_RHAND] = MeshBuilder::GenerateOBJ("Hand", "OBJ//RightHand.obj");
	meshList[GEO_RHAND]->textureID = LoadTGA("Image//RightHand.tga");

	meshList[GEO_LHAND] = MeshBuilder::GenerateOBJ("Hand", "OBJ//LeftHand.obj");
	meshList[GEO_LHAND]->textureID = LoadTGA("Image//LeftHand.tga");

	meshList[GEO_HANDICON] = MeshBuilder::GenerateQuad("HandIcon", Color(1, 1, 1));
	meshList[GEO_HANDICON]->textureID = LoadTGA("Image//HandIcon.tga");

	meshList[GEO_PICKAXE] = MeshBuilder::GenerateOBJ("Pickaxe", "OBJ//Pickaxe.obj");
	meshList[GEO_PICKAXE]->textureID = LoadTGA("Image//Pickaxe.tga");

	meshList[GEO_PICKAXEICON] = MeshBuilder::GenerateQuad("PickAxeIcon", Color(1, 1, 1));
	meshList[GEO_PICKAXEICON]->textureID = LoadTGA("Image//PickaxeIcon.tga");

	meshList[GEO_BAT] = MeshBuilder::GenerateOBJ("BaseballBat", "OBJ//BaseballBat.obj");
	meshList[GEO_BAT]->textureID = LoadTGA("Image//BaseballBat.tga");

	meshList[GEO_BATICON] = MeshBuilder::GenerateQuad("BatIcon", Color(1, 1, 1));
	meshList[GEO_BATICON]->textureID = LoadTGA("Image//BaseballBat.tga");

	meshList[GEO_SWORD] = MeshBuilder::GenerateOBJ("Sword", "OBJ//Sword.obj");
	meshList[GEO_SWORD]->textureID = LoadTGA("Image//Sword.tga");

	meshList[GEO_SWORDICON] = MeshBuilder::GenerateQuad("SwordIcon", Color(1, 1, 1));
	meshList[GEO_SWORDICON]->textureID = LoadTGA("Image//SwordIcon.tga");

	meshList[GEO_REPAIRPOD] = MeshBuilder::GenerateTorus("Repair", Color(1, 0, 0), 4, 36, 1.0f, 0.1f);
	meshList[GEO_REPAIRDONE] = MeshBuilder::GenerateTorus("Repair", Color(0, 1, 0), 4, 36, 1.0f, 0.1f);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_MAINDOORLEFT] = MeshBuilder::GenerateOBJ("MainDoorLeft", "OBJ//MDLeft.obj");
	meshList[GEO_MAINDOORLEFT]->textureID = LoadTGA("Image//MDLeft.tga");
	meshList[GEO_MAINDOORRIGHT] = MeshBuilder::GenerateOBJ("MainDoorRight", "OBJ//MDRight.obj");
	meshList[GEO_MAINDOORRIGHT]->textureID = LoadTGA("Image//MDRight.tga");
	meshList[GEO_RUBBLE] = MeshBuilder::GenerateOBJ("Rubble", "OBJ//Rubble.obj");
	meshList[GEO_PORTRAIT] = MeshBuilder::GenerateOBJ("Portrait", "OBJ//Portrait.obj");
	meshList[GEO_PORTRAIT]->textureID = LoadTGA("Image//Scream.tga");

	// Tools Interface and It's Icons
	meshList[GEO_PLANETFLOOR] = MeshBuilder::GenerateQuad("planet floor", Color(1, 1, 1));
	meshList[GEO_PLANETFLOOR]->textureID = LoadTGA("Image//PlanetFloor.tga");

	meshList[GEO_FACILITYOUT] = MeshBuilder::GenerateOBJ("FacilityOut", "OBJ//FacilityOUT.obj");
	meshList[GEO_FACILITYOUT]->textureID = LoadTGA("Image//FacilityOUT.tga");
	meshList[GEO_FACILITYOUTWALL] = MeshBuilder::GenerateQuad("Facility Wall Outside", Color(1, 1, 1));
	meshList[GEO_FACILITYOUTWALL]->textureID = LoadTGA("Image//OutsideWALL.tga");

	/*--------------------[Used as a background for Dead Scene]--------------------*/
	meshList[GEO_DEADCOLOR] = MeshBuilder::GenerateQuad("DeadScreen", Color(1, 0, 0));
	meshList[GEO_DEADBLACKSCREEN] = MeshBuilder::GenerateQuad("DeadSCreenTwo", Color(0, 0, 0));

	meshList[GEO_SPACESHIP] = MeshBuilder::GenerateOBJ("Ship", "OBJ//Spaceship.obj");
	meshList[GEO_SPACESHIP]->textureID = LoadTGA("Image//MaterialsShip.tga");

	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJ("ROCK", "OBJ//Rock.obj");
	meshList[GEO_ROCK]->textureID = LoadTGA("Image//rock.tga");

	meshList[GEO_HEALTHICON] = MeshBuilder::GenerateQuad("HealthIcon", Color(1, 1, 1));
	meshList[GEO_HEALTHICON]->textureID = LoadTGA("Image//Heart1.tga");

    meshList[GEO_BOSS] = MeshBuilder::GenerateOBJ("boss", "OBJ//Boss1.obj");
    meshList[GEO_BOSS]->textureID = LoadTGA("Image//Boss1.tga");

    meshList[GEO_GHOST1] = MeshBuilder::GenerateOBJ("Alien", "OBJ//AlienOne.obj");
    meshList[GEO_GHOST1]->textureID = LoadTGA("Image//Alien1.tga");

    meshList[GEO_CRYSTAL1] = MeshBuilder::GenerateOBJ("ghost placeholder", "OBJ//Crystal1.obj");
    meshList[GEO_CRYSTAL1]->textureID = LoadTGA("Image//Crystal.tga");
    meshList[GEO_CRYSTAL2] = MeshBuilder::GenerateOBJ("ghost placeholder", "OBJ//Crystal2.obj");
    meshList[GEO_CRYSTAL2]->textureID = LoadTGA("Image//Crystal.tga");


	// meshList for health bar
	meshList[GEO_HEALTHBAR] = MeshBuilder::GenerateQuad("Healthbar", Color(1, 0, 0));
	meshList[GEO_STAMINABAR] = MeshBuilder::GenerateQuad("STAMINABAR", Color(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

    MobOne.setSpawnGhost(25, -8);
    MobTwo.setSpawnGhost(26, 73);
    MobThree.setSpawnGhost(-22, 42);

    BossOne.setSpawnBossOne(-36, -6);


}

static float LSPEED = 10.f;


void SceneEnd::Reset()
{
	Explorer::instance()->hp = 100;
	Explorer::instance()->isDead = false;
	Explorer::instance()->PlayerLife = 3;
	Explorer::instance()->SavePoint = (0.0f, 0.0f, 0.0f);
	Variables.f_redScreenTimer = 0.0f;

	for (int i = 0; i < 10; ++i)
	{
		Explorer::instance()->b_SoundEffect[i] = false;
		Explorer::instance()->b_MonsterSound[i] = false;
	}

	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->itemAttack[i] = 0;

		if (Explorer::instance()->GetToolType(i + 1) != ToolUI::Hand)
			Explorer::instance()->TotalTools.push_back(ToolUI(ToolUI::Empty));
	}
}
/****************************************************************************/
/*!
\brief
This Function checks for camera position and relative target and stops 'movement'

\param smallx
the smaller x value of the AABB bounding box

\param largex
the larger x value of the AABB bounding box

\param smallz
the smaller z value of the AABB bounding box

\param largez
the larger z value of the AABB bounding box
*/
/****************************************************************************/
void SceneEnd::Collision(float smallx, float largex, float smallz, float largez)
{
	if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z >= smallz) && (camera.position.z <= smallz + 3.f)){ camera.position.z = smallz; }
	if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z <= largez) && (camera.position.z >= largez - 3.f)){ camera.position.z = largez; }
	if ((camera.position.z >= smallz) && (camera.position.z <= largez) && (camera.position.x >= smallx) && (camera.position.x <= smallx + 3.f)){ camera.position.x = smallx; }
	if ((camera.position.z >= smallz) && (camera.position.z <= largez) && (camera.position.x <= largex) && (camera.position.x >= largex - 3.f)){ camera.position.x = largex; }

	camera.target = Vector3(
		sin(Math::DegreeToRadian(camera.rotationY)) * cos(Math::DegreeToRadian(camera.rotationX)) + camera.position.x,
		sin(Math::DegreeToRadian(camera.rotationX)) + camera.position.y,
		cos(Math::DegreeToRadian(camera.rotationX)) * cos(Math::DegreeToRadian(camera.rotationY)) + camera.position.z
		);
}
/****************************************************************************/
/*!
\brief
This Function checks for camera position being near the edges of a AABB bounding box
, with a current allowance of 2.f.

\param smallx
the smaller x value of the AABB bounding box

\param largex
the larger x value of the AABB bounding box

\param smallz
the smaller z value of the AABB bounding box

\param largez
the larger z value of the AABB bounding box
*/
/****************************************************************************/
bool SceneEnd::proximitycheck(float smallx, float largex, float smallz, float largez)
{
	//this function checks if the camera is close to a side of the object
	bool result = false;
	if ((camera.position.x >= smallx - 2.f) && (camera.position.x <= smallx) && (camera.position.z >= smallz) && (camera.position.z <= largez)){ result = true; }
	if ((camera.position.x <= largex + 2.f) && (camera.position.x >= largex) && (camera.position.z >= smallz) && (camera.position.z <= largez)){ result = true; }
	if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z >= smallz - 2.f) && (camera.position.z <= smallz)){ result = true; }
	if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z <= largez + 2.f) && (camera.position.z >= largez)){ result = true; }
	return result;
}
/****************************************************************************/
/*!
\brief
This Function controls the animation of the death screen

\param dt
Delta time
*/
/****************************************************************************/

void SceneEnd::UpdatePlayerDiesInteraction(double dt)
{
	if (Explorer::instance()->isDead == true)
	{
		Variables.f_redScreenTimer += (float)(dt);
		light[0].power = 0.0f;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}
}

void SceneEnd::ContinueGameOrNot()
{
	if (Explorer::instance()->PlayerLife > 0 && Variables.f_redScreenTimer > 4.0f)
	{
		if (Application::IsKeyPressed('Y'))
		{
			camera.position.x = 0;
			camera.position.y = 10;
			camera.position.z = 0;

			--Explorer::instance()->PlayerLife;
			Explorer::instance()->hp = 100;
			Explorer::instance()->isDead = false;
			Variables.f_redScreenTimer = 0.0f;

			for (int i = 0; i < 3; ++i)
			{
				b_RepairDone[i] = false;
				b_startRepair[i] = false;
			}

			for (int i = 0; i < 2; ++i)
				f_RepairProcess[i] = 0.0f;

			f_rockY = 25.0f;

            //
            MobOne.health = 8;
            MobTwo.health = 8;
            MobThree.health = 8;
            BossOne.health = 32;

            MobMS = 25;
            BossMS = 15;

            MobOne.setSpawnGhost(25, -8);
            MobTwo.setSpawnGhost(26, 73);
            MobThree.setSpawnGhost(-22, 42);

            BossOne.setSpawnBossOne(-36, -6);

			for (int i = 0; i < 10; ++i)
			{
				Explorer::instance()->b_SoundEffect[i] = false;
				Explorer::instance()->b_MonsterSound[i] = false;
			}

			light[0].power = 2.0f;
			glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
		}

		else if (Application::IsKeyPressed('N'))
		{
			Reset();
			Application::OpenGame();
		}
	}
}

void SceneEnd::MouseScrollToolSlot()
{
	if (Application::mouse_scroll > 0)
	{
		Explorer::instance()->i_SlotIndex++;
	}

	else if (Application::mouse_scroll < 0)
	{
		Explorer::instance()->i_SlotIndex--;
	}

	if (Explorer::instance()->i_SlotIndex > 4)
	{
		Explorer::instance()->i_SlotIndex = 1;
	}

	else if (Explorer::instance()->i_SlotIndex < 1)
	{
		Explorer::instance()->i_SlotIndex = 4;
	}
}

void SceneEnd::RenderMouseScrollToolSlot()
{
	if (Explorer::instance()->isDead == false)
	{
		if (Explorer::instance()->i_SlotIndex == 1)
			RenderModelOnScreen(meshList[GEO_TOOLUIONE], 7.0f, 7.0f, 7.0f, 0.0f, 1.0f, 0.0f, 0.0f, 5.75f, 0.0f, 0.0f, false);

		if (Explorer::instance()->i_SlotIndex == 2)
			RenderModelOnScreen(meshList[GEO_TOOLUITWO], 7.0f, 7.0f, 7.0f, 0.0f, 1, 0, 0, 5.75f, 0.0f, 0.0f, false);

		if (Explorer::instance()->i_SlotIndex == 3)
			RenderModelOnScreen(meshList[GEO_TOOLUITHREE], 7.0f, 7.0f, 7.0f, 0.0f, 1, 0, 0, 5.75f, 0.0f, 0.0f, false);

		if (Explorer::instance()->i_SlotIndex == 4)
			RenderModelOnScreen(meshList[GEO_TOOLUIFOUR], 7.0f, 7.0f, 7.0f, 0.0f, 1, 0, 0, 5.75f, 0.0f, 0.0f, false);
	}
}

void SceneEnd::ToolSelectionMouseScroll()
{
	if (Explorer::instance()->isDead == false)
	{
		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Hand)
		{
			RenderModelOnScreen(meshList[GEO_RHAND], 15, 15, 15, Variables.RotateX, 1, 0, 0, 4.5f, 0.0f, -1.0f, false);
			RenderModelOnScreen(meshList[GEO_LHAND], 15, 15, 15, Variables.RotateX, 1, 0, 0, 0.75f, 0.0f, -1.0f, false);
		}

		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Pickaxe)
		{
			modelStack.PushMatrix();
			RenderModelOnScreen(meshList[GEO_PICKAXE], 15.0f, 15.0f, 15.0f, Variables.RotateX, 1, 0, 0, 4.5f, 0.0f, 0.0f, false);
			modelStack.PopMatrix();
		}

		else if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::BaseballBat)
		{
			modelStack.PushMatrix();
			RenderModelOnScreen(meshList[GEO_BAT], 15.0f, 15.0f, 15.0f, Variables.RotateX, 1, 0, 0, 4.5f, 0.0f, 0.0f, false);
			modelStack.PopMatrix();
		}

		else if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Sword)
		{
			modelStack.PushMatrix();
			RenderModelOnScreen(meshList[GEO_SWORD], 15.0f, 15.0f, 15.0f, Variables.RotateX, 1, 0, 0, 4.5f, 0.0f, 0.0f, false);
			modelStack.PopMatrix();
		}
	}
}

void SceneEnd::RenderToolIcon()
{
	if (Explorer::instance()->isDead == false)
	{
		if (Explorer::instance()->isDead == false)
		{
			if (Explorer::instance()->GetToolType(1) == ToolUI::Hand)
			{
				RenderModelOnScreen(meshList[GEO_HANDICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 6.6f, 0.775f, 1.0f, false);
			}

			if (Explorer::instance()->GetToolType(2) == ToolUI::Pickaxe)
			{
				RenderModelOnScreen(meshList[GEO_PICKAXEICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 8.175f, 0.775f, 1.0f, false);
			}

			else if (Explorer::instance()->GetToolType(2) == ToolUI::BaseballBat)
			{
				RenderModelOnScreen(meshList[GEO_BATICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 8.175f, 0.775f, 1.0f, false);
			}

			else if (Explorer::instance()->GetToolType(2) == ToolUI::Sword)
			{
				RenderModelOnScreen(meshList[GEO_SWORDICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 8.175f, 0.775f, 1.0f, false);
			}

			if (Explorer::instance()->GetToolType(3) == ToolUI::Pickaxe)
			{
				RenderModelOnScreen(meshList[GEO_PICKAXEICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 9.725f, 0.775f, 1.0f, false);
			}

			else if (Explorer::instance()->GetToolType(3) == ToolUI::BaseballBat)
			{
				RenderModelOnScreen(meshList[GEO_BATICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 9.725f, 0.775f, 1.0f, false);
			}

			else if (Explorer::instance()->GetToolType(3) == ToolUI::Sword)
			{
				RenderModelOnScreen(meshList[GEO_SWORDICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 9.725f, 0.775f, 1.0f, false);
			}

			if (Explorer::instance()->GetToolType(4) == ToolUI::Pickaxe)
			{
				RenderModelOnScreen(meshList[GEO_PICKAXEICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 11.725f, 0.775f, 1.0f, false);
			}

			else if (Explorer::instance()->GetToolType(4) == ToolUI::BaseballBat)
			{
				RenderModelOnScreen(meshList[GEO_BATICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 11.725f, 0.775f, 1.0f, false);
			}

			else if (Explorer::instance()->GetToolType(4) == ToolUI::Sword)
			{
				RenderModelOnScreen(meshList[GEO_SWORDICON], 4.5f, 4.5f, 4.5f, 90, 1, 0, 0, 11.275f, 0.775f, 1.0f, false);
			}
		}
	}
}
/****************************************************************************/
/*!
\brief
This Function controls the animation of the tool swing

\param dt
Delta time
*/
/****************************************************************************/

void SceneEnd::MouseClickFunction(double dt)
{
	if (Application::IsKeyPressed(VK_LBUTTON) && Variables.b_LockSwing == false && Variables.b_LockSwingDebounce == false && Explorer::instance()->stamina >= 20)
	{
		Variables.b_LockSwing = true;
		Variables.b_LockSwingDebounce = true;
		Explorer::instance()->stamina -= 20;

		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Pickaxe)
		{
			if (Explorer::instance()->b_SoundEffect[5] == false)
			{
				Application::MusicWillPlay(7, false);
				Explorer::instance()->b_SoundEffect[5] = true;
			}
		}

		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::BaseballBat)
		{
			if (Explorer::instance()->b_SoundEffect[5] == false)
			{
				Application::MusicWillPlay(8, false);
				Explorer::instance()->b_SoundEffect[5] = true;
			}
		}

		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Sword)
		{
			if (Explorer::instance()->b_SoundEffect[5] == false)
			{
				Application::MusicWillPlay(9, false);
				Explorer::instance()->b_SoundEffect[5] = true;
			}
		}
	}

	if (Variables.b_LockSwingDebounce == true)
	{
		Variables.RotateX -= 360.0f * (float)dt;
		if (Variables.RotateX <= -45.0f)
		{
			Variables.RotateX = -45.0f;
			Variables.b_LockSwingDebounce = false;      
            checkAttack();
		}
	}

	if (Variables.b_LockSwingDebounce == false && Variables.b_LockSwing == true && Variables.RotateX <= 0.0f)
	{
		Variables.RotateX += 360.0f * (float)dt;
		if (Variables.RotateX >= 0.0f)
		{
			Variables.RotateX = 0.0f;
			Variables.b_LockSwing = false;
		}
	}

    if (!Variables.b_LockSwing)
    {
        CrosshairHit = false;
    }
}

void SceneEnd::UpdateRepairs(double dt)
{
	if (camera.position.x > -6.0f && camera.position.x < 6.0f && camera.position.z > -166.0f && camera.position.z < -154.0f)
	{
		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Hand && b_RepairDone[1] == false)
		{
			b_startRepair[1] = true;
			f_RepairProcess[1] += (float)(5.0f * dt);
		}
	}

	else if (camera.position.x > -6.0f && camera.position.x < 6.0f && camera.position.z > -246.0f && camera.position.z < -234.0f)
	{
		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Hand && b_RepairDone[0] == false)
		{
			b_startRepair[0] = true;
			f_RepairProcess[0] += (float)(5.0f * dt);
		}
	}

	if (f_RepairProcess[0] >= 100.0f && b_RepairDone[0] == false && b_startRepair[0] == true)
	{
		b_startRepair[0] = false;
		b_RepairDone[0] = true;
	}

	if (f_RepairProcess[1] >= 100.0f && b_RepairDone[1] == false && b_startRepair[1] == true)
	{
		b_startRepair[1] = false;
		b_RepairDone[1] = true;
	}
}

bool SceneEnd::b_ReadyToFly()
{
	for (int i = 0; i < 3; ++i)
	{
		if (b_RepairDone[i] == false)
		{
			return false;
			break;
		}
	}

	return true;
}
/****************************************************************************/
/*!
\brief
This Function controls the flickering of the "torchlight"

\param dt
Delta time
*/
/****************************************************************************/

void SceneEnd::FlickeringLight(double dt)
{
	Explorer::instance()->f_FlickeringLight += (float)dt;
	if (static_cast<int>(Explorer::instance()->f_FlickeringLight) < 1.0f)
	{
		light[0].power = 2.0f;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}

	else if (Explorer::instance()->f_FlickeringLight < 1.2f)
	{
		light[0].power = 0.0f;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}

	else if (Explorer::instance()->f_FlickeringLight > 1.2f)
	{
		Explorer::instance()->f_FlickeringLight = 0.0f;
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

void SceneEnd::Update(double dt)
{
	FPS = 1.f / (float)dt;
	worldspin += (float)(dt);

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	Collision(-50.0f, 70.0f, -240.0f, -160.0f);

	if (camera.position.x > -56.0f && camera.position.x < -44.0f && camera.position.z > -206.0f && camera.position.z < -194.0f)
	{
		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Pickaxe && b_RepairDone[2] == false && Application::IsKeyPressed(VK_LBUTTON) && Explorer::instance()->stamina >= 20)
		{
			b_startRepair[2] = true;
			f_rockY -= 0.15f;
		}

		if (f_rockY <= 1.0f)
		{
			f_rockY = 1.0f;
			b_RepairDone[2] = true;
			b_startRepair[2] = false;
		}
	}

	/*-------------------------[Death of the Explorer]-------------------------------*/
	Explorer::instance()->checkDead();
	UpdatePlayerDiesInteraction(dt);
	ContinueGameOrNot();

	if (Explorer::instance()->PlayerLife <= 0 && Variables.f_redScreenTimer > 8.0f)
	{
		Reset();
		Application::OpenGame();
	}

	if (Application::IsKeyPressed('Z'))
	{
		Explorer::instance()->InsertToolSlot(ToolUI::Pickaxe);
	}

	/*-------------------------[End of Death Functions]-------------------------------*/

	/*-------------------------[Tool UI Functions]-------------------------------*/
	MouseScrollToolSlot();
	MouseClickFunction(dt);
	/*-------------------------[End of Tool UI Functions]-------------------------------*/

	camera.Update(dt);
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[0].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));

	UpdateRepairs(dt);
    MobOne.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);
    MobTwo.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);
    MobThree.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);
    BossOne.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);
    MobCheck();
    moveMob(dt);
	if (b_ReadyToFly() && camera.position.x >= -60 && camera.position.x <= 80 && camera.position.z >= -250 && camera.position.z <= -150)
	{
		if (Application::IsKeyPressed('E'))
		{
			Application::EndingCutScene();
		}
	}

	//if (Application::IsKeyPressed('X'))
	//Explorer::instance()->InsertToolSlot(ToolUI::Pickaxe);
	//Explorer::instance()->InsertToolSlot(ToolUI::BaseballBat);
	//Explorer::instance()->InsertToolSlot(ToolUI::Sword);

    

	if (Application::IsKeyPressed('E'))
		Explorer::instance()->InsertToolSlot(ToolUI::Pickaxe);


    //door collision
    Collision(-40, 40, 70, 110);
    //unending wall collision
    Collision(-500, 500, 95, 105);
    //world bound
    Collision(495, 505, -500, 500);
    Collision(-505, -495, -500, 500);
    Collision(-500, 500, -505, -495);

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

void SceneEnd::RenderMesh(Mesh*mesh, bool enableLight)
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
This Function renders text at a coordinate on worldspace

\param Mesh* mesh
pointer to mesh to render

\param text
text to render

\param color
color of the text to render
*/
/****************************************************************************/

void SceneEnd::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneEnd::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneEnd::RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float Tx, float Ty, float Tz, bool LightYN)
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

void SceneEnd::Render()
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
    //mobs
    if (MobOne.Spawn)
    {
        RenderMobs(MobOne.MobPosX, MobOne.MobPosZ);
    }
    if (MobTwo.Spawn)
    {
        RenderMobs(MobTwo.MobPosX, MobTwo.MobPosZ);
    }
    if (MobThree.Spawn)
    {
        RenderMobs(MobThree.MobPosX, MobThree.MobPosZ);
    }
    if (BossOne.Spawn)
    {
        RenderBoss(BossOne.MobPosX, BossOne.MobPosZ);
    }

	RenderSkyBox();
	RenderSceneEnd();
	RenderFloor();
    RenderDownWall(0, 100);
	RenderShipAndPod();

	RenderPlayerDiesInteraction();

	ToolSelectionMouseScroll();
	RenderMouseScrollToolSlot();
	RenderToolIcon();
	RenderRepairText();
	RenderMineText();

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS :" + std::to_string(FPS), Color(0, 1, 0), 2, 0, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "POS (" + std::to_string(camera.position.x) + "," + std::to_string(camera.position.y) + "," + std::to_string(camera.position.z) + ")", Color(1, 0, 0), 2, 0, 2);
    if (!CrosshairHit)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0.25f, 0.9f, 0.82f), 4, 9.8f, 7);
    }
    if (CrosshairHit)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(1.0f, 0.0f, 0.0f), 4, 9.8f, 7);

    }

	if (b_RepairDone[2] == false)
	{
		modelStack.PushMatrix();
			modelStack.Translate(-30, 0, -200);
			modelStack.Scale(20, f_rockY, 20);
			RenderMesh(meshList[GEO_ROCK], true);
		modelStack.PopMatrix();
	}

	RenderModelOnScreen(meshList[GEO_HEALTHBAR], Explorer::instance()->hp / 5, 1.0f, 1.0f, 90, 1, 0, 0, 0, 57.0f, 0, false);
	RenderModelOnScreen(meshList[GEO_STAMINABAR], Explorer::instance()->stamina / 5, 1.0f, 1.0f, 90, 1, 0, 0, 0, 56.0f, 0, false);

	for (float i = 0; i < Explorer::instance()->PlayerLife; ++i)
		RenderModelOnScreen(meshList[GEO_HEALTHICON], 3.f, 3.f, 3.f, 90, 1, 0, 0, (22.f + i), 18.5f, 1.0f, false);

}
/****************************************************************************/
/*!
\brief
This Function deletes openGL based stuff
*/
/****************************************************************************/

void SceneEnd::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}