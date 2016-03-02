#include "SceneLevelTwo.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "LoadTGA.h"
#include "Utility.h"
#include <sstream>
#include "GlobalVariables.h"


SceneLevelTwo::SceneLevelTwo()
{
	Switch1Int = false;
	Switch2Int = false;
	Switch1Rot = 45.f;
	Switch2Rot = 45.f;
	Switch1Press = false;
	Switch2Press = false;
	transSpikeDoor = false;
	closeDoors = false;
	timerDoor = 3;
	openDoor1 = false;
	openDoor2 = false;
	invisWALLDisappear = false;
	puzzling = false;
	transSpikeWall2 = 0;
	hitWall = false;

	countdown = 0;
	JumpScare = false;
	timer = false;
}

SceneLevelTwo::~SceneLevelTwo()
{
}

void SceneLevelTwo::Init()
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
    camera.Init(Vector3(0, 10, 400), Vector3(0, 10, -1), Vector3(0, 1, 0));
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

	meshList[GEO_HEALTHICON] = MeshBuilder::GenerateQuad("HealthIcon", Color(1, 1, 1));
	meshList[GEO_HEALTHICON]->textureID = LoadTGA("Image//Heart1.tga");

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
    meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

    meshList[GEO_RUBBLE] = MeshBuilder::GenerateOBJ("Rubble", "OBJ//Rubble.obj");
    meshList[GEO_PORTRAIT] = MeshBuilder::GenerateOBJ("Portrait", "OBJ//Portrait.obj");
    meshList[GEO_PORTRAIT]->textureID = LoadTGA("Image//Scream.tga");

	meshList[GEO_GHOST1] = MeshBuilder::GenerateOBJ("Alien", "OBJ//AlienOne.obj");
	meshList[GEO_GHOST1]->textureID = LoadTGA("Image//Alien1.tga");

    // Tools Interface and It's Icons

    meshList[GEO_FACILITYFLOOR] = MeshBuilder::GenerateQuad("Facility Floor", Color(1, 1, 1));
    meshList[GEO_FACILITYFLOOR]->textureID = LoadTGA("Image//InsideFLOOR.tga");

    meshList[GEO_FACILITYWALLS] = MeshBuilder::GenerateQuad("Facility Wall", Color(1, 1, 1));
    meshList[GEO_FACILITYWALLS]->textureID = LoadTGA("Image//InsideWALL.tga");

    meshList[GEO_FACILITYCEILINGS] = MeshBuilder::GenerateQuad("Facility Ceiling", Color(1, 1, 1));
    meshList[GEO_FACILITYCEILINGS]->textureID = LoadTGA("Image//InsideCEILING.tga");

    meshList[GEO_SLIDEDOORTOP] = MeshBuilder::GenerateOBJ("Hand", "OBJ//SlideDoorTop.obj");
    meshList[GEO_SLIDEDOORTOP]->textureID = LoadTGA("Image//SlidingDoorTop.tga");
    meshList[GEO_SLIDEDOORBTM] = MeshBuilder::GenerateOBJ("Hand", "OBJ//SlideDoorBtm.obj");
    meshList[GEO_SLIDEDOORBTM]->textureID = LoadTGA("Image//SlidingDoorBtm.tga");

    meshList[GEO_SPAWNPOINT] = MeshBuilder::GenerateOBJ("Spawn", "OBJ//SpawnPoint.obj");
    meshList[GEO_SPAWNPOINT]->textureID = LoadTGA("Image//SpawnPoint.tga");

	meshList[GEO_TRAPWALL] = MeshBuilder::GenerateOBJ("SPIKEWALL", "OBJ//walltrap.obj");
	meshList[GEO_TRAPWALL]->textureID = LoadTGA("Image//WallTrap.tga");

	meshList[GEO_HEALTHBAR] = MeshBuilder::GenerateQuad("Healthbar", Color(1, 0, 0));
	meshList[GEO_STAMINABAR] = MeshBuilder::GenerateQuad("STAMINABAR", Color(0, 1, 0));

	meshList[GEO_LIGHTGREEN] = MeshBuilder::GenerateOBJ("green light", "OBJ//PuzzleLight.obj");
	meshList[GEO_LIGHTGREEN]->textureID = LoadTGA("Image//PuzzleLightGREEN.tga");

	meshList[GEO_LIGHTRED] = MeshBuilder::GenerateOBJ("red light", "OBJ//PuzzleLight.obj");
	meshList[GEO_LIGHTRED]->textureID = LoadTGA("Image//PuzzleLightRED.tga");

    meshList[GEO_LEVER] = MeshBuilder::GenerateOBJ("lever", "OBJ//PuzzleLever.obj");
    meshList[GEO_LEVER]->textureID = LoadTGA("Image//PuzzleLever.tga");

	/*--------------------[Used as a background for Dead Scene]--------------------*/
	meshList[GEO_DEADCOLOR] = MeshBuilder::GenerateQuad("DeadScreen", Color(1, 0, 0));
	meshList[GEO_DEADBLACKSCREEN] = MeshBuilder::GenerateQuad("DeadSCreenTwo", Color(0, 0, 0));

    Mtx44 projection;
    projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
    projectionStack.LoadMatrix(projection);

    //scene changer inits.............
    //scene changer init end.............
	Explorer::instance()->SavePoint = camera.position;
	ScareGhost.setSpawnGhost(20, 45);
}

