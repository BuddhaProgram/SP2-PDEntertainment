#include "SceneLevelOneA.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Misc.h"

#include "LoadTGA.h"
#include "Utility.h"
#include <sstream>
#include "GlobalVariables.h"


SceneLevelOneA::SceneLevelOneA()
{
}

SceneLevelOneA::~SceneLevelOneA()
{
}

void SceneLevelOneA::Init()
{
    // Init VBO here

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glDisable(GL_CULL_FACE);

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
    light[0].power = 5.0f;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;
    light[0].cosCutoff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
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
    camera.Init(Vector3(0, 10, 424), Vector3(0, 10, 0), Vector3(0, 1, 0));
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

    meshList[GEO_RUBBLE] = MeshBuilder::GenerateOBJ("Rubble", "OBJ//Rubble.obj");
	meshList[GEO_RUBBLE]->textureID = LoadTGA("Image//InsideWALL.tga");
    meshList[GEO_PORTRAIT] = MeshBuilder::GenerateOBJ("Portrait", "OBJ//Portrait.obj");
    meshList[GEO_PORTRAIT]->textureID = LoadTGA("Image//Scream.tga");

    // Tools Interface and It's Icons

    meshList[GEO_FACILITYFLOOR] = MeshBuilder::GenerateQuad("Facility Floor", Color(0.623f, 0.467f, 0.467f));
    meshList[GEO_FACILITYFLOOR]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
    meshList[GEO_FACILITYFLOOR]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
    meshList[GEO_FACILITYFLOOR]->material.kSpecular.Set(1, 1, 1);

    meshList[GEO_DOORSWITCH] = MeshBuilder::GenerateCube("Switch", Color(0.623f, 0.467f, 0.467f));
    meshList[GEO_DOORSWITCH]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
    meshList[GEO_DOORSWITCH]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
    meshList[GEO_DOORSWITCH]->material.kSpecular.Set(1, 1, 1);

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


    meshList[GEO_GHOST1] = MeshBuilder::GenerateOBJ("ghost placeholder", "OBJ//GhostPlaceholder.obj");
    meshList[GEO_GHOST1]->textureID = LoadTGA("Image//Ghostplaceholder.tga");

	meshList[GEO_SLIDEDOORTOP] = MeshBuilder::GenerateOBJ("Hand", "OBJ//SlideDoorTop.obj");
	meshList[GEO_SLIDEDOORTOP]->textureID = LoadTGA("Image//SlidingDoorTop.tga");
	meshList[GEO_SLIDEDOORBTM] = MeshBuilder::GenerateOBJ("Hand", "OBJ//SlideDoorBtm.obj");
	meshList[GEO_SLIDEDOORBTM]->textureID = LoadTGA("Image//SlidingDoorBtm.tga");

    meshList[GEO_SPAWNPOINT] = MeshBuilder::GenerateOBJ("Spawn", "OBJ//SpawnPoint.obj");
    meshList[GEO_SPAWNPOINT]->textureID = LoadTGA("Image//SpawnPoint.tga");


    Mtx44 projection;
    projection.SetToPerspective(45.0f, 16.f / 9.f, 0.1f, 10000.f);
    projectionStack.LoadMatrix(projection);

    Ghost.setSpawnGhost(-30, -15);
}

static float LSPEED = 10.f;


void SceneLevelOneA::Reset()
{
}

void SceneLevelOneA::Collision(float smallx, float largex, float smallz, float largez)
{
    if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z >= smallz) && (camera.position.z <= smallz + 3.f)){ camera.position.z = smallz; }
    if ((camera.position.x >= smallx) && (camera.position.x <= largex) && (camera.position.z <= largez) && (camera.position.z >= largez - 3.f)){ camera.position.z = largez; }
    if ((camera.position.z >= smallz) && (camera.position.z <= largez) && (camera.position.x >= smallx) && (camera.position.x <= smallx + 3.f)){ camera.position.x = smallx; }
    if ((camera.position.z >= smallz) && (camera.position.z <= largez) && (camera.position.x <= largex) && (camera.position.x >= largex - 3.f)){ camera.position.x = largex; }
}

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

