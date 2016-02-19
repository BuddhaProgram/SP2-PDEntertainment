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

	if (SPGame::numScene == 2)
	{
		modelStack.PushMatrix();
			modelStack.Translate(camera.position.x, 0, camera.position.z);
			modelStack.Scale(300, 1, 300);
			RenderMesh(meshList[GEO_FACILITYFLOOR], true);
		modelStack.PopMatrix();
	}
}

// renders the Starting level
void SPGame::RenderSceneStart()
{
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
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float z = -90; z <= 90; z += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(87, 12.5f, z);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Scale(25, 1, 25);
		RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
		modelStack.PopMatrix();
	}
	for (float z = -90; z <= 90; z += 24.94f)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-87, 12.5f, z);
		modelStack.Rotate(180, 0, 1, 0);
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

    //bottom left quadron
    RenderUpWall(-2, -5, -55);//1
    RenderRightWall(-49, -55, -5);//2
    RenderUpWall(-5, -8, -49);//3
    RenderRightWall(-38, -49, -8);//4
    RenderUpWall(-8, -28, -38);//5
    RenderRightWall(-28, -38, -28);//6
    RenderUpWall(-28, -38, -28);//7
    RenderRightWall(-12,-28,-38);//8
    RenderDownWall(-12,-38,-12);//9
    RenderLeftWall(-12, -28, -12);//10
    RenderUpWall(-12, -22, -28);//11
    RenderRightWall(-28,-35, -22);//12

    RenderDownWall(21,-22,-35);//13 (centre long wall)

    //bottom right quadron
    RenderRightWall(-23, -35, 21);//14
    RenderUpWall(21, 12, -23);//15
    RenderRightWall(-7, -23, 12);//16
    RenderDownWall(24, 12, -7);//17
    RenderRightWall(7,-7,24);//18
    RenderLeftWall(7, -7, 27);//19
    RenderDownWall(40, 27, -7);//20
    RenderLeftWall(-7, -23, 40);//21
    RenderUpWall(40, 24, -23);//22

    RenderLeftWall(-23,-38,24);//23
    RenderUpWall(24, 8, -38);//24
    RenderLeftWall(-38, -51, 8);//25
    RenderUpWall(8, 5, -51);//26
    RenderLeftWall(-51, -55, 5);//27
    RenderUpWall(5,2,-55);//28


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