static float LSPEED = 10.f;

void SceneLevelTwo::Reset()
{
	Explorer::instance()->hp = 100;
	Explorer::instance()->stamina = 100;
	Explorer::instance()->isDead = false;
	Explorer::instance()->SavePoint = (0.0f, 0.0f, 0.0f);
	Variables.f_redScreenTimer = 0.0f;
	Switch1Int = false;
	Switch2Int = false;
	Switch1Rot = 45.f;
	Switch2Rot = 45.f;
	Switch1Press = false;
	Switch2Press = false;
	transSpikeDoor = false;
	closeDoors = false;
	timerDoor = 3;
	openDoor1 = false;
	openDoor2 = false;
	invisWALLDisappear = false;
	puzzling = false;
	transSpikeWall2 = 0;
	hitWall = false;



	anima.QPDOOR1_BOT = 0;
	anima.QPDOOR1_TOP = 0;
	anima.QP_TOPDOOR1 = false;
	anima.QP_BOTDOOR1 = false;

	anima.QPDOOR2_TOP = 0;
	anima.QPDOOR2_BOT = 0;
	anima.QP_TOPDOOR2 = false;
	anima.QP_BOTDOOR2 = false;

	anima.QPDOOR3_TOP = 0;
	anima.QPDOOR3_BOT = 0;
	anima.QP_TOPDOOR3 = false;
	anima.QP_BOTDOOR3 = false;

	anima.QPDOOR4_TOP = 10;
	anima.QPDOOR4_BOT = -6;
	anima.QP_TOPDOOR4 = false;
	anima.QP_BOTDOOR4 = false;

	anima.QPDOOR5_TOP = 0;
	anima.QPDOOR5_BOT = 0;
	anima.QP_TOPDOOR5 = false;
	anima.QP_BOTDOOR5 = false;

	anima.DoorSlideTop_5 = 10;
	anima.DoorSlideBtm_5 = -6;
	anima.ClosingDoorTop5 = true;
	anima.ClosingDoorBtm5 = true;

	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->checkSavePoint[i] = false;
	}

	activateDoor1 = false;

	ScareGhost.setSpawnGhost(20, 45);
	ScareGhost.health = 8;
	ScareGhost.Spawn = false;

	countdown = 0;
	JumpScare = false;
	timer = false;
}

void SceneLevelTwo::ResetAll()
{
	Explorer::instance()->hp = 100;
	Explorer::instance()->isDead = false;
	Explorer::instance()->PlayerLife = 3;
	Explorer::instance()->SavePoint = (0.0f, 0.0f, 0.0f);
	Variables.f_redScreenTimer = 0.0f;

	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->checkSavePoint[i] = false;
	}
}

