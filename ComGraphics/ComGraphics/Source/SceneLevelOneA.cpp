/*************************************************************/
/*!
\file       SceneLevelOneA.cpp
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Function definitions for SceneLevelOneA
*/
/*************************************************************/
#include "SceneLevelOneA.h"
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
\brief	Default Constructor definitions for SceneLevelOneA
*/
/****************************************************************************/
SceneLevelOneA::SceneLevelOneA()
{
	 activateDoor1 = false;
	 activateDoor2_1 = false;
	 activateDoor2_2 = false;
	 activateDoor3 = false;
	 Key_1 = false;
	 Notice = false;
	 Notice2 = false;
	 willDrop = false;
	 Key1Active = false;
     CrosshairHit = false;
     SwitchRot = 45.f;
}

/****************************************************************************/
/*!
\brief	Default destructor for SceneLevelOneA
*/
/****************************************************************************/
SceneLevelOneA::~SceneLevelOneA()
{
}

/****************************************************************************/
/*!
\brief	Initializer definitions for SceneLevelOneA, including light, camera positions etc.
*/
/****************************************************************************/
void SceneLevelOneA::Init()
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
    camera.Init(Vector3(0, 10, 420), Vector3(0, 10, 1), Vector3(0, 1, 0));
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

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
    meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

    meshList[GEO_RUBBLE] = MeshBuilder::GenerateOBJ("Rubble", "OBJ//Rubble.obj");
	meshList[GEO_RUBBLE]->textureID = LoadTGA("Image//InsideWALL.tga");
    meshList[GEO_PORTRAIT] = MeshBuilder::GenerateOBJ("Portrait", "OBJ//Portrait.obj");
    meshList[GEO_PORTRAIT]->textureID = LoadTGA("Image//Scream.tga");
	meshList[GEO_TV] = MeshBuilder::GenerateOBJ("TV", "OBJ//TV.obj");
	meshList[GEO_TV]->textureID = LoadTGA("Image//TV.tga");
	meshList[GEO_BARREL] = MeshBuilder::GenerateOBJ("Barrel", "OBJ//Barrel.obj");
	meshList[GEO_BARREL]->textureID = LoadTGA("Image//Barrel.tga");
	meshList[GEO_DEADBODY] = MeshBuilder::GenerateOBJ("Pile of dead body", "OBJ//DeadBody.obj");
	meshList[GEO_DEADBODY]->textureID = LoadTGA("Image//DeadBody.tga");

	meshList[GEO_BLOOD] = MeshBuilder::GenerateOBJ("ToolUI", "OBJ//v2ToolUI.obj");
	meshList[GEO_BLOOD]->textureID = LoadTGA("Image//Blood.tga");

    meshList[GEO_DOORSWITCH] = MeshBuilder::GenerateOBJ("lever", "OBJ//PuzzleLever.obj");
    meshList[GEO_DOORSWITCH]->textureID = LoadTGA("Image//PuzzleLever.tga");

    meshList[GEO_FACILITYWALLS] = MeshBuilder::GenerateQuad("Facility Wall", Color(1, 1, 1));
    meshList[GEO_FACILITYWALLS]->textureID = LoadTGA("Image//InsideWALL.tga");

    meshList[GEO_FACILITYCEILINGS] = MeshBuilder::GenerateQuad("Facility Ceiling", Color(1, 1, 1));
    meshList[GEO_FACILITYCEILINGS]->textureID = LoadTGA("Image//InsideCEILING.tga");

    meshList[GEO_FACILITYFLOOR] = MeshBuilder::GenerateQuad("Facility Floor", Color(1, 1, 1));
    meshList[GEO_FACILITYFLOOR]->textureID = LoadTGA("Image//InsideFLOOR.tga");
    
    meshList[GEO_FACILITYOUT] = MeshBuilder::GenerateOBJ("FacilityOut", "OBJ//FacilityOUT.obj");
    meshList[GEO_FACILITYOUT]->textureID = LoadTGA("Image//FacilityOUT.tga");
    meshList[GEO_FACILITYOUTWALL] = MeshBuilder::GenerateQuad("Facility Wall Outside", Color(1, 1, 1));
    meshList[GEO_FACILITYOUTWALL]->textureID = LoadTGA("Image//OutsideWALL.tga");


    meshList[GEO_GHOST1] = MeshBuilder::GenerateOBJ("Alien", "OBJ//AlienOne.obj");
    meshList[GEO_GHOST1]->textureID = LoadTGA("Image//Alien1.tga");

	meshList[GEO_SLIDEDOORTOP] = MeshBuilder::GenerateOBJ("Hand", "OBJ//SlideDoorTop.obj");
	meshList[GEO_SLIDEDOORTOP]->textureID = LoadTGA("Image//SlidingDoorTop.tga");
	meshList[GEO_SLIDEDOORBTM] = MeshBuilder::GenerateOBJ("Hand", "OBJ//SlideDoorBtm.obj");
	meshList[GEO_SLIDEDOORBTM]->textureID = LoadTGA("Image//SlidingDoorBtm.tga");

    meshList[GEO_SPAWNPOINT] = MeshBuilder::GenerateOBJ("Spawn", "OBJ//SpawnPoint.obj");
    meshList[GEO_SPAWNPOINT]->textureID = LoadTGA("Image//SpawnPoint.tga");

    meshList[GEO_SUITCASE] = MeshBuilder::GenerateOBJ("Spawn", "OBJ//SuitCase.obj");
    meshList[GEO_SUITCASE]->textureID = LoadTGA("Image//SuitCase.tga");

	meshList[GEO_HEALTHBAR] = MeshBuilder::GenerateQuad("Healthbar", Color(1, 0, 0));
	meshList[GEO_STAMINABAR] = MeshBuilder::GenerateQuad("STAMINABAR", Color(0, 1, 0));

	meshList[GEO_HEALTHICON] = MeshBuilder::GenerateQuad("HealthIcon", Color(1, 1, 1));
	meshList[GEO_HEALTHICON]->textureID = LoadTGA("Image//Heart1.tga");

	/*--------------------[Used as a background for Dead Scene]--------------------*/
	meshList[GEO_DEADCOLOR] = MeshBuilder::GenerateQuad("DeadScreen", Color(1, 0, 0));
	meshList[GEO_DEADBLACKSCREEN] = MeshBuilder::GenerateQuad("DeadSCreenTwo", Color(0, 0, 0));

    Mtx44 projection;
    projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
    projectionStack.LoadMatrix(projection);

    Ghost.setSpawnGhost(-30, -15);
	Explorer::instance()->SavePoint = camera.position;
}

