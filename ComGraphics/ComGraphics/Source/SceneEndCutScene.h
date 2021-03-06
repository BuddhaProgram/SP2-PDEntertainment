/**************************************************************************/
/*!
\file			SceneEndCutScene.h
\author			Matsuda Kenichi
\par			email: 150450F\@mymail.nyp.edu.sg
\brief
Class to define cutscene for the ending of the game
*/
/**************************************************************************/

#ifndef SCENEENDCUTSCENE_H
#define SCENEENDCUTSCENE_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include <vector>
#include <fstream>

using std::vector;
using std::ifstream;
using std::string;

/**************************************************************************/
/*!
Class SceneEndCutScene:
\brief
Define SceneEndCutScene and its method make the ending cutscene
*/
/**************************************************************************/

class SceneEndCutScene : public Scene
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

		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_MOUNTTEXT,

		GEO_MAINDOORLEFT,
		GEO_MAINDOORRIGHT,
		GEO_RUBBLE,
		GEO_PORTRAIT,

		GEO_PLANETFLOOR,
		GEO_FACILITYFLOOR,

		GEO_FACILITYOUT,
		GEO_FACILITYOUTWALL,
		GEO_FACILITYWALLS,
		GEO_FACILITYCEILINGS,

		// Animations when player dies
		GEO_DEADCOLOR,
		GEO_DEADBLACKSCREEN,

		GEO_SPACESHIP,
		GEO_REPAIRPOD,
		GEO_REPAIRDONE,

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
	SceneEndCutScene(); //Default constructor
	~SceneEndCutScene(); //Destructor

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Reset();
	virtual void Exit();

	Camera3 camera;

private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	//scene renders
	void RenderLevel1();
	void RenderFloor();
	void RenderSkyBox();
	void RenderSceneEndCutScene();

	//render functions 
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float Tx, float Ty, float Tz, bool LightYN);

	// Spaceship and Pod function
	bool b_RepairDone[3];
	bool b_startRepair;
	float f_RepairProcess;
	void RenderShipAndPod();

	void RenderRepairText();
	void UpdateRepairs(double dt);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Animation anima;

	MS modelStack, viewStack, projectionStack;

	Light light[1];

	float worldspin;


	Vector3 start;
	Vector3 end;
	GlobalVariables Variables;

	float FPS;
	bool displayInteract;

	float MoveCamera1;
	float MoveCamera2;
	bool CameraMove1;
	bool CameraMove2;

	float MoveQuad;
	bool QuadMove;

};


#endif