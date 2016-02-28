#include "SceneStart.h"
#include "OpeningCutScene2.h"
#include "OBJAnimation.h"

Animation anima;

//renders the default sky box
void SceneStart::RenderSkyBox()
{
    //skybox..................................................................................
    modelStack.PushMatrix();//skybox start
		modelStack.Scale(500, 500, 500);
		modelStack.Rotate(Variables.f_Worldspin, 0, 1, 0);

    //front
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, -10);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(20, 0, 20);
			RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();

    //right
		modelStack.PushMatrix();
			modelStack.Translate(10, 0, 0);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(20, 0, 20);
			RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();

		//left
		modelStack.PushMatrix();
			modelStack.Translate(-10, 0, 0);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(20, 0, 20);
			RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();

    //back
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, 10);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(20, 0, 20);
			RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();

    //bottom
		modelStack.PushMatrix();
			modelStack.Translate(0, -10, 0);
			modelStack.Scale(20, 0, 20);
			RenderMesh(meshList[GEO_BOTTOM], false);
		modelStack.PopMatrix();

    //top
		modelStack.PushMatrix();
			modelStack.Translate(0, 10, 0);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(20, 0, 20);
			RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();

    modelStack.PopMatrix();//skybox end
}

// Rendering of Floor for all Scenes.
void SceneStart::RenderFloor()
{
		for (int x = -450; x < 500; x += 100)
		{
			for (int z = -450; z < 500; z += 100)
			{
				modelStack.PushMatrix();
					modelStack.Translate((float)x, 0, (float)z);
					modelStack.Scale(100, 1, 100);
					RenderMesh(meshList[GEO_PLANETFLOOR], true);
				modelStack.PopMatrix();
			}
		}	

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 53);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_DEADBODY], true);
		modelStack.PopMatrix();
	}

	
		
//void SceneStart::
// renders the Starting level
void SceneStart::RenderSceneStart()
{
    //basic renders
    RenderFloor();
    //structure renders
    modelStack.PushMatrix();
		modelStack.Translate(0, 0, -90);
		modelStack.Scale(6, 6.1f, 4);
		RenderMesh(meshList[GEO_FACILITYOUT], true);
	modelStack.PopMatrix();

	for (float x = -75; x <= 75; x += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(x, 12.5f, -100);
		modelStack.Rotate(270, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float z = -90; z <= 90; z += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(87, 12.5f, z);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float z = -90; z <= 90; z += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-87, 12.5f, z);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float x = -75; x <= 75; x += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(x, 12.5f, 97);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	RenderSkyBox();


	//modelStack.PushMatrix();
	//modelStack.Translate(86.9, 5, 0);
	//modelStack.Rotate(90, 0, 0, 1);
	//modelStack.Scale(40, 1, 90);
	//RenderMesh(meshList[GEO_BLOOD1], true);
	//modelStack.PopMatrix();

    //object renders
}

//renders the default sky box
void OpeningCutScene2::RenderSkyBox()
{
	//skybox..................................................................................
	modelStack.PushMatrix();//skybox start
	modelStack.Scale(500, 500, 500);
	modelStack.Rotate(Variables.f_Worldspin, 0, 1, 0);

	//front
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(20, 0, 20);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//right
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(20, 0, 20);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//left
	modelStack.PushMatrix();
	modelStack.Translate(-10, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20, 0, 20);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	//back
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 10);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(20, 0, 20);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//bottom
	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);
	modelStack.Scale(20, 0, 20);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	//top
	modelStack.PushMatrix();
	modelStack.Translate(0, 10, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(20, 0, 20);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();//skybox end
}

// Rendering of Floor for all Scenes.
void OpeningCutScene2::RenderFloor()
{
	for (int x = -450; x < 500; x += 100)
	{
		for (int z = -450; z < 500; z += 100)
		{
			modelStack.PushMatrix();
			modelStack.Translate((float)x, 0, (float)z);
			modelStack.Scale(100, 1, 100);
			RenderMesh(meshList[GEO_PLANETFLOOR], true);
			modelStack.PopMatrix();
		}
	}

}


//void SceneStart::
// renders the Starting level
void OpeningCutScene2::RenderSceneStart()
{
	//basic renders
	RenderFloor();
	//structure renders
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -90);
	modelStack.Scale(6, 6.1f, 4);
	RenderMesh(meshList[GEO_FACILITYOUT], true);
	modelStack.PopMatrix();

	for (float x = -75; x <= 75; x += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(x, 12.5f, -100);
		modelStack.Rotate(270, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float z = -90; z <= 90; z += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(87, 12.5f, z);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float z = -90; z <= 90; z += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-87, 12.5f, z);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float x = -75; x <= 75; x += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(x, 12.5f, 97);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	RenderSkyBox();


	//modelStack.PushMatrix();
	//modelStack.Translate(86.9, 5, 0);
	//modelStack.Rotate(90, 0, 0, 1);
	//modelStack.Scale(40, 1, 90);
	//RenderMesh(meshList[GEO_BLOOD1], true);
	//modelStack.PopMatrix();

	//object renders
}


