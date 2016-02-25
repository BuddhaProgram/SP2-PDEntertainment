#include "SceneLevelOneA.h"
#include "OBJAnimation.h"
#include "Application.h"


// Rendering of Floor for all Scenes.
void SceneLevelOneA::RenderFloorCeiling()
{
    modelStack.PushMatrix();
		modelStack.Scale(1000, 1, 1000);
		RenderMesh(meshList[GEO_FACILITYFLOOR], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
		modelStack.Translate(0, 20, 0);
		modelStack.Rotate(180, 1, 0, 0);
		modelStack.Scale(1000, 1, 1000);
		RenderMesh(meshList[GEO_FACILITYCEILINGS], true);
    modelStack.PopMatrix();
}

void SceneLevelOneA::RenderSuitCase()
{
    modelStack.PushMatrix();
    modelStack.Translate(280, EnvTranslateY, 120);
    modelStack.Rotate(EnvRotateY, 0, 1, 0);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_SUITCASE], true);
    modelStack.PopMatrix();
}

//void SceneLevelOneA::
// renders the Starting level

void SceneLevelOneA::RenderInteract()
{
    RenderTextOnScreen(meshList[GEO_TEXT], "Press E to interact", Color(1, 0, 0), 3, 8.75f, 8);
}

void SceneLevelOneA::RenderScene()
{
    // temp key switch place holder for first locked door
    modelStack.PushMatrix();
    modelStack.Translate(-200, 3, 120);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_SPAWNPOINT], true);
    modelStack.PopMatrix();

    //firstsave
    modelStack.PushMatrix();
		modelStack.Translate(120, EnvTranslateY, 75);
        modelStack.Rotate(EnvRotateY, 0, 1, 0);
		modelStack.Scale(4, 4, 4);
		RenderMesh(meshList[GEO_SPAWNPOINT], true);
	modelStack.PopMatrix();

    RenderFloorCeiling();
    RenderSuitCase();

    //bottom left quadron
    modelStack.PushMatrix();
    modelStack.Translate(0, -10, 0);
    modelStack.Scale(1, 2.5, 1);
    RenderUpWall(-2, -5, -55, 1);//1 
    RenderRightWall(-49, -55, -5, 2);//2
    RenderUpWall(-5, -8, -49, 3);//3
    RenderRightWall(-38, -49, -8, 4);//4
    RenderUpWall(-8, -28, -38, 5);//5
    RenderRightWall(-28, -38, -25, 6);//6
    RenderUpWall(-25, -38, -28, 7);//7
    RenderRightWall(-12, -28, -38, 8);//8
    RenderDownWall(-12, -38, -12, 9);//9
    RenderLeftWall(-12, -28, -12, 10);//10
    RenderUpWall(-12, -22, -28, 11);//11
    RenderRightWall(-28, -35, -22, 12);//12

    RenderDownWall(21, -22, -35, 13);//13 (centre long wall)

    //bottom right quadron
    RenderRightWall(-23, -35, 21, 14);//14
    RenderUpWall(21, 12, -23, 15);//15
    RenderRightWall(-7, -23, 12, 16);//16
    RenderDownWall(24, 12, -7, 17);//17
    RenderRightWall(7, -7, 24, 18);//18
    RenderLeftWall(7, -7, 27, 19);//19
    RenderDownWall(40, 27, -7, 20);//20
    RenderLeftWall(-7, -23, 40, 21);//21
    RenderUpWall(40, 24, -23,22);//22

    RenderLeftWall(-23, -38, 24, 23);//23
    RenderUpWall(24, 8, -38, 24);//24
    RenderLeftWall(-38, -51, 8, 25);//25
    RenderUpWall(8, 5, -51, 26);//26
    RenderLeftWall(-51, -55, 5, 27);//27
    RenderUpWall(5, 2, -55, 28);//28

	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 455);
	modelStack.Scale(6, 3.1f, 4);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_FACILITYOUT], true);
	modelStack.PopMatrix();
	Collision(-25, 25, 430, 500);
}

