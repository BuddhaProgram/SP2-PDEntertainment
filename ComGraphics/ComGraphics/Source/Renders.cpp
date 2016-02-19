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
    RenderUpWall(0, -5, -55);
    RenderRightWall(-49, -55, -5);
    RenderUpWall(-5, -9, -49);
    RenderRightWall(-39, -49, -9);
    RenderUpWall(-9,-27, -39);
    


    //------------------------------------------------------------------------
	//top quads

	RenderRightWall(63, 47, -43);//1
	RenderDownWall(-10, -43, 62);//2
	RenderLeftWall(63, 47, -10);//3
	RenderUpWall(-10, -35, 47);//4
	RenderUpWall(-38, -43, 47);//5

	RenderRightWall(47, 38, -38); //6
	RenderLeftWall(47, 41, -35); //7
	RenderDownWall(0, -35, 41);//8
	RenderUpWall(-20, -38, 38); //9
	RenderRightWall(38, 28, -20);//10
	RenderLeftWall(38, 28, -17); //11
	RenderUpWall(3, -17, 38); //12

	RenderLeftWall(51, 38, 3); //13
	RenderRightWall(51, 41, 0); //14
	RenderUpWall(0, -4, 51);//15
	RenderUpWall(10, 3, 51); //16
	RenderLeftWall(62, 51, 10); //17
	RenderRightWall(62, 51, -4);//18
	RenderDownWall(10, -4, 62); //19

	RenderDownWall(-20, -28, 28);//20
	RenderDownWall(-5, -17, 28);//21
	RenderRightWall(28, 10, -28);//22
	RenderUpWall(-5, -28, 10);//23
	RenderLeftWall(15, 10, -5);//24
	RenderLeftWall(28, 18, -5);//25

	RenderDownWall(10, -5, 18);//26
	RenderUpWall(10, -5, 15);//27
	RenderRightWall(25, 18, 10);//28
	RenderRightWall(15, 7, 10);//29
	RenderUpWall(24, 10, 7);//30
	RenderDownWall(27, 10, 25);//31

	RenderDownWall(40, 30, 25);//32
	RenderLeftWall(25, 7, 40);//33
	RenderUpWall(40, 27, 7);//34
	RenderRightWall(31, 25, 27);//35
	RenderLeftWall(31, 25, 30);//36

	RenderUpWall(27, 20, 31);//37
	RenderUpWall(35, 30, 31);//38
	RenderRightWall(35, 31, 20);//39
	RenderLeftWall(35, 31, 35);//40
	RenderDownWall(35, 20, 35);//41


  //TOP QUAD END
	//-----------------------------------------------------


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