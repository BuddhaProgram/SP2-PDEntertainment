#include "SPGame.h"
#include "OBJAnimation.h"

Animation anima;

//renders the default sky box
void SPGame::RenderSkyBox()
{
    //skybox..................................................................................
    modelStack.PushMatrix();//skybox start
		modelStack.Scale(500, 500, 500);
		modelStack.Rotate(worldspin, 0, 1, 0);

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
void SPGame::RenderFloor()
{
	if (SPGame::numScene == 1 || SPGame::numScene == 3)
	{		
		for (int x = -950; x < 1000; x += 100)
		{
			for (int z = -950; z < 1000; z += 100)
			{
				modelStack.PushMatrix();
				modelStack.Translate(x, 0, z);
				modelStack.Scale(100, 1, 100);
				RenderMesh(meshList[GEO_FLOOR], true);
				modelStack.PopMatrix();
			}
		}	
	}

	if (SPGame::numScene == 2)
	{
		modelStack.PushMatrix();
			modelStack.Translate(camera.position.x, 0, camera.position.z);
			modelStack.Scale(10, 1, 10);
			RenderMesh(meshList[GEO_FLOOR], true);
		modelStack.PopMatrix();
	}
}

// renders the Starting level
void SPGame::RenderSceneStart()
{
    //structure renders
    modelStack.PushMatrix();
		modelStack.Translate(0, 0, -90);
		modelStack.Scale(6, 6, 4);
		RenderMesh(meshList[GEO_FACILITYOUT], true);
	modelStack.PopMatrix();
	RenderSkyBox();

    //object renders


    //Enemy renders
    if (Ghost.Spawn)
    {
        RenderGhost1();
    }
}

//render the exit level
void SPGame::RenderSceneEnd()
{
    //structure renders
    modelStack.PushMatrix();
		modelStack.Translate(0, 0, 90);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(6, 6, 4);
		RenderMesh(meshList[GEO_FACILITYOUT], true);
    modelStack.PopMatrix();
	RenderSkyBox();

    //object renders


    //Enemy renders
    if (Ghost.Spawn)
    {
        RenderGhost1();
    }
}

void SPGame::RenderLevel1()
{
    if (Ghost.Spawn)
    {
        RenderGhost1();
    }
}

void SPGame::RenderGhost1()
{
    modelStack.PushMatrix();
		modelStack.Translate(Ghost.MobPosX, Ghost.MobPosY, Ghost.MobPosZ);
		RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();
}

void SPGame::RenderCutScene()
{
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 0);
	modelStack.Rotate(anima.OpenDoorL, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_MAINDOORLEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-10, 0, 0);
	modelStack.Rotate(anima.OpenDoorR, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_MAINDOORRIGHT], false);
	modelStack.PopMatrix();
}