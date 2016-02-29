#ifndef SCENELEVELONEA_H
#define SCENELEVELONEA_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include "MobGhost.h"



class SceneLevelOneA : public Scene
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

        GEO_RUBBLE,
        GEO_PORTRAIT,
		GEO_BLOOD,

        GEO_PLANETFLOOR,
        GEO_FACILITYFLOOR,

        GEO_FACILITYOUT,
        GEO_FACILITYOUTWALL,
        GEO_FACILITYWALLS,
        GEO_FACILITYCEILINGS,
		GEO_TV,

        GEO_SPAWNPOINT,

        // Tools Interface and It's Icons
		GEO_TOOLUIONE,
		GEO_TOOLUITWO,
		GEO_TOOLUITHREE,
		GEO_TOOLUIFOUR,

		GEO_LHAND,
		GEO_RHAND,

		GEO_PICKAXE,
		GEO_PICKAXEICON,

		GEO_BAT,
		GEO_BATICON,

		GEO_SWORD,
		GEO_SWORDICON,

        GEO_GHOST1,
		GEO_BOSS1,

        GEO_DOORSWITCH,
		GEO_SLIDEDOORTOP,
		GEO_SLIDEDOORBTM,
        //player related
        GEO_HEALTHBAR,
		GEO_STAMINABAR,

		// Animations when player dies
		GEO_DEADCOLOR,
		GEO_DEADBLACKSCREEN,

        GEO_SUITCASE,
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
    SceneLevelOneA();
    ~SceneLevelOneA();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void ResetSameScene();
    virtual void ResetAll();
    virtual void Exit();

    Camera3 camera;
private:
    void RenderMesh(Mesh *mesh, bool enableLight);

    //scene renders
    void RenderScene();
    void RenderFloorCeiling();
    void RenderCutSceneOne();
    void RenderSuitCase();
    void RenderInteract();

    //map rendering
    void RenderDownWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber);//positive Z facing wall
    void RenderUpWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber);//negative Z facing Wall
    void RenderRightWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber);// positive X facing wall
    void RenderLeftWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber);//negative X facing wall

    //mob renders
    void RenderGhost(float xpos, float zpos);

	//Obj renders
	void CollapseRubble();
	void DropPortrait();

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

	// Tool UI functions
	void ToolsUI();
	void MouseScrollToolSlot();
	void RenderMouseScrollToolSlot();
	void ToolSelectionMouseScroll();
	void RenderToolIcon();

	void MouseClickFunction(double dt);

	void RenderPickUpPickAxe();

	// Updates save point position
	void UpdateSavePoint();
	void RenderSavePointText();

    //checkers and animation functions
	void checkRubbleFall();
	void checkDoor1(double dt);
	void checkDoor2();
	void checkDoor3();
	void checkDrop();
    void AttackCheck();
	void TestDoorRender(); // Sliding Door
    void EnvironmentAnimation(double dt);
	void AnimationCheck(double dt);

	// Checkers and interaction when player dies
	void RenderPlayerDiesInteraction();
	void UpdatePlayerDiesInteraction(double dt);

	void ContinueGameOrNot();

	// Checkers and interaction with suitcases
	void PickUpSuitcaseInteraction();
	void RenderPickUpSuitcaseText();

    //objects and mob animation variables
    bool displayInteract1;
    bool displayInteract2;
    bool displayInteract3;
    bool activateDoor1 = false;
    bool activateDoor2_1 = false;
    bool activateDoor2_2 = false;
    bool activateDoor3 = false; //if true open door
    bool Key_1 = false;
    bool Notice = false;
    bool Notice2 = false;
    bool willDrop = false;
    bool Key1Active = false;
    float SwitchRot = 45.f;

    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    Animation anima;

    MS modelStack, viewStack, projectionStack;

    Light light[1];

    Vector3 start;
    Vector3 end;
    GlobalVariables Variables;
    MobGhost Ghost;

    float FPS;
	

    //collision variables 
    float CollXLarge[28];
    float CollXSmall[28];
    float CollZLarge[28];
    float CollZSmall[28];
};


#endif