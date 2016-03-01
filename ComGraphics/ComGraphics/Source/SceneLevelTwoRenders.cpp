#include "SceneLevelTwo.h"
#include "OBJAnimation.h"
#include "Application.h"

#include "Misc.h"
misc functionMisc;

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
    functionMisc.camX = camera.position.x;
    functionMisc.camY = camera.position.y;
    functionMisc.camZ = camera.position.z;

    RenderSwitches();
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
	modelStack.Translate(0, anima.DoorSlideTop_5, 120);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.DoorSlideBtm_5, 120);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();


	//MIDDLE DOORS
	modelStack.PushMatrix();
	modelStack.Translate(-85, anima.QPDOOR1_TOP, 4);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6.4f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-85, anima.QPDOOR1_BOT, 4);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6.4f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();
	//MIDDLE DOORS

	//MIDDLE DOORS
	modelStack.PushMatrix();
	modelStack.Translate(85, anima.QPDOOR2_TOP, 4);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6.4f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(85, anima.QPDOOR2_BOT, 4);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6.4f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();
	//MIDDLE DOORS

	//MIDDLE DOORS
	modelStack.PushMatrix();
	modelStack.Translate(0, anima.QPDOOR3_TOP, -100);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.QPDOOR3_BOT, -100);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();
	//MIDDLE DOORS

	//MIDDLE DOORS
	modelStack.PushMatrix();
	modelStack.Translate(0, anima.QPDOOR4_TOP, -300);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, anima.QPDOOR4_BOT, -300);
	modelStack.Scale(6.5f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();
	//MIDDLE DOORS

	//ENDING DOORS
	modelStack.PushMatrix();
	modelStack.Translate(340, anima.QPDOOR5_TOP, -25);
	modelStack.Scale(8, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(340, anima.QPDOOR5_BOT, -25);
	modelStack.Scale(8, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();
	//ENDING DOORS
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

	modelStack.PushMatrix();
	modelStack.Translate(320, 0, -390 + transSpikeWall2);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(7, 7, 7.25f);

		modelStack.PushMatrix();
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

	modelStack.PopMatrix();
}

void SceneLevelTwo::RenderSwitches()
{
    modelStack.PushMatrix();
    modelStack.Translate(-200, 7, 4.6f);
    modelStack.Rotate(-Switch1Rot, 0, 0, 1);
    RenderMesh(meshList[GEO_LEVER], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(200, 7, 4.6f);
    modelStack.Rotate(Switch2Rot, 0, 0, 1);
    RenderMesh(meshList[GEO_LEVER], true);
    modelStack.PopMatrix();

   
}

void SceneLevelTwo::SwitchCheck(double dt)
{
    if (functionMisc.WithinArea(-206, -192, 0.6f, 8.6f))
    {
        Switch1Int = true;
        if (Application::IsKeyPressed(VK_RBUTTON))
        {
            Switch1Press = true;
        }
    }
    else
    {
        Switch1Int = false;
    }

    if (functionMisc.WithinArea(192, 206, 0.6f, 8.6f))
    {
        Switch2Int = true;
        if (Application::IsKeyPressed(VK_RBUTTON))
        {
            Switch2Press = true;
        }
        
    }
    else
    {
        Switch2Int = false;
    }

    if (Switch1Press)
    {
        if (Switch1Rot < 135)
        {
            Switch1Rot += (float)(dt)* 90;
        }
    }
    if (Switch2Press)
    {
        if (Switch2Rot < 135)
        {
            Switch2Rot += (float)(dt)* 90;
        }
    }

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

void SceneLevelTwo::RenderPuzzle()
{
	for (int i = 0, placing = 0; i < 60; i += 12, ++placing)
	{
		if (!Switches.b_PuzzleTwo[placing])
		{
			modelStack.PushMatrix();
				modelStack.Translate((float)(312 - i), 17, -36);
				modelStack.Scale(2, 2, 2);
				modelStack.Rotate(90, 0, 1, 0);
				RenderMesh(meshList[GEO_LIGHTRED], true);
			modelStack.PopMatrix();
		}

		else if (Switches.b_PuzzleTwo[placing])
		{
			modelStack.PushMatrix();
				modelStack.Translate((float)(312 - i), 17, -36);
				modelStack.Scale(2, 2, 2);
				modelStack.Rotate(90, 0, 1, 0);
				RenderMesh(meshList[GEO_LIGHTGREEN], true);
			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix();
		modelStack.Translate(306, 5, -37);
		modelStack.Scale(2, 2, 2);
		modelStack.Rotate(-45, 1, 0, 0);
		modelStack.Rotate(Variables.f_SwitchRotateOne, 1, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_LEVER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(294, 5, -37);
		modelStack.Scale(2, 2, 2);
		modelStack.Rotate(-45, 1, 0, 0);
		modelStack.Rotate(Variables.f_SwitchRotateTwo, 1, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_LEVER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(282, 5, -37);
		modelStack.Scale(2, 2, 2);
		modelStack.Rotate(-45, 1, 0, 0);
		modelStack.Rotate(Variables.f_SwitchRotateThree, 1, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_LEVER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(270, 5, -37);
		modelStack.Scale(2, 2, 2);
		modelStack.Rotate(-45, 1, 0, 0);
		modelStack.Rotate(Variables.f_SwitchRotateFour, 1, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_LEVER], true);
	modelStack.PopMatrix();
}