void SceneLevelTwo::Collision(float smallx, float largex, float smallz, float largez)
{
    if ((camera.position.x > smallx) && (camera.position.x < largex) && (camera.position.z > smallz) && (camera.position.z < smallz + 5.f)){ camera.position.z = smallz; }
    if ((camera.position.x > smallx) && (camera.position.x < largex) && (camera.position.z < largez) && (camera.position.z > largez - 5.f)){ camera.position.z = largez; }
    if ((camera.position.z > smallz) && (camera.position.z < largez) && (camera.position.x > smallx) && (camera.position.x < smallx + 5.f)){ camera.position.x = smallx; }
    if ((camera.position.z > smallz) && (camera.position.z < largez) && (camera.position.x < largex) && (camera.position.x > largex - 5.f)){ camera.position.x = largex; }

	camera.target = Vector3(
		sin(Math::DegreeToRadian(camera.rotationY)) * cos(Math::DegreeToRadian(camera.rotationX)) + camera.position.x,
		sin(Math::DegreeToRadian(camera.rotationX)) + camera.position.y,
		cos(Math::DegreeToRadian(camera.rotationX)) * cos(Math::DegreeToRadian(camera.rotationY)) + camera.position.z
		);
}

void SceneLevelTwo::SpecialCollision(float smallx, float largex, float smallz, float largez)
{
	if ((camera.position.x > smallx) && (camera.position.x < largex) && (camera.position.z > smallz) && (camera.position.z < smallz + 5.f)){ camera.position.z = smallz; hitWall = true; }
	if ((camera.position.x > smallx) && (camera.position.x < largex) && (camera.position.z < largez) && (camera.position.z > largez - 5.f)){ camera.position.z = largez; hitWall = true; }
	if ((camera.position.z > smallz) && (camera.position.z < largez) && (camera.position.x > smallx) && (camera.position.x < smallx + 5.f)){ camera.position.x = smallx; hitWall = true; }
	if ((camera.position.z > smallz) && (camera.position.z < largez) && (camera.position.x < largex) && (camera.position.x > largex - 5.f)){ camera.position.x = largex; hitWall = true; }

	camera.target = Vector3(
		sin(Math::DegreeToRadian(camera.rotationY)) * cos(Math::DegreeToRadian(camera.rotationX)) + camera.position.x,
		sin(Math::DegreeToRadian(camera.rotationX)) + camera.position.y,
		cos(Math::DegreeToRadian(camera.rotationX)) * cos(Math::DegreeToRadian(camera.rotationY)) + camera.position.z
		);
}

bool SceneLevelTwo::proximitycheck(float smallx, float largex, float smallz, float largez)
{
    //this function checks if the camera is close to a side of the object
    bool result = false;
    if ((camera.position.x >= smallx - 2.f) && (camera.position.x <= smallx) && (camera.position.z >= smallz) && (camera.position.z <= largez)){ result = true; }
    if ((camera.position.x <= largex + 2.f) && (camera.position.x >= largex) && (camera.position.z >= smallz) && (camera.position.z <= largez)){ result = true; }
    if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z >= smallz - 2.f) && (camera.position.z <= smallz)){ result = true; }
    if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z <= largez + 2.f) && (camera.position.z >= largez)){ result = true; }
    return result;
}

void SceneLevelTwo::ToolsUI()
{

}

void SceneLevelTwo::ToolSelectionMouseScroll()
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

void SceneLevelTwo::RenderToolIcon()
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

void SceneLevelTwo::MouseScrollToolSlot()
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

void SceneLevelTwo::RenderMouseScrollToolSlot()
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