static float LSPEED = 10.f;

/****************************************************************************/
/*!
\brief	This Function resets all local variables to default values as listed in Init.
*/
/****************************************************************************/
void SceneLevelOneA::ResetSameScene()
{
	Explorer::instance()->hp = 100;
	Explorer::instance()->isDead = false;
	Explorer::instance()->SavePoint = (0.0f, 0.0f, 0.0f);
	Variables.f_redScreenTimer = 0.0f;

	activateDoor1 = false;
	activateDoor2_1 = false;
	activateDoor2_2 = false;
	activateDoor3 = false;
	Key_1 = false;
	Notice = false;
	Notice2 = false;
	willDrop = false;
	Key1Active = false;

	anima.RubbleCollapse = 100;
	anima.Collapse = false;
	anima.f_PortraitDrop = 6;
	anima.f_PortraitFall = 0;
	anima.b_toPortraitDrop = false;
	anima.b_toPortraitFall = false;

	anima.DoorSlideTop = 0;
	anima.DoorSlideBtm = 0;
	anima.toSlideDoorTop = true;
	anima.toSlideDoorBtm = true;

	anima.DoorSlideTop_2 = 0;
	anima.DoorSlideBtm_2 = 0;
	anima.toSlideDoorTop2 = true;
	anima.toSlideDoorBtm2 = true;
	anima.ClosingDoorTop2 = true;
	anima.ClosingDoorBtm2 = true;

	anima.DoorSlideTop_3 = 0;
	anima.DoorSlideBtm_3 = 0;
	anima.toSlideDoorTop3 = true;
	anima.toSlideDoorBtm3 = true;

	for (int i = 0; i < 10; ++i)
	{
		Explorer::instance()->b_SoundEffect[i] = false;
		Explorer::instance()->b_MonsterSound[i] = false;
	}

    Ghost.Spawn = false;
    Ghost.health = 8;
    Ghost.setSpawnGhost(-30, -15);
}

