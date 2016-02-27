#include "SceneLevelOneB.h"
#include "OBJAnimation.h"
#include "Application.h"


// Rendering of Floor for all Scenes.
void SceneLevelOneB::RenderFloorCeiling()
{
    modelStack.PushMatrix();
    modelStack.Scale(1000, 1, 1000);
    RenderMesh(meshList[GEO_FACILITYFLOOR], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 20, -155);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(1000, 1, 430);
    RenderMesh(meshList[GEO_FACILITYCEILINGS], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 40, -440);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(1000, 1, 240);
    RenderMesh(meshList[GEO_FACILITYCEILINGS], true);
    modelStack.PopMatrix();
}
//void SceneLevelOneB::
// renders the Starting level


void SceneLevelOneB::RenderScene()
{

    RenderPuzzle();
    //secondsave
    modelStack.PushMatrix();
    modelStack.Translate(-200, 5, -200);
    modelStack.Rotate(EnvRotateY, 0, 1, 0);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_SPAWNPOINT], true);
    modelStack.PopMatrix();
    RenderFloorCeiling();

    //suitcase
    modelStack.PushMatrix();
    modelStack.Translate(-200, 5, -120);
    modelStack.Rotate(EnvRotateY, 0, 1, 0);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_SUITCASE], true);
    modelStack.PopMatrix();

    //------------------------------------------------------------------------
    //top quads
    modelStack.PushMatrix();
    modelStack.Translate(0, -3, 0);
    modelStack.Scale(1, 1.2f, 1);

    modelStack.PushMatrix();
    modelStack.Translate(0, -7, 0);
    modelStack.Scale(1, 2.2f, 1);

    modelStack.PushMatrix();
    modelStack.Translate(0, -7, 0);
    modelStack.Scale(1, 2.2f, 1);
    RenderRightWall(63, 47, -43, 1);//1
    RenderDownWall(-10, -43, 62, 2);//2
    RenderLeftWall(63, 47, -10, 3);//3
    RenderUpWall(-10, -35, 47, 4);//4
    RenderUpWall(-38, -43, 47, 5);//5
    modelStack.PopMatrix();

    RenderRightWall(47, 38, -38, 6); //6
    RenderLeftWall(47, 41, -35, 7); //7
    RenderDownWall(0, -35, 41, 8);//8
    RenderUpWall(-20, -38, 38, 9); //9
    RenderRightWall(38, 28, -20, 10);//10
    RenderLeftWall(38, 28, -17, 11); //11
    RenderUpWall(3, -17, 38, 12); //12

    RenderLeftWall(51, 38, 3, 13); //13
    RenderRightWall(51, 41, 0, 14); //14
    RenderUpWall(0, -4, 51, 15);//15
    RenderUpWall(10, 3, 51, 16); //16
    RenderLeftWall(62, 51, 10, 17); //17
    RenderRightWall(62, 51, -4, 18);//18
    RenderDownWall(10, -4, 62, 19); //19

    RenderDownWall(-20, -28, 28, 20);//20
    RenderDownWall(-5, -17, 28, 21);//21
    RenderRightWall(28, 10, -28, 22);//22
    RenderUpWall(-5, -28, 10, 23);//23
    RenderLeftWall(15, 10, -5, 24);//24
    RenderLeftWall(28, 18, -5, 25);//25

    RenderDownWall(10, -5, 18, 26);//26
    RenderUpWall(10, -5, 15, 27);//27
    RenderRightWall(25, 18, 10, 28);//28
    RenderRightWall(15, 7, 10, 29);//29
    RenderUpWall(24, 10, 7, 30);//30
    RenderDownWall(27, 10, 25, 31);//31

    RenderDownWall(40, 30, 25, 32);//32
    RenderLeftWall(25, 7, 40,33);//33
    RenderUpWall(40, 27, 7, 34);//34
    RenderRightWall(31, 25, 27, 35);//35
    RenderLeftWall(31, 25, 30, 36);//36

    RenderUpWall(27, 20, 31, 37);//37
    RenderUpWall(35, 30, 31, 38);//38
    RenderRightWall(35, 31, 20, 39);//39
    RenderLeftWall(35, 31, 35, 40);//40
    RenderDownWall(35, 20, 35, 41);//41

    //connector betw 1A and 1B
    RenderRightWall(7, -7, 24, 42);//42
    RenderLeftWall(7, -7, 27, 43);//43

    modelStack.PushMatrix();
    modelStack.Translate(0, 7, 0);
    RenderUpWall(-35, -38, 47, 44);
    modelStack.PopMatrix();
    modelStack.PopMatrix();
    //Floating wall to cover hole in boss room
    
    modelStack.PopMatrix();
    //TOP QUAD END
    //-----------------------------------------------------
}