void SceneLevelOneA::checkRubbleFall()
{
	if (/*!(anima.WithinArea(-20, 20, 400, 450))*/  !(camera.position.x >= -20 && camera.position.x <= 20 && camera.position.z >= 400 && camera.position.z <= 450))
	{
		anima.Collapse = true;
		if (anima.RubbleCollapse <= 0)
		{
			anima.Collapse = false;
		}
	}

	if (!anima.Collapse)
	{
		Collision(-25, 25, 420, 500);
	}
}

void SceneLevelOneA::checkDoor1()
{
	if (proximitycheck(170, 190, 199, 200))
	{
		displayInteract1 = true;
	}
	else
	{
		displayInteract1 = false;
	}
	if (Application::IsKeyPressed('E'))
	{
		if (proximitycheck(170, 190, 199, 200))
		{
			displayInteract1 = false;
			if (Key_1)
			{
				activateDoor1 = true;
			}
			else
			{
				Notice = true;
			}
		}
	}
	if (!proximitycheck(170, 190, 199, 200))
	{
		Notice = false;
	}
	if (anima.toSlideDoorBtm)
	{
		//Collision(150, 200, 180, 200);
	}
}

void SceneLevelOneA::checkDoor2()
{
	if (proximitycheck(-208, -176, 232, 235))
	{
		displayInteract2 = true;
		if (activateDoor2_1)
		{
			displayInteract2 = false;
		}
	}
	else
	{
		displayInteract2 = false;
	}
	if (Application::IsKeyPressed('E') && proximitycheck(-204, -180, 235, 240))
	{
		activateDoor2_1 = true;
	}

	if (Ghost.Spawn)
	{
		activateDoor2_1 = false;
		activateDoor2_2 = true;
		if (activateDoor2_2)
		{
			Collision(-208, -176, 225, 235);
		}
	}

	if (anima.toSlideDoorBtm2)
	{
		Collision(-208, -176, 225, 235);
	}

	/*if (!proximitycheck(-208, -176, 245, 255))
	{
	activateDoor2 = false;
	}
	*/
}

void SceneLevelOneA::checkDoor3()
{
	//if (!activateDoor3_1)
	//{
	//	activateDoor3_2 = true;
	//}

	if (proximitycheck(192, 217, 60, 64))
	{
		displayInteract3 = true;	
		if (activateDoor3)
		{
			displayInteract3 = false;
		}
	}
	else
	{
		displayInteract3 = false;
	}
	if (proximitycheck(192, 217, 60, 64) && (Application::IsKeyPressed('E')))
	{
		activateDoor3 = true;
	}


	//if (/*!proximitycheck(192, 217, 60, 64)*/ camera.position.x <= 192 && camera.position.x >= 217 && camera.position.z >= 64)
	//{
	//	activateDoor3_1 = false;
	//	activateDoor3_2 = true;
	//}

	if (anima.toSlideDoorBtm3)
	{
		Collision(192, 217, 60, 64);
	}

}

void SceneLevelOneA::checkDrop()
{
	if (proximitycheck(64,160, 288, 305))
	{
		willDrop = true;
	}
}

void SceneLevelOneA::TestDoorRender()
{
	modelStack.PushMatrix();
	modelStack.Translate(180, anima.DoorSlideTop, 188);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(180, anima.DoorSlideBtm, 188);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-188, anima.DoorSlideTop_2, 228);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-188, anima.DoorSlideBtm_2, 228);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(204, anima.DoorSlideTop_3, 59);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(204, anima.DoorSlideBtm_3, 59);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

}

void SceneLevelOneA::RenderGhost(float xpos, float zpos)
{
    modelStack.PushMatrix();
    modelStack.Translate(xpos, 6, zpos);
    RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();
}

void SceneLevelOneA::CollapseRubble()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + anima.RubbleCollapse, 440);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[GEO_RUBBLE], true);
	modelStack.PopMatrix();
}

void SceneLevelOneA::DropPortrait()
{

	modelStack.PushMatrix();
	modelStack.Translate(192, anima.f_PortraitDrop , 300);
	modelStack.Scale(12, 4, 12);
	modelStack.Rotate(anima.f_PortraitFall, 0, 0, 1);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PORTRAIT], true);
	modelStack.PopMatrix();

}

void SceneLevelOneA::EnvironmentAnimation(double dt)
{
    EnvRotateY += (float)(20.f * dt);

  
}