void SceneLevelOneA::Update(double dt)
{
    light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
    light[0].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));
    FPS = 1.f / (float)dt;
    //worldspin += (float)(dt);

    /*-------------------------[End of Tool UI Functions]-------------------------------*/

    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    //camera.Update(dt);

    anima.OBJAnimation(dt);
    anima.Collapsing(dt);
	if (activateDoor1) {anima.OpenSlideDoor1(dt);}
	if (activateDoor2)
	{
		anima.OpenSlideDoor2(dt);
	}
	else if (!activateDoor2)
	{
		anima.CloseSlideDoor2(dt);
	}


    if (proximitycheck(-13, 13, -105, -70))
    {
        displayInteract = true;
    }
    else
    {
        displayInteract = false;
    }

    //wall collision DO NOT TOUCH
    for (int i = 0; i < 28; i++)
    {
        Collision(CollXSmall[i], CollXLarge[i], CollZSmall[i], CollZLarge[i]);
    }


	if (/*!(anima.WithinArea(-20, 20, 400, 450))*/  !(camera.position.x >= -20 && camera.position.x <= 20 && camera.position.z >= 400 && camera.position.z <= 450))
	{
		anima.Collapse = true;
		if (anima.RubbleCollapse <= 0)
		{
			anima.Collapse = false;
		}
	}
	if (!anima.Collapse)
	{
		Collision(-25, 25, 430, 460);
	}


	if (proximitycheck(170, 188, 190, 200))
	{
		displayInteract = true;
	}
	else
	{
		displayInteract = false;
	}
	if (Application::IsKeyPressed('E'))
	{
		if (proximitycheck(150, 200, 200, 300))
		{
			displayInteract = false;
			if (Key_1)
			{
				activateDoor1 = true;
			}
			else
			{
				Notice = true;
			}
		}
	}
	if (!proximitycheck(170, 188, 190, 200))
	{
		Notice = false;
	}
	if (anima.toSlideDoorBtm)
	{
		Collision(150, 200, 180, 200);
	}


	std::cout << activateDoor2 << std::endl;

	if (proximitycheck(-208, -176, 225, 235))
	{
		displayInteract = true;
	}
	else
	{
		displayInteract = false;
	}
	if (Application::IsKeyPressed('E') && proximitycheck(-204, -180, 235, 240))
	{
		activateDoor2 = true;	
		displayInteract = false;
	}

	if (Ghost.Spawn)
	{
		activateDoor2 = false;
	}

	if (anima.toSlideDoorBtm2)
	{
		Collision(-208, -176, 225, 235);
	}

	/*if (!proximitycheck(-208, -176, 245, 255))
	{
		activateDoor2 = false;
	}
	*/	


    if (Application::IsKeyPressed('J'))
    {
        Ghost.Spawn = true;
    }

    camera.Update(dt);
    //mob stuff
    if (proximitycheck(-226, -172, 210,228)&&!activateDoor1)
    {
        Ghost.Spawn = true;
    }


    Ghost.checkPlayerPos(dt, 5, 1, camera.position.x, camera.position.z);//pos checker

    if (Ghost.Spawn)
    {
        Ghost.move(dt, 50);
    }
    if (proximitycheck(-220,-200, 120, 140) && !activateDoor1)
    {
        displayInteract = true;
        if (Application::IsKeyPressed('E'))
        {
            activateDoor1 = true;
            Ghost.Spawn = false;
        }
    }
    
}

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

void SceneLevelOneA::RenderModelOnScreen(Mesh* mesh, float size, float Rotate, int rX, int rY, int rZ, float x, float y, float z, bool LightYN)
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
	modelStack.Rotate(Rotate, (float)rX, (float)rY, (float)rZ);

    RenderMesh(mesh, LightYN);

    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}

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

    modelStack.PushMatrix();
    modelStack.Translate(-200,0,120);
    modelStack.Scale(5, 5, 5);
    RenderMesh(meshList[GEO_DOORSWITCH], true);
    modelStack.PopMatrix();

    //mob renders
    if (Ghost.Spawn)
    {
        RenderGhost(Ghost.MobPosX, Ghost.MobPosZ);
    }

    RenderTextOnScreen(meshList[GEO_TEXT], "FPS :" + std::to_string(FPS), Color(0, 1, 0), 2, 0, 1);
    RenderTextOnScreen(meshList[GEO_TEXT], "POS (" + std::to_string(camera.position.x) + "," + std::to_string(camera.position.y) + "," + std::to_string(camera.position.z) + ")", Color(1, 0, 0), 2, 0, 2);
    RenderTextOnScreen(meshList[GEO_TEXT], "TAR (" + std::to_string(camera.target.x) + "," + std::to_string(camera.target.y) + "," + std::to_string(camera.target.z) + ")", Color(1, 0, 0), 2, 0, 3);
    RenderTextOnScreen(meshList[GEO_TEXT], "VIEW (" + std::to_string(camera.view.x) + "," + std::to_string(camera.view.y) + "," + std::to_string(camera.view.z) + ")", Color(1, 0, 0), 2, 0, 4);
    RenderTextOnScreen(meshList[GEO_TEXT], "UP (" + std::to_string(camera.up.x) + "," + std::to_string(camera.up.y) + "," + std::to_string(camera.up.z) + ")", Color(1, 0, 0), 2, 0, 5);
    RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0.25f, 0.9f, 0.82f), 4, 10, 7);

	if (Notice)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "NO KEY", Color(0, 1, 0), 4, 10, 7);
	}
    if (displayInteract)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Press E to interact", Color(1, 0, 0), 3, 8.75f, 12);
    }
}

void SceneLevelOneA::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}