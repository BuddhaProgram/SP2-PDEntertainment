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
					modelStack.Translate(x, 0, z);
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


    RenderUpWall(5, -5, 5 );
    RenderDownWall(5,-5, -5);
    RenderRightWall(5, -5, 5);
    RenderLeftWall(5, -5, -5);

	/*----------------------------------[Renders Facility Walls and Ceilings]------------------------------------*/
		//Sets the position of horizontal walls
	/*All the code in this section translate the walls according to the x-axis; z-axis is always fixed*/
	//for (int horizontalX = -36; horizontalX <= 36; horizontalX += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -460);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = -44; horizontalX >= -60; horizontalX -= 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -412);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = 44; horizontalX <= 60; horizontalX += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -412);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = -68; horizontalX >= -224; horizontalX -= 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -324);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//						modelStack.Translate(0, 8, 0);
	//						modelStack.Rotate(90, 1, 0, 0);
	//						modelStack.Scale(8, 8, 8);
	//						RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = 68; horizontalX <= 188; horizontalX += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -324);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = -180; horizontalX <= 164; horizontalX += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -300);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = -228; horizontalX >= -304; horizontalX -= 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -244);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = -116; horizontalX >= -184; horizontalX -= 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -244);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalX = -300; horizontalX <= -116; horizontalX += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(horizontalX, 4, -116);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 1, 0, 0);
	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	///*All the code in this section translate the walls according to the z-axis; x-axis is always fixed*/
	//for (int horizontalZ = -456; horizontalZ <= -412; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(-40, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);
	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -456; horizontalZ <= -412; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(40, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -408; horizontalZ <= -328; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(-64, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -408; horizontalZ <= -328; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(64, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -408; horizontalZ <= -328; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(64, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -320; horizontalZ <= -248; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(-224, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -296; horizontalZ <= -248; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(-184, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -240; horizontalZ <= -120; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(-112, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}

	//for (int horizontalZ = -240; horizontalZ <= -120; horizontalZ += 8)
	//{
	//	modelStack.PushMatrix();
	//		modelStack.Translate(-304, 4, horizontalZ);

	//		modelStack.PushMatrix();
	//			modelStack.Translate(0, 8, 0);

	//			modelStack.PushMatrix();
	//				modelStack.Translate(0, 8, 0);

	//				modelStack.PushMatrix();
	//					modelStack.Translate(0, 8, 0);
	//					modelStack.Rotate(90, 0, 1, 0);
	//					modelStack.Rotate(90, 1, 0, 0);

	//					modelStack.Scale(8, 8, 8);
	//					RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//				modelStack.PopMatrix();

	//				modelStack.Rotate(90, 0, 1, 0);
	//				modelStack.Rotate(90, 1, 0, 0);
	//				modelStack.Scale(8, 8, 8);
	//				RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//			modelStack.PopMatrix();

	//			modelStack.Rotate(90, 0, 1, 0);
	//			modelStack.Rotate(90, 1, 0, 0);
	//			modelStack.Scale(8, 8, 8);
	//			RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//		modelStack.PopMatrix();

	//		modelStack.Rotate(90, 0, 1, 0);
	//		modelStack.Rotate(90, 1, 0, 0);
	//		modelStack.Scale(8, 8, 8);
	//		RenderMesh(meshList[GEO_FACILITYWALLS], true);
	//	modelStack.PopMatrix();
	//}
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