void SceneLevelOneB::RenderDoor()
{

	//1st door
	modelStack.PushMatrix();
	modelStack.Translate(204, 0, 59);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(204, 0, 59);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	Collision(190, 216, 54, 60);
	//2nd door
	modelStack.PushMatrix();
	modelStack.Translate(204, anima.DoorSlideTop, -51);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(204, anima.DoorSlideBtm, -51);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	//3rd door open by switch
	modelStack.PushMatrix();
	modelStack.Translate(228, anima.DoorSlideTop_2, -218);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(228, anima.DoorSlideBtm_2, -218);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	//4th door open by switch
	modelStack.PushMatrix();
	modelStack.Translate(56, anima.DoorSlideTop_3, -128);
	modelStack.Scale(4.9f, 4, 5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(56, anima.DoorSlideBtm_3, -128);
	modelStack.Scale(4.9f, 4, 5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	//5th door BOSS door
	modelStack.PushMatrix();
	modelStack.Translate(-292, 0, -363);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-292, 0, -363);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

	//6th door near elevator
	modelStack.PushMatrix();
	modelStack.Translate(12, anima.DoorSlideTop_4, -400);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, anima.DoorSlideBtm_4, -400);
	modelStack.Scale(4.9f, 4, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], true);
	modelStack.PopMatrix();

}

void SceneLevelOneB::checkDoor1()
{
	if (proximitycheck(190, 216, -40, -46))
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
		if (proximitycheck(190, 216, -40, -46))
		{
			activateDoor1 = true;
		}
		
	}
	if (anima.toSlideDoorBtm)
	{
		Collision(190, 216, -55, -45);
	}
}

void SceneLevelOneB::checkDoor2()
{

	if (Switches.b_PuzzleOne[0] && Switches.b_PuzzleOne[1] && Switches.b_PuzzleOne[2])
	{
		activateDoor2 = true;
	}

	if (anima.toSlideDoorBtm2)
	{
		Collision(52, 65, -150, -100);
		Collision(205, 245, -220, -210);
	}
}

void SceneLevelOneB::checkDoor3()
{
	if (proximitycheck(-350, -250 ,-375, -355))
	{
		displayInteract2 = true;
		if (activateDoor3_1)
		{
			displayInteract2 = false;
		}
	}
	else
	{
		displayInteract2 = false;
	}
	if (Application::IsKeyPressed('E') && proximitycheck(-350, -250, -375, -355))
	{
		activateDoor3_1 = true;
	}

	if (BossOne.Spawn)
	{
		activateDoor3_1 = false;
		activateDoor3_2 = true;
		displayInteract2 = false;
		if (activateDoor3_2)
		{
			Collision(-350, -250, -375, -355);
		}
		if (BossOne.health <= 0)
		{
			activateDoor3_1 = true;
			activateDoor3_2 = false;
			if (activateDoor3_1)
			{
				anima.toSlideDoorTop_Boss = true;
				anima.toSlideDoorBtm_Boss = true;
				displayInteract2 = false;
			}
		}
	}

	if (anima.toSlideDoorBtm_Boss)
	{
		Collision(-350, -250, -375, -355);
	}
}

