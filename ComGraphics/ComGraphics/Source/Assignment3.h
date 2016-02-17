#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include "PlayerStat.h"
#include "ToolSection.h"
#include "HostileMob.h"

class Assignment3 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_BOTTOM,
		GEO_TOP,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_FRONT,
		GEO_BACK,
		GEO_QUAD,
		GEO_PICKAXE,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_MOUNTTEXT,

		GEO_EARTH,
		GEO_MOON,
		GEO_PLANET,
		GEO_ASTEROID1,
		GEO_ASTEROID2,

		GEO_MAINDOORLEFT,
		GEO_MAINDOORRIGHT,
		GEO_RUBBLE,
		GEO_PORTRAIT,


		// Tools Interface
		GEO_TOOLUI,

        GEO_GHOST1,

        //player related
        GEO_HEALTH,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	Assignment3();
	~Assignment3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Reset();
	virtual void Exit();
	
private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderScene1();
    void RenderScene2();

	void ToolsUI();
	void UpdateToolSlot();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh* mesh, float size, float Rotate, float x, float y, float z, bool LightYN);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;
	Animation anima;

	MS modelStack, viewStack, projectionStack;

	Light light[1];

	float PlanetRotate;
	float AsteroidRotate;
	float AsteroidRotateF;
	float AsteroidMove;
	float AsteroidMoveS;

    //variables for scene changer
    int numScene;

    //sceneStart

    //scene 1

    //scene 2

    //sce
   

    Vector3 start ;
    Vector3 end;

	ToolSection Inventory;
	ToolUI::ToolType Tool;
    HostileMob Ghost;
    float FPS;
	int SlotIndex;

};

#endif