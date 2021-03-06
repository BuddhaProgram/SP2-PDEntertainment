/****************************************************************************/
/*!
\file SceneEnd.h
\author Ng Jun Guo
\par email: ng_junguo901@hotmail.com
\brief
header file for SceneEnd
*/
/****************************************************************************/
#ifndef SCENEEND_H
#define SCENEEND_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "MobGhost.h"
#include "MobBossOne.h"
#include "OBJAnimation.h"
#include <iomanip>

/****************************************************************************/
/*!
Class SceneEnd:
\brief
Defines stuff needed for SceneEnd
*/
/****************************************************************************/
class SceneEnd : public Scene
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

		GEO_ROCK,

		// Tools Interface and It's Icons
		GEO_TOOLUIONE,
		GEO_TOOLUITWO,
		GEO_TOOLUITHREE,
		GEO_TOOLUIFOUR,

		GEO_LHAND,
		GEO_RHAND,

		GEO_HANDICON,

		GEO_PICKAXE,
		GEO_PICKAXEICON,

		GEO_BAT,
		GEO_BATICON,

		GEO_SWORD,
		GEO_SWORDICON,

		GEO_GHOST1,
        GEO_BOSS,
        GEO_CRYSTAL1,
        GEO_CRYSTAL2,
		// Animations when player dies
		GEO_DEADCOLOR,
		GEO_DEADBLACKSCREEN,

		GEO_SPACESHIP,
		GEO_REPAIRPOD,
		GEO_REPAIRDONE,

		GEO_HEALTHICON,

		//player related
		GEO_HEALTHBAR,
		GEO_STAMINABAR,

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
	SceneEnd();
	~SceneEnd();

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
	void RenderSceneEnd();

	//map rendering
	void RenderDownWall(int xPos, int zPos);//positive Z facing wall
	

	//mob renders
	void RenderGhost1();

	//render functions 
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float Tx, float Ty, float Tz, bool LightYN);
	//checks
	void checkPlayerPos(double dt, int checkRate, int lessenSpeed);
	void checkPlayerPosMisc();
	void Collision(float smallx, float largex, float smallz, float largez);
	bool proximitycheck(float smallx, float largex, float smallz, float largez);

	// Switches Functions for puzzles
	void PuzzleOneSwitchCheck(double dt);

	// Spaceship and Pod function
	bool b_RepairDone[3];
	bool b_startRepair[3];
	bool b_ReadyToFly();
	float f_RepairProcess[2];
	void RenderShipAndPod();

	void RenderRepairText();
	void RenderMineText();
	void UpdateRepairs(double dt);

	float f_rockY;

	// Combat
    

	// Tool UI functions
	void MouseScrollToolSlot();
	void RenderMouseScrollToolSlot();
	void ToolSelectionMouseScroll();
	void RenderToolIcon();

	void MouseClickFunction(double dt);

	// Checkers and interaction when player dies
	void RenderPlayerDiesInteraction();
	void UpdatePlayerDiesInteraction(double dt);

	void ContinueGameOrNot();

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Animation anima;

	MS modelStack, viewStack, projectionStack;

	Light light[1];
	void FlickeringLight(double dt);

	//float PlanetRotate;
	//float AsteroidRotate;
	//float AsteroidRotateF;
	//float AsteroidMove;
	//float AsteroidMoveS;

	float worldspin;


	Vector3 start;
	Vector3 end;

	float FPS;

    //mobs 
    MobGhost MobOne;
    MobGhost MobTwo;
    MobGhost MobThree;
    MobBossOne BossOne;

    bool spawnWaveOne =false;
    int killCounter;
    int waveCounter;

    void moveMob(double dt);
    void RenderMobs(float xpos, float zpos);
    void RenderBoss(float xpos, float zpos);
    void ResetMobs();
    void MobCheck();
    void checkAttack();

    int MobMS;
    int BossMS;

    bool CrosshairHit;
   
};


#endif