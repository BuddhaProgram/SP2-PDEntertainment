#ifndef OPENINGCUTSCENE2_H
#define OPENINGCUTSCENE2_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "Misc.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include "HostileMob.h"
#include "MobGhost.h"

class OpeningCutScene2 : public Scene
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

		GEO_PLANETFLOOR,
		GEO_FACILITYFLOOR,

		GEO_FACILITYOUT,
		GEO_FACILITYOUTWALL,
		GEO_FACILITYWALLS,
		GEO_FACILITYCEILINGS,

		GEO_DEADBODY,
		GEO_BLOOD1,


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
	OpeningCutScene2();
	~OpeningCutScene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Reset();
	virtual void Exit();

	Camera3 camera;
private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	//scene renders
	void RenderSceneStart();
	void RenderSkyBox();
	void RenderFloor();

	//map rendering
	void RenderDownWall(int xPosLarge, int xPosSmall, int zPos);//positive Z facing wall
	void RenderUpWall(int xPosLarge, int xPosSmall, int zPos);//negative Z facing Wall
	void RenderRightWall(int zPosLarge, int zPosSmall, int xPos);// positive X facing wall
	void RenderLeftWall(int zPosLarge, int zPosSmall, int xPos);//negative X facing wall

	//render functions 
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float x, float y, float z, bool LightYN);
	void RenderTextWord();

	// Interactions to change to FirstCutScene
	void ChangeFirstCutScene();

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Animation anima;

	MS modelStack, viewStack, projectionStack;

	Light light[1];


	//variables for scene changer

	Vector3 start;
	Vector3 end;

	misc Misc;

	bool rotateCamX;
	float MoveCamera1;
	bool camera_check1;
	bool camera_check2;
	bool camera_check3;

	bool rotateCamY;
	float RotateCamera;

	bool wokeUp;
	bool check1;
	bool check2;
	bool check3;
	float eyeOpening;

	bool text1;
	bool text2;

};

#endif