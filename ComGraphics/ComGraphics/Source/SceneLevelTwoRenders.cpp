#include "SceneLevelTwo.h"
#include "OBJAnimation.h"
#include "Application.h"

// Rendering of Floor for all Scenes.
void SceneLevelTwo::RenderFloorCeiling()
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

//void SceneLevelTwo::
// renders the Starting level

void SceneLevelTwo::RenderScene()
{
    RenderFloorCeiling();
	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);
	modelStack.Scale(1, 2.5f, 1);
		RenderUpWall(5, -5, -55, 1);
		RenderRightWall(-45, -55, -5, 2);
		RenderLeftWall(-45, -55, 5, 3);
		RenderUpWall(-5, -10, -45, 4);
		RenderUpWall(10, 5, -45, 5);

		RenderRightWall(-15, -45, -10, 6);
		RenderLeftWall(-15, -45, 10, 7);
		RenderDownWall(-2, -10, -15, 8);
		RenderDownWall(10, 2, -15, 9);
		RenderRightWall(-10, -15, -2, 10);
		RenderLeftWall(-10, -15, 2, 11);

		RenderUpWall(-2, -10, -10, 12);
		RenderUpWall(10, 2, -10, 13);
		RenderRightWall(-2, -10, -10, 14);
		RenderLeftWall(-2, -10, 10, 15);
		RenderRightWall(10, 2, -10, 16);
		RenderLeftWall(10, 2, 10, 17);
		RenderDownWall(-2, -10, 10, 18);
		RenderDownWall(10, 2, 10, 19);

		RenderDownWall(-10, -15, 2, 20);
		RenderUpWall(-10, -15, -2, 21);
		RenderLeftWall(5, 2, -15, 22);
		RenderLeftWall(-2, -5, -15, 23);
		RenderDownWall(-15, -25, 5, 24);
		RenderUpWall(-15, -25, -5, 25);
		RenderRightWall(5, -5, -25, 26);

		RenderDownWall(15, 10, 2, 27);
		RenderUpWall(15, 10, -2, 28);
		RenderRightWall(5, 2, 15, 29);
		RenderRightWall(-2, -5, 15, 30);
		RenderDownWall(25, 15, 5, 31);
		RenderUpWall(25, 15, -5, 32);
		RenderLeftWall(5, -5, 25, 33);

		RenderRightWall(15, 10, -2, 34);
		RenderLeftWall(15, 10, 2, 35);
		RenderUpWall(-2, -10, 15, 36);
		RenderUpWall(10, 2, 15, 37);
		RenderRightWall(35, 15, -10, 38);
		RenderLeftWall(35, 15, 10, 39);
		RenderDownWall(-2, -10, 35, 40);
		RenderDownWall(10, 2, 35, 41);

		RenderRightWall(40, 35, -2, 42);
		RenderLeftWall(40, 35, 2, 43);
		RenderUpWall(-2, -5, 40, 44);
		RenderUpWall(5, 2, 40, 45);
		RenderRightWall(50, 40, -5, 46);
		RenderDownWall(5, -5, 50, 47);
		RenderLeftWall(50, 47, 5, 48);
		RenderLeftWall(43, 40, 5, 49);

		RenderDownWall(30, 5, 47, 50);
		RenderUpWall(30, 5, 43, 51);
		RenderRightWall(50, 47, 30, 52);
		RenderRightWall(43, 5, 30, 53);
		RenderDownWall(50, 30, 50, 54);
		RenderLeftWall(50, 5, 50, 55);
		RenderUpWall(40, 30, 5, 56);
		RenderUpWall(50, 45, 5, 57);
		RenderRightWall(5, 0, 40, 58);
		RenderLeftWall(5, 0, 45, 59);
		RenderUpWall(45, 40, 0, 60);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.DoorSlideTop_5, 123);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.DoorSlideBtm_5, 123);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

}

void SceneLevelTwo::RenderTraps()
{
	modelStack.PushMatrix();
	modelStack.Translate(-75+transSpikeDoor, 0, 244);
	modelStack.Scale(7, 7, 7.25f);

		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 3);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 6);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 9);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 12);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 15);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -3);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -6);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -9);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -12);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -15);
		RenderMesh(meshList[GEO_TRAPWALL], true);
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneLevelTwo::RenderGhost1()
{
    modelStack.PushMatrix();
    modelStack.Translate(Ghost.MobPosX, Ghost.MobPosY, Ghost.MobPosZ);
    RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();
}

void SceneLevelTwo::RenderPlayerDiesInteraction()
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