void SceneLevelTwo::MouseClickFunction(double dt)
{
    if (Application::IsKeyPressed(VK_LBUTTON) && Variables.b_LockSwing == false && Variables.b_LockSwingDebounce == false && Explorer::instance()->stamina >= 20)
    {
        Variables.b_LockSwing = true;
        Variables.b_LockSwingDebounce = true;
        Explorer::instance()->stamina -= 20;
    }

    if (Variables.b_LockSwingDebounce == true)
    {
        Variables.RotateX -= 360.0f * (float)dt;

        if (Variables.RotateX <= -45.0f)
        {
            Variables.RotateX = -45.0f;
            Variables.b_LockSwingDebounce = false;
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
}

void SceneLevelTwo::UpdatePlayerDiesInteraction(double dt)
{
	if (Explorer::instance()->isDead == true)
	{
		Variables.f_redScreenTimer += (float)(dt);
		light[0].power = 0.0f;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}
}

void SceneLevelTwo::ContinueGameOrNot()
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

			light[0].power = 1.0f;
			glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
			Reset();
		}

		else if (Application::IsKeyPressed('N'))
		{
			Explorer::instance()->hp = 100;
			Explorer::instance()->isDead = false;
			Explorer::instance()->PlayerLife = 3;
			Explorer::instance()->SavePoint = (0.0f, 0.0f, 0.0f);
			Application::OpenGame();
		}
	}
}

void SceneLevelTwo::checkPlayerPosMisc()
{
	Misc.camX = camera.position.x;
	Misc.camY = camera.position.y;
	Misc.camZ = camera.position.z;
}

void SceneLevelTwo::SomeUpdates(double dt)
{
	//check if touch wall
	if (hitWall == true)
	{
		Explorer::instance()->isDead = true;
	}
	//stuff
	if (openDoor1 == true)
	{
		anima.QP_TOPDOOR1 = true;
		anima.QP_BOTDOOR1 = true;
	}

	if (openDoor2 == true)
	{
		anima.QP_TOPDOOR2 = true;
		anima.QP_BOTDOOR2 = true;
	}

	if (timerDoor == 0)
	{
		anima.QP_TOPDOOR4 = true;
		if (anima.QPDOOR4_TOP <= 0)
		{
			anima.QP_TOPDOOR4 = false;
		}
		anima.QP_BOTDOOR4 = true;
		Collision(-20, 20, -305, -295);
	}

	if (Misc.WithinArea(-12, 12, -105, -95) && Application::IsKeyPressed('E') && openDoor1 == true && openDoor2 == true)
	{
		invisWALLDisappear = true;
	}

	if (invisWALLDisappear == false)
	{
		Collision(-20, 20, -110, -100);
	}
	else
	{
		timerDoor -= (float)dt;
		if (timerDoor <= 0)
		{
			timerDoor = 0;
		}
	}

	if (anima.QP_TOPDOOR1 && anima.QP_BOTDOOR1)//left door
	{
		anima.OpenQPDOOR1(dt);
	}
	else
	{
		Collision(-96, -80, -20, 22);
	}

	if (anima.QP_TOPDOOR2 && anima.QP_BOTDOOR2)//right door
	{
		anima.OpenQPDOOR2(dt);
	}
	else
	{
		Collision(80, 96, -20, 22);
	}

	if (Switch1Press == true && Switch2Press == true)
	{
		anima.QP_TOPDOOR3 = true;
		anima.QP_BOTDOOR3 = true;
	}

	if (anima.QP_TOPDOOR3 && anima.QP_BOTDOOR3)//first frontfacing door
	{
		anima.OpenQPDOOR3(dt);
	}
	else
	{
		Collision(-20, 20, -105, -95);
	}

	if (anima.QP_TOPDOOR4 && anima.QP_BOTDOOR4)
	{
		anima.OpenQPDOOR4(dt);
		Collision(-20, 20, -305, -295);
	}

	if (anima.QP_TOPDOOR5 && anima.QP_BOTDOOR5)
	{
		anima.OpenQPDOOR5(dt);
	}
	else
	{
		Collision(320, 360, -30, -10);
	}

	if (openDoor1 == false && proximitycheck(-96, -80, -20, 22) && Application::IsKeyPressed('E'))
	{
		openDoor1 = true;
	}

	if (openDoor2 == false && proximitycheck(80, 96, -20, 22) && Application::IsKeyPressed('E'))
	{
		openDoor2 = true;
	}

	if (Misc.WithinArea(-76, 76, -272, -120) && timerDoor == 0)
	{
		Explorer::instance()->isDead = true;
	}

	if (Misc.WithinArea(-76, 76, 128, 360))

		//trapwall collision
		SpecialCollision(-76 + transSpikeDoor, -60 + transSpikeDoor, 127, 362);

	if (Misc.WithinArea(-76, 76, 127, 361))

	{
		transSpikeDoor += 0.7f;
	}
	if (Misc.WithinArea(-12, 12, 80, 118))
	{
		closeDoors = true;
	}

	if (closeDoors == true)
	{
		anima.CloseSlideDoor5(dt);
		Collision(-20, 20, 115, 125);
	}

	if (transSpikeDoor > 140)
	{
		transSpikeDoor = 140;
	}

	SpecialCollision(240, 400, -392 + transSpikeWall2, -376 + transSpikeWall2);

	if (Misc.WithinArea(244, 360, -60, -40))
	{
		puzzling = true;
	}
	if (puzzling == true)
	{
		transSpikeWall2 += (float)dt;
	}
	if (Misc.WithinArea(324, 356, -20, -4))
	{
		Application::EndingScene();
	}

	if ((Switches.SwitchPuzzleTwo() == true))
	{
		anima.QP_TOPDOOR5 = true;
		anima.QP_BOTDOOR5 = true;
	}
}