void SceneLevelOneB::checkDoor4()
{
	if (proximitycheck(0, 25, -410, -390))
	{
		displayInteract3 = true;
		if (activateDoor4)
		{
			displayInteract3 = false;
		}
	}
	else
	{
		displayInteract3 = false;
	}
	if (Application::IsKeyPressed('E'))
	{
		if (proximitycheck(0, 25, -410, -390))
		{
			activateDoor4 = true;
		}

	}

	if (anima.toSlideDoorBtm4)
	{
		Collision(0, 25, -410, -390);
	}

}

void SceneLevelOneB::RenderGhost(float xpos, float zpos)
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
    modelStack.Scale(3, 3, 3);
	modelStack.Rotate(rotGhost+270, 0, 1, 0);
    RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();
}

void SceneLevelOneB::RenderBoss(float xpos, float zpos)
{
	float rotGhost;
	Vector3 view = (Vector3(xpos,0,zpos) - camera.position).Normalize();
	if (camera.target.z > camera.position.z)
	{
		rotGhost = Math::RadianToDegree(atan(view.x / view.z)) - 180;
	}
	else
	{
		rotGhost = Math::RadianToDegree(atan(view.x / view.z));
	}
    modelStack.PushMatrix();//boss start

    modelStack.Translate(xpos, 4, zpos);
	modelStack.Rotate(rotGhost-90, 0, 1, 0);
    modelStack.Scale(5, 5, 5);
    RenderMesh(meshList[GEO_BOSS1], true);

    if (BossOne.AttackAnimation)
    {
        modelStack.PushMatrix();
        modelStack.Translate(0, 4, 0);
        modelStack.Rotate(BossOne.CrystalAnim, 1, 1, 0);
		RenderMesh(meshList[GEO_CRYSTAL1], true);
        modelStack.PopMatrix();

        modelStack.PushMatrix();
        modelStack.Translate(0, 4, 0);
        modelStack.Rotate(BossOne.CrystalAnim, -1, 1, 0);
		RenderMesh(meshList[GEO_CRYSTAL2], true);
        modelStack.PopMatrix();
    }

    modelStack.PopMatrix();//boss end
}

void SceneLevelOneB::EnvironmentAnimation(double dt)
{
    EnvRotateY += (float)(20.f * dt);
}

void SceneLevelOneB::attackCheck()
{
    //Ghost combat checker

    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(20.f, PuzzleGhost1.MobPosX, PuzzleGhost1.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        PuzzleGhost1.TakeDamage(Explorer::instance()->itemAttack[Variables.i_SlotIndex - 1]);
    }

    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(20.f, PuzzleGhost2.MobPosX, PuzzleGhost2.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        PuzzleGhost2.TakeDamage(Explorer::instance()->itemAttack[Variables.i_SlotIndex - 1]);
    }
    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(60.f, BossOne.MobPosX, BossOne.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        BossOne.TakeDamage(Explorer::instance()->itemAttack[Variables.i_SlotIndex - 1]);//temporary variable is 1
    }
}

void SceneLevelOneB::MobsSpawn()
{
    
    if (proximitycheck(216, 240, -256, -248) && PuzzleGhost1.health >0)
    {
        PuzzleGhost1.Spawn = true;
    }
    if (proximitycheck(216, 240, -256, -248) && PuzzleGhost2.health >0)
    {
        PuzzleGhost2.Spawn = true;
    }
    if (proximitycheck(-304, -280, -392, -384) && BossOne.health>0)
    {
        std::cout << "boss" << std::endl;
        BossOne.Spawn = true;
    }
        
}

void SceneLevelOneB::AnimationCheck(double dt)
{
	if (activateDoor1)
	{
		anima.OpenSlideDoor1(dt);
	}
	if (activateDoor2)
	{
		anima.OpenSlideDoor2(dt);
		anima.OpenSlideDoor3(dt);
	}
	if (activateDoor3_1)
	{
		anima.OpenSlideDoor_Boss(dt);
	}
	else if (activateDoor3_2)
	{
		anima.CloseSlideDoor_Boss(dt);
	}

	if (!BossOne.Spawn && activateDoor3_1)
	{
		anima.OpenSlideDoor_Boss(dt);
	}

	if (activateDoor4)
	{
		anima.OpenSlideDoor4(dt);
	}

}

