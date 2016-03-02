#ifndef OPENINGCUTSCENE_H
#define OPENINGCUTSCENE_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include "GlobalVariables.h"
#include <vector>
#include <fstream>

using std::vector;
using std::ifstream;
using std::string;

class OpeningCutScene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_TEXTBACKGROUND,

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
	OpeningCutScene();
	~OpeningCutScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Reset();
	virtual void Exit();

	Camera3 camera;

	vector<string> readText;
	vector<string> ReadFromText(string link);
	vector<string> TestYou;
	vector<string>::iterator its = readText.begin();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float x, float y, float z, bool LightYN);

	//render functions 
	void RenderOpeningCutScene(vector<string> Test);

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

	float TextMove;
	bool toMoveText;
	bool appearText;
	float BGMove;
	bool toMoveBG;
	bool appearBG;

	bool startTimer;
	float timercount;

	bool changeScene;
};


#endif