void SceneLevelTwo::SwitchCollisionChecker()
{
	Collision(252, 320, -50, -34);
}

void SceneLevelTwo::PuzzleTwoSwitchCheck(double dt)
{
	Variables.f_SwitchDebounce += (float)dt;
	if (camera.position.x > 300 && camera.position.x < 312 && camera.position.z > -55 && camera.position.z < -30)
	{
		if (Application::IsKeyPressed(VK_RBUTTON) && Variables.f_SwitchDebounce > 0.5f)
		{
			if (Variables.b_SwitchAnimate[0] == false)
				Variables.b_SwitchAnimate[0] = true;

			else
				Variables.b_SwitchAnimate[0] = false;

			if (Switches.b_PuzzleTwo[0] == false)
				Switches.b_PuzzleTwo[0] = true;

			else
				Switches.b_PuzzleOne[0] = false;

			if (Switches.b_PuzzleTwo[3] == false)
				Switches.b_PuzzleTwo[3] = true;

			else
				Switches.b_PuzzleTwo[3] = false;

			if (Switches.b_PuzzleTwo[4] == false)
				Switches.b_PuzzleTwo[4] = true;

			else
				Switches.b_PuzzleTwo[4] = false;

			Variables.f_SwitchDebounce = 0.0f;
		}
	}

	if (camera.position.x > 288 && camera.position.x < 300 && camera.position.z > -55 && camera.position.z < -30)
	{
		if (Application::IsKeyPressed(VK_RBUTTON) && Variables.f_SwitchDebounce > 0.5f)
		{
			if (Variables.b_SwitchAnimate[1] == false)
				Variables.b_SwitchAnimate[1] = true;

			else
				Variables.b_SwitchAnimate[1] = false;

			if (Switches.b_PuzzleTwo[0] == false)
				Switches.b_PuzzleTwo[0] = true;

			else
				Switches.b_PuzzleTwo[0] = false;

			Variables.f_SwitchDebounce = 0.0f;
		}
	}

	if (camera.position.x > 276 && camera.position.x < 288 && camera.position.z > -55 && camera.position.z < -30)
	{
		if (Application::IsKeyPressed(VK_RBUTTON) && Variables.f_SwitchDebounce > 0.5f)
		{
			if (Variables.b_SwitchAnimate[2] == false)
				Variables.b_SwitchAnimate[2] = true;

			else
				Variables.b_SwitchAnimate[2] = false;

			if (Switches.b_PuzzleTwo[1] == false)
				Switches.b_PuzzleTwo[1] = true;

			else
				Switches.b_PuzzleTwo[1] = false;

			if (Switches.b_PuzzleTwo[3] == false)
				Switches.b_PuzzleTwo[3] = true;

			else
				Switches.b_PuzzleTwo[3] = false;

			if (Switches.b_PuzzleTwo[4] == false)
				Switches.b_PuzzleTwo[4] = true;

			else
				Switches.b_PuzzleTwo[4] = false;

			Variables.f_SwitchDebounce = 0.0f;
		}
	}

	if (camera.position.x > 264 && camera.position.x < 276 && camera.position.z > -55 && camera.position.z < -30)
	{
		if (Application::IsKeyPressed(VK_RBUTTON) && Variables.f_SwitchDebounce > 0.5f)
		{
			if (Variables.b_SwitchAnimate[3] == false)
				Variables.b_SwitchAnimate[3] = true;

			else
				Variables.b_SwitchAnimate[3] = false;

			if (Switches.b_PuzzleTwo[0] == false)
				Switches.b_PuzzleTwo[0] = true;

			else
				Switches.b_PuzzleTwo[0] = false;

			if (Switches.b_PuzzleTwo[1] == false)
				Switches.b_PuzzleTwo[1] = true;

			else
				Switches.b_PuzzleTwo[1] = false;

			if (Switches.b_PuzzleTwo[2] == false)
				Switches.b_PuzzleTwo[2] = true;

			else
				Switches.b_PuzzleTwo[2] = false;

			Variables.f_SwitchDebounce = 0.0f;
		}
	}
}