void SceneLevelOneB::checkPlayerPosMisc()
{
    Misc.camX = camera.position.x;
    Misc.camY = camera.position.y;
    Misc.camZ = camera.position.z;
}

// Puzzle Renderings
void SceneLevelOneB::RenderPuzzle()
{
	//levers
	modelStack.PushMatrix();
		modelStack.Translate(320, 6, -168);
		modelStack.Rotate(45, 0, 0, 1);
		modelStack.Rotate(Variables.f_SwitchRotateOne, 0, 0, 1);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_PUZZLELEVER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(320, 6, -144);
		modelStack.Rotate(45, 0, 0, 1);
		modelStack.Rotate(Variables.f_SwitchRotateTwo, 0, 0, 1);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_PUZZLELEVER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(320, 6, -120);
		modelStack.Rotate(45, 0, 0, 1);
		modelStack.Rotate(Variables.f_SwitchRotateThree, 0, 0, 1);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_PUZZLELEVER], true);
	modelStack.PopMatrix();

	//buttons
	if (!Switches.b_PuzzleOne[0])
	{
		modelStack.PushMatrix();
			modelStack.Translate(320, 15, -168);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_LIGHTRED], true);
		modelStack.PopMatrix();
	}
	else if (Switches.b_PuzzleOne[0])
	{
		modelStack.PushMatrix();
			modelStack.Translate(320, 15, -168);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_LIGHTGREEN], true);
		modelStack.PopMatrix();
	}

	if (!Switches.b_PuzzleOne[1])
	{
		modelStack.PushMatrix();
			modelStack.Translate(320, 15, -144);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_LIGHTRED], true);
		modelStack.PopMatrix();
	}
	else if (Switches.b_PuzzleOne[1])
	{
		modelStack.PushMatrix();
			modelStack.Translate(320, 15, -144);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_LIGHTGREEN], true);
		modelStack.PopMatrix();
	}

	if (!Switches.b_PuzzleOne[2])
	{
		modelStack.PushMatrix();
			modelStack.Translate(320, 15, -120);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_LIGHTRED], true);
		modelStack.PopMatrix();
	}
	else if (Switches.b_PuzzleOne[2])
	{
		modelStack.PushMatrix();
			modelStack.Translate(320, 15, -120);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_LIGHTGREEN], true);
		modelStack.PopMatrix();
	}
}

void SceneLevelOneB::RenderPlayerDiesInteraction()
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
			RenderTextOnScreen(meshList[GEO_TEXT], "You are Dead!", Color(1, 0.2, 1), 5.0f, 4.5f, 9.0f);
		}

		else if (Variables.f_redScreenTimer > 4.0f)
		{
			if (Explorer::instance()->PlayerLife > 0)
			{
				RenderModelOnScreen(meshList[GEO_DEADBLACKSCREEN], 100.0f, 100.0f, 100.0f, 90, 1, 0, 0, 0.3f, 0.5f, 0, false);
				RenderTextOnScreen(meshList[GEO_TEXT], "You are Dead!", Color(1, 0.2, 1), 5.0f, 4.5f, 9.0f);
				RenderTextOnScreen(meshList[GEO_TEXT], "Continue? (Y/ N)", Color(1, 1, 1), 5.0f, 4.0f, 8.0f);
			}

			else if (Explorer::instance()->PlayerLife <= 0)
			{
				RenderModelOnScreen(meshList[GEO_DEADBLACKSCREEN], 100.0f, 100.0f, 100.0f, 90, 1, 0, 0, 0.3f, 0.5f, 0, false);
				RenderTextOnScreen(meshList[GEO_TEXT], "You are Dead!", Color(1, 0.2, 1), 5.0f, 4.5f, 9.0f);
				RenderTextOnScreen(meshList[GEO_TEXT], "Game Over!", Color(1, 1, 1), 5.0f, 5.0f, 8.0f);

				if (Variables.f_redScreenTimer > 8.0f)
				{
					Application::OpenGame();
				}
			}
		}
	}
}