/****************************************************************************/
/*!
\brief	This Function resets all GLOBAL variables to default values as listed in Init.
*/
/****************************************************************************/
void SceneLevelOneA::ResetAll()
{
    Explorer::instance()->PlayerLife = 3;

	for (int i = 0; i < 10; ++i)
	{
		Explorer::instance()->b_SoundEffect[i] = false;
		Explorer::instance()->b_MonsterSound[i] = false;
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
void SceneLevelOneA::Collision(float smallx, float largex, float smallz, float largez)
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
bool SceneLevelOneA::proximitycheck(float smallx, float largex, float smallz, float largez)
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
Used to check if player is within the area and if item is not in the inventory,
item will be picked up.
*/
/****************************************************************************/
void SceneLevelOneA::ToolsUI()
{
	if (Explorer::instance()->b_PickUpTool[0] == false && camera.position.x > -5.0f && camera.position.x < 5.0f && camera.position.z > 350.0f && camera.position.z < 370.0f)
	{
		Explorer::instance()->InsertToolSlot(ToolUI::Pickaxe);
		Explorer::instance()->b_PickUpTool[0] = true;
	}
}

/****************************************************************************/
/*!
\brief
Renders the tool according to i_SlotIndex
*/
/****************************************************************************/
void SceneLevelOneA::ToolSelectionMouseScroll()
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

/****************************************************************************/
/*!
\brief
Renders the icon of the tool according to the tooltype in the list created
in Explorer class
*/
/****************************************************************************/
void SceneLevelOneA::RenderToolIcon()
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
Uses glfw function to sense for mousewheel and add or minus i_SlotIndex accordingly
*/
/****************************************************************************/
void SceneLevelOneA::MouseScrollToolSlot()
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

/****************************************************************************/
/*!
\brief
Renders the tool inventory according to i_SlotIndex
*/
/****************************************************************************/
void SceneLevelOneA::RenderMouseScrollToolSlot()
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
/****************************************************************************/
/*!
\brief
This Function controls the animation of the tool swing

\param dt
delta time used to check animations and some logic
*/
/****************************************************************************/
void SceneLevelOneA::MouseClickFunction(double dt)
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
            AttackCheck();
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
/****************************************************************************/
/*!
\brief
This Function controls the animation of the death screen

\param dt
Delta time
*/
/****************************************************************************/

void SceneLevelOneA::UpdatePlayerDiesInteraction(double dt)
{
	if (Explorer::instance()->isDead == true)
	{
		Variables.f_redScreenTimer += (float)(dt);
		light[0].power = 0.0f;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}
}
/****************************************************************************/
/*!
\brief
This Function controls the death screen and checks if the player wants to continue the game

*/
/****************************************************************************/
void SceneLevelOneA::ContinueGameOrNot()
{
	if (Explorer::instance()->PlayerLife > 0 && Variables.f_redScreenTimer > 4.0f)
	{
		if (Application::IsKeyPressed('Y'))
		{
			camera.position = Explorer::instance()->SavePoint;

			--Explorer::instance()->PlayerLife;
			Explorer::instance()->hp = 100;
			Explorer::instance()->isDead = false;
			Variables.f_redScreenTimer = 0.0f;

			ResetSameScene();

			light[0].power = 1.0f;
			glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
		}

		else if (Application::IsKeyPressed('N'))
		{
			Application::OpenGame();

			ResetAll();
			ResetSameScene();
			for (int i = 0; i < 4; ++i)
			{
				Explorer::instance()->itemAttack[i] = 0;
			}

			Explorer::instance()->RemoveToolSlot(ToolUI::Empty);
		}
	}
}
/****************************************************************************/
/*!
\brief
This Function controls the intercation with the suitcase

*/
/****************************************************************************/

void SceneLevelOneA::PickUpSuitcaseInteraction()
{
	if (camera.position.x > 270.0f && camera.position.x < 290.0f && camera.position.z > 110.0f && camera.position.z < 130.0f)
	{
		if (Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Hand && Explorer::instance()->b_pickUpSuitCase[0] == false)
		{
			Explorer::instance()->b_pickUpSuitCase[0] = true;
			Explorer::instance()->i_SuitcaseCount++;
		}
	}
}
/****************************************************************************/
/*!
\brief
Light flickering
\param double dt
delta time used to determine if light should be switched on or off
*/
/****************************************************************************/
void SceneLevelOneA::FlickeringLight(double dt)
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
void SceneLevelOneA::Update(double dt)
{
	FPS = 1.f / (float)dt;
	camera.Update(dt);
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[0].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));

	Variables.f_rotatingTool += (float)(180 * dt);


	if (Application::IsKeyPressed('5'))
		Explorer::instance()->hp -= (float)(50.0f * dt);

	/*-------------------------[Death of the Explorer]-------------------------------*/
	Explorer::instance()->checkDead();
	UpdatePlayerDiesInteraction(dt);
	ContinueGameOrNot();

	if (Explorer::instance()->PlayerLife <= 0 && Variables.f_redScreenTimer > 8.0f)
	{
		ResetAll();
		Application::OpenGame();
	}

	/*-------------------------[End of Death Functions]-------------------------------*/



	/*-------------------------[Tool UI Functions]-------------------------------*/
	ToolsUI();
	MouseScrollToolSlot();
	MouseClickFunction(dt);
	/*-------------------------[End of Tool UI Functions]-------------------------------*/


	/*-------------------------[Suitcase Interaction]-------------------------------*/
	PickUpSuitcaseInteraction();

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	anima.Collapsing(dt);
	checkRubbleFall();
	checkDoor1(dt);
	checkDoor2();
	checkDoor3();
	checkDrop();
	EnvironmentAnimation(dt);
	AnimationCheck(dt);

	//wall collision DO NOT TOUCH
	for (int i = 0; i < 28; i++)
	{
		Collision(CollXSmall[i], CollXLarge[i], CollZSmall[i], CollZLarge[i]);
	}
    Collision(-235, -220, 98, 110);
	//mob stuff
	if (proximitycheck(-226, -160, 210, 218) && !activateDoor1)
	{
		Ghost.Spawn = true;

		if (Ghost.Spawn == true && Explorer::instance()->b_MonsterSound[0] == false)
		{
			Explorer::instance()->b_MonsterSound[0] = true;
			Application::MusicWillPlay(3, false);
		}
	}


	Ghost.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);//pos checker

	if (Ghost.Spawn)
	{
		Ghost.move(dt, 25);
		Collision(Ghost.MobPosX - 4, Ghost.MobPosX + 4, Ghost.MobPosZ - 4, Ghost.MobPosZ + 4);
	}
    
    //codes for changing to level1B
    if (proximitycheck(192, 216, -8, 8))
    {
        Application::SceneLevel1B();
    }

	if (anima.Collapse && Explorer::instance()->b_SoundEffect[0] == false)
	{
		Application::MusicWillPlay(1, false);
		Explorer::instance()->b_SoundEffect[0] = true;
	}

	FlickeringLight(dt);
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
void SceneLevelOneA::RenderMesh(Mesh*mesh, bool enableLight)
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
void SceneLevelOneA::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneLevelOneA::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneLevelOneA::RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float Tx, float Ty, float Tz, bool LightYN)
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
void SceneLevelOneA::Render()
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

	RenderScene();
	TestDoorRender();
	CollapseRubble();
	DropPortrait();
	RenderBarrel();

	ToolSelectionMouseScroll();
	RenderMouseScrollToolSlot();
	RenderToolIcon();

	//mob renders
	if (Ghost.Spawn)
	{
		RenderGhost(Ghost.MobPosX, Ghost.MobPosZ);
	}

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

	if (Notice)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Door is locked", Color(0, 1, 0), 4, 8, 7);
	}
	if (displayInteract1 || displayInteract2 || displayInteract3)
	{
		RenderInteract();
	}
    if (Key1Active)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Press Right Mouse to interact", Color(1, 0, 0), 3, 8.75f, 8);
    }


	if (Explorer::instance()->isDead == false)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_HEALTHBAR], Explorer::instance()->hp / 5, 1.0f, 1.0f, 90, 1, 0, 0, 0, 57, 0, false);
		RenderModelOnScreen(meshList[GEO_STAMINABAR], Explorer::instance()->stamina / 5, 1.0f, 1.0f, 90, 1, 0, 0, 0, 56, 0, false);
		modelStack.PopMatrix();
	}

	RenderPlayerDiesInteraction();


	RenderPickUpPickAxe();
	RenderPickUpSuitcaseText();

	for (float i = 0; i < Explorer::instance()->PlayerLife; ++i)
		RenderModelOnScreen(meshList[GEO_HEALTHICON], 3.f, 3.f, 3.f, 90, 1, 0, 0, (22.f + i), 18.5f, 1.0f, false);
}

/****************************************************************************/
/*!
\brief
This Function deletes openGL based stuff
*/
/****************************************************************************/
void SceneLevelOneA::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}