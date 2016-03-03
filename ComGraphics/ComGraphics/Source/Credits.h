/**************************************************************************/
/*!
\file			Credits.h
\author			Matsuda Kenichi
\par			email: 150450F\@mymail.nyp.edu.sg
\brief
Class to define Credits

/**************************************************************************/

#ifndef CREDITS_H
#define CREDITS_H

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

/**************************************************************************/
/*!
Class Credits:
\brief
Define Credits and its method to make the credits scene
*/
/**************************************************************************/

class Credits : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TITLE,
		GEO_TEXT,
		GEO_TEXTBACKGROUND,

		GEO_NAME1,
		GEO_NAME2,
		GEO_NAME3,
		GEO_NAME4,

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
	Credits();
	~Credits();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Reset();
	virtual void Exit();

	Camera3 camera;

private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh* mesh, float Sx, float Sy, float Sz, float Rotate, float rX, float rY, float rZ, float x, float y, float z, bool LightYN);

	//render functions 
	void RenderCredits();
	void RenderMovingCredits(double dt);

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

	float firstcredits;
	float secondcredits;
	float thirdcredits;
	float fourthcredits;
	float fifthcredits;
	float lastcredits;

	bool move1 = true;
	bool move2;
	bool move3;
	bool move4;
	bool move5;
	bool move6;
	bool first = true;
	bool second;
	bool third;
	bool fourth;
	bool fifth;
	bool last;

	float countdown;
	bool timer;
};


#endif