void SceneLevelTwo::LogicAnimationSwitches(double dt)
{
	if (Variables.b_SwitchAnimate[0] == true)
	{
		Variables.f_SwitchRotateOne -= (float)(180.0f * dt);

		if (Variables.f_SwitchRotateOne <= -90.0f)
		{
			Variables.f_SwitchRotateOne = -90.0f;
		}
	}

	if (Variables.b_SwitchAnimate[0] == false)
	{
		Variables.f_SwitchRotateOne += (float)(180.0f * dt);

		if (Variables.f_SwitchRotateOne >= 0.0f)
		{
			Variables.f_SwitchRotateOne = 0.0f;
		}
	}

	if (Variables.b_SwitchAnimate[1] == true)
	{
		Variables.f_SwitchRotateTwo -= (float)(180.0f * dt);

		if (Variables.f_SwitchRotateTwo <= -90.0f)
		{
			Variables.f_SwitchRotateTwo = -90.0f;
		}
	}

	if (Variables.b_SwitchAnimate[1] == false)
	{
		Variables.f_SwitchRotateTwo += (float)(180.0f * dt);

		if (Variables.f_SwitchRotateTwo >= 0.0f)
		{
			Variables.f_SwitchRotateTwo = 0.0f;
		}
	}

	if (Variables.b_SwitchAnimate[2] == true)
	{
		Variables.f_SwitchRotateThree -= (float)(180.0f * dt);

		if (Variables.f_SwitchRotateThree <= -90.0f)
		{
			Variables.f_SwitchRotateThree = -90.0f;
		}
	}

	if (Variables.b_SwitchAnimate[2] == false)
	{
		Variables.f_SwitchRotateThree += (float)(180.0f * dt);

		if (Variables.f_SwitchRotateThree >= 0.0f)
		{
			Variables.f_SwitchRotateThree = 0.0f;
		}
	}

	if (Variables.b_SwitchAnimate[3] == true)
	{
		Variables.f_SwitchRotateFour -= (float)(180.0f * dt);

		if (Variables.f_SwitchRotateFour <= -90.0f)
		{
			Variables.f_SwitchRotateFour = -90.0f;
		}
	}

	if (Variables.b_SwitchAnimate[3] == false)
	{
		Variables.f_SwitchRotateFour += (float)(180.0f * dt);

		if (Variables.f_SwitchRotateFour >= 0.0f)
		{
			Variables.f_SwitchRotateFour = 0.0f;
		}
	}
}

