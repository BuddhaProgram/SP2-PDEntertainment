#ifndef SCENELEVELTWO_H
#define SCENELEVELTWO_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include "MobGhost.h"

class SceneLevelTwo : public Scene
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

        GEO_PLANETFLOOR,
        GEO_FACILITYFLOOR,

        GEO_FACILITYOUT,
        GEO_FACILITYOUTWALL,
        GEO_FACILITYWALLS,
        GEO_FACILITYCEILINGS,
		GEO_TRAPWALL,

		GEO_HEALTHBAR,
		GEO_STAMINABAR,

        GEO_LHAND,
        GEO_RHAND,

        // Tools Interface and It's Icons
		GEO_TOOLUIONE,
		GEO_TOOLUITWO,
		GEO_TOOLUITHREE,
		GEO_TOOLUIFOUR,

		GEO_PICKAXE,
		GEO_PICKAXEICON,

		GEO_BAT,
		GEO_BATICON,

		GEO_SWORD,
		GEO_SWORDICON,

        GEO_GHOST1,
        GEO_SPAWNPOINT,

        GEO_SLIDEDOORTOP,
        GEO_SLIDEDOORBTM,

        //player related

		GEO_DEADCOLOR,
		GEO_DEADBLACKSCREEN,


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
    SceneLevelTwo();
    ~SceneLevelTwo();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Reset();
    virtual void Exit();

    Camera3 camera;
private:
    void RenderMesh(Mesh *mesh, bool enableLight);

    //scene renders
    void RenderScene();
    void RenderFloorCeiling();

    //map rendering
    void RenderDownWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber);//positive Z facing wall
    void RenderUpWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber);//negative Z facing Wall
    void RenderRightWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber);// positive X facing wall
    void RenderLeftWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber);//negative X facing wall

    //mob renders
    void RenderGhost1();
	void RenderTraps();

    //render functions 
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float x, float y, float z, bool LightYN);
    //checks
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

    Vector3 start;
    Vector3 end;
    GlobalVariables Variables;
	misc Misc;

    float FPS;
    bool displayInteract1;
    bool activateDoor1;

    float CollXLarge[60];
    float CollXSmall[60];
    float CollZLarge[60];
    float CollZSmall[60];

	float transSpikeDoor;
	bool closeDoors = false;
    MobGhost Ghost;

};


#endif