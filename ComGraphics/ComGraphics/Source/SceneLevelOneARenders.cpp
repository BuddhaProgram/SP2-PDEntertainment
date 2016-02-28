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
    modelStack.Translate(280, 5, 120);
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
		modelStack.Translate(120, 5, 75);
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
    RenderLeftWall(-28, -35, -22, 12);//12

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

	modelStack.PushMatrix();
	modelStack.Translate(0, 8, 285);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 2, 7);
	RenderMesh(meshList[GEO_TV], true);
	modelStack.PopMatrix();

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
		if (activateDoor1)
		{
			displayInteract1 = false;
		}
	}
	else
	{
		displayInteract1 = false;
	}
	if (Application::IsKeyPressed('E'))
	{
		if (proximitycheck(170, 190, 199, 200))
		{
			if (Key_1)
			{
				activateDoor1 = true;
				displayInteract1 = false;
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
	//	Collision(140, 210, 180, 200);
	}

	if (proximitycheck(-205, -195, 115, 125) && !activateDoor1)
	{
		Key1Active = true;
		if (Application::IsKeyPressed('E'))
		{
			Key_1 = true;
		}
		if (Key1Active)
		{
			displayInteract1 = false;
		}
	}
	else
	{
		Key1Active = false;
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
			Collision(-218, -166, 225, 235);
		}
		if (Ghost.health <= 0)
		{
			activateDoor2_1 = true;
			activateDoor2_2 = false;
			if (activateDoor2_1)
			{
				anima.toSlideDoorTop2 = true;
				anima.toSlideDoorBtm2 = true;
				displayInteract2 = false;
			}
		}
	}

	if (anima.toSlideDoorBtm2)
	{
		Collision(-218, -166, 225, 235);
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
		Collision(182, 227, 60, 64);
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

	modelStack.PushMatrix();
	modelStack.Translate(204, 0, -40);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(204, 0, -40);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

}

void SceneLevelOneA::RenderGhost(float xpos, float zpos)
{
	float rotGhost;
	if (camera.target.z > camera.position.z)
	{
		rotGhost = Math::RadianToDegree(atan(camera.view.x / camera.view.z)) - 180;
	}
	else
	{
		rotGhost = Math::RadianToDegree(atan(camera.view.x / camera.view.z));
	}
    modelStack.PushMatrix();
    modelStack.Translate(xpos, 6, zpos);
	modelStack.Rotate(rotGhost + 270, 0, 1, 0);
	modelStack.Scale(6, 3, 6);
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
void SceneLevelOneA::AttackCheck()
{
    //Ghost combat checker

    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(20.f, Ghost.MobPosX, Ghost.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        Ghost.TakeDamage(Explorer::instance()->itemAttack[Variables.i_SlotIndex - 1]);//temporary variable is 1
    }
}

void SceneLevelOneA::AnimationCheck(double dt)
{
	if (activateDoor1) { anima.OpenSlideDoor1(dt); }
	if (activateDoor2_1)
	{
		anima.OpenSlideDoor2(dt);
	}
	else if (activateDoor2_2)
	{
		anima.CloseSlideDoor2(dt);
	}
	if (!Ghost.Spawn && activateDoor2_1)
	{
		anima.OpenSlideDoor2(dt);
	}
	if (activateDoor3) { anima.OpenSlideDoor3(dt); }

	if (!(proximitycheck(192, 217, 60, 64)))
	{
		anima.CloseSlideDoor3(dt);
	}
	if (willDrop)
	{
		anima.Portraits(dt);

	}
}

void SceneLevelOneA::RenderPlayerDiesInteraction()
{
	if (Explorer::instance()->isDead == true)
	{
		if (Variables.f_redScreenTimer <= 2.0f)
		{
			RenderModelOnScreen(meshList[GEO_DEADCOLOR], 100.0f, 100.0f, 100.0f, 90, 1, 0, 0, 0.3f, 0.5f, 0, false);
		}

		else if (Variables.f_redScreenTimer > 2.0f && Variables.f_redScreenTimer <= 4.0f)
		{
			RenderModelOnScreen(meshList[GEO_DEADBLACKSCREEN], 100.0f, 100.0f, 100.0f, 90, 1, 0, 0, 0.3f, 0.5f, 0, false);
			RenderTextOnScreen(meshList[GEO_TEXT], "You are Dead!", Color(1, 0.2f, 1), 5.0f, 4.5f, 9.0f);
		}

		else if (Variables.f_redScreenTimer > 4.0f)
		{
			if (Explorer::instance()->PlayerLife > 0)
			{
				RenderModelOnScreen(meshList[GEO_DEADBLACKSCREEN], 100.0f, 100.0f, 100.0f, 90, 1, 0, 0, 0.3f, 0.5f, 0, false);
				RenderTextOnScreen(meshList[GEO_TEXT], "You are Dead!", Color(1, 0.2f, 1), 5.0f, 4.5f, 9.0f);
				RenderTextOnScreen(meshList[GEO_TEXT], "Continue? (Y/ N)", Color(1, 1, 1), 5.0f, 4.0f, 8.0f);
			}

			else if (Explorer::instance()->PlayerLife <= 0)
			{
				RenderModelOnScreen(meshList[GEO_DEADBLACKSCREEN], 100.0f, 100.0f, 100.0f, 90, 1, 0, 0, 0.3f, 0.5f, 0, false);
				RenderTextOnScreen(meshList[GEO_TEXT], "You are Dead!", Color(1, 0.2f, 1), 5.0f, 4.5f, 9.0f);
				RenderTextOnScreen(meshList[GEO_TEXT], "Game Over!", Color(1, 1, 1), 5.0f, 5.0f, 8.0f);
			}
		}
	}
}