void SceneLevelTwo::FlickeringLight(double dt)
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

void SceneLevelTwo::Update(double dt)
{
    FPS = 1.f / (float)dt;
    //worldspin += (float)(dt);

    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    SwitchCheck(dt);
    //wall collision
    for (int i = 0; i < 60; i++)
    {
        Collision(CollXSmall[i], CollXLarge[i], CollZSmall[i], CollZLarge[i]);
    }

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

	std::cout << Explorer::instance()->f_FlickeringLight << std::endl;
	checkPlayerPosMisc();

	/*-------------------------[Switches Function]-------------------------------*/
	LogicAnimationSwitches(dt);
	PuzzleTwoSwitchCheck(dt);
	SwitchCollisionChecker();
	RenderPuzzle();
	Switches.SwitchPuzzleTwo();


	FlickeringLight(dt);

	SomeUpdates(dt);
	camera.Update(dt);
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[0].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));
	ScareGhost.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);
	SomeUpdates(dt);
	RenderJumpScare();
	if (!JumpScare)
	{
		camera.Update(dt);
	}

	if (Application::IsKeyPressed('Z'))
	{
		Explorer::instance()->InsertToolSlot(ToolUI::Pickaxe);
	}
	if (ScareGhost.Spawn)
	{
		ScareGhost.move(dt, 25);
	}
}

void SceneLevelTwo::RenderMesh(Mesh*mesh, bool enableLight)
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

void SceneLevelTwo::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneLevelTwo::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneLevelTwo::RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float Tx, float Ty, float Tz, bool LightYN)
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

void SceneLevelTwo::Render()
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

    ToolSelectionMouseScroll();
    RenderMouseScrollToolSlot();
    RenderToolIcon();

    RenderScene();
	RenderTraps();

	RenderPuzzle();
	if (ScareGhost.Spawn)
	{
		RenderGhost1();
	}

    RenderTextOnScreen(meshList[GEO_TEXT], "FPS :" + std::to_string(FPS), Color(0, 1, 0), 2, 0, 1);
    RenderTextOnScreen(meshList[GEO_TEXT], "POS (" + std::to_string(camera.position.x) + "," + std::to_string(camera.position.y) + "," + std::to_string(camera.position.z) + ")", Color(1, 0, 0), 2, 0, 2);
    RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0.25f, 0.9f, 0.82f), 4, 9.8f, 7);

	if (Explorer::instance()->isDead == false)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_HEALTHBAR], Explorer::instance()->hp / 5, 1.0f, 1.0f, 90, 1, 0, 0, 0, 57, 0, false);
		RenderModelOnScreen(meshList[GEO_STAMINABAR], Explorer::instance()->stamina / 5, 1.0f, 1.0f, 90, 1, 0, 0, 0, 56, 0, false);
		modelStack.PopMatrix();
	}

    if (displayInteract1 /*|| displayInteract2 || displayInteract3*/)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Press E to interact", Color(1, 0, 0), 3, 8.75f, 8);
    }

    if (Switch1Int || Switch2Int)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Press Right mouse to interact", Color(1, 0, 0), 3, 8.75f, 8);
    }

	if (timerDoor != 0 && invisWALLDisappear == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "YOU HAVE " + std::to_string((int)timerDoor) +  "SECONDS. RUN.", Color(1, 0, 0), 3, 8.75f, 8);
	}

	RenderPlayerDiesInteraction();

	for (float i = 0; i < Explorer::instance()->PlayerLife; ++i)
		RenderModelOnScreen(meshList[GEO_HEALTHICON], 3.f, 3.f, 3.f, 90, 1, 0, 0, (22.f + i), 18.5f, 1.0f, false);

	if (JumpScare)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_GHOST1], 50, 50, 50, -90, 0, 1, 0, 0.8f, 0, 0, false);
		modelStack.PopMatrix();
	}
}

void SceneLevelTwo::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}