#include "SceneEnd.h"
#include "SceneEndCutScene.h"
#include "Application.h"
#include "OBJAnimation.h"

//renders the default sky box
void SceneEnd::RenderSkyBox()
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
void SceneEnd::RenderFloor()
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

//render the exit level
void SceneEnd::RenderSceneEnd()
{
    //structure renders
    modelStack.PushMatrix();
		modelStack.Translate(0, 0, 90);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(6, 6, 4);
		RenderMesh(meshList[GEO_FACILITYOUT], true);
		modelStack.PopMatrix();
    //object renders

}


void SceneEnd::RenderPlayerDiesInteraction()
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

void SceneEnd::RenderShipAndPod()
{
	modelStack.PushMatrix();
		modelStack.Translate(0, -2, -200);
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_SPACESHIP], true);
	modelStack.PopMatrix();

	if (b_RepairDone[0] == false)
	{
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, -240);
			modelStack.Scale(12, 12, 12);
			modelStack.Rotate(45, 0, 1, 0);
			RenderMesh(meshList[GEO_REPAIRPOD], true);
		modelStack.PopMatrix();
	}

	else
	{
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, -240);
			modelStack.Scale(12, 12, 12);
			modelStack.Rotate(45, 0, 1, 0);
			RenderMesh(meshList[GEO_REPAIRDONE], true);
		modelStack.PopMatrix();
	}

	if (b_RepairDone[1] == false)
	{
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, -160);
			modelStack.Scale(12, 12, 12);
			modelStack.Rotate(45, 0, 1, 0);
			RenderMesh(meshList[GEO_REPAIRPOD], true);
		modelStack.PopMatrix();
	}

	else
	{
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, -160);
			modelStack.Scale(12, 12, 12);
			modelStack.Rotate(45, 0, 1, 0);
			RenderMesh(meshList[GEO_REPAIRDONE], true);
		modelStack.PopMatrix();
	}

	if (b_RepairDone[2] == false)
	{
		modelStack.PushMatrix();
			modelStack.Translate(-50, 0, -200);
			modelStack.Scale(12, 12, 12);
			modelStack.Rotate(45, 0, 1, 0);
			RenderMesh(meshList[GEO_REPAIRPOD], true);
		modelStack.PopMatrix();
	}

	else
	{
		modelStack.PushMatrix();
			modelStack.Translate(-50, 0, -200);
			modelStack.Scale(12, 12, 12);
			modelStack.Rotate(45, 0, 1, 0);
			RenderMesh(meshList[GEO_REPAIRDONE], true);
		modelStack.PopMatrix();
	}
}

void SceneEnd::RenderMineText()
{
	if (camera.position.x > -56.0f && camera.position.x < -44.0f && camera.position.z > -206.0f && camera.position.z < -194.0f)
	{
		if (b_RepairDone[2] == true && b_startRepair[2] == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Rocks are rem oved!", Color(0.1f, 0.3f, 1.0f), 3.0f, 9.0f, 8.0f);
		}

		if (b_RepairDone[2] == false && b_startRepair[2] == true && Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Pickaxe)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "M ine the rocks!", Color(0.1f, 0.3f, 1.f), 3.0f, 10.0f, 6.0f);
		}

		else if (b_RepairDone[2] == false && b_startRepair[2] == true && Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex != ToolUI::Pickaxe))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Use Pickaxe to mine!", Color(0.1f, 0.3f, 1.0f), 3.0f, 7.0f, 8.0f);
		}
	}
}

void SceneEnd::RenderRepairText()
{
	if (camera.position.x > -6.0f && camera.position.x < 6.0f && camera.position.z > -166.0f && camera.position.z < -154.0f)
	{
		if (b_RepairDone[1] == true && b_startRepair[1] == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Repair is done!", Color(0.1f, 0.3f, 1.0f), 3, 10.0f, 8.0f);
		}

		if (b_startRepair[1] == true && b_RepairDone[1] == false && Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Hand)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Repairing ...", Color(0.1f, 0.3f, 1), 3, 10.0f, 8.0f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(f_RepairProcess) + " %", Color(0.1f, 0.3f, 1), 3, 10.0f, 7.0f);
		}

		else if (b_startRepair[1] == true && b_RepairDone[1] == false && Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) != ToolUI::Hand)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Use Hands for repair!", Color(0.1f, 0.3f, 1.0f), 3, 8.0f, 8.0f);
		}
	}

	if (camera.position.x > -6.0f && camera.position.x < 6.0f && camera.position.z > -246.0f && camera.position.z < -234.0f)
	{
		if (b_RepairDone[0] == true && b_startRepair[0] == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Repair is done!", Color(0.1f, 0.3f, 1.0f), 3, 10.0f, 8.0f);
		}

		if (b_startRepair[0] == true && b_RepairDone[0] == false && Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) == ToolUI::Hand)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Repairing ...", Color(0.1f, 0.3f, 1), 3, 10.0f, 8.0f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(f_RepairProcess) + " %", Color(0.1f, 0.3f, 1), 3, 10.0f, 7.0f);
		}

		else if (b_startRepair[0] == true && b_RepairDone[0] == false && Explorer::instance()->GetToolType(Explorer::instance()->i_SlotIndex) != ToolUI::Hand)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Use Hands for repair!", Color(0.1f, 0.3f, 1.0f), 3, 8.0f, 8.0f);
		}
	}
}


void SceneEndCutScene::RenderSkyBox()
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
void SceneEndCutScene::RenderFloor()
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

void SceneEndCutScene::RenderSceneEndCutScene()
{
	//structure renders
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 90);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(6, 6, 4);
	RenderMesh(meshList[GEO_FACILITYOUT], true);
	modelStack.PopMatrix();
	//object renders

}

void SceneEndCutScene::RenderShipAndPod()
{
	modelStack.PushMatrix();
	modelStack.Translate(anima.MovingShip2, anima.MovingShip, -200);
	modelStack.Scale(15, 15, 15);
	RenderMesh(meshList[GEO_SPACESHIP], true);
	modelStack.PopMatrix();
}


void SceneEnd::RenderMobs(float xpos, float zpos)
{
    float rotGhost;
    Vector3 view = (Vector3(xpos, 0, zpos) - camera.position).Normalize();
    if (camera.target.z > camera.position.z)
    {
        rotGhost = Math::RadianToDegree(atan(view.x / view.z)) - 180;
    }
    else
    {
        rotGhost = Math::RadianToDegree(atan(view.x / view.z));
    }
   
        modelStack.PushMatrix();
        modelStack.Translate(xpos, 5, zpos);
        modelStack.Rotate(rotGhost - 90, 0, 1, 0);
        modelStack.Scale(4, 4, 4);
        RenderMesh(meshList[GEO_GHOST1], true);
        modelStack.PopMatrix();  
   
}

void SceneEnd::RenderBoss(float xpos, float zpos)
{
    float rotGhost;
    Vector3 view = (Vector3(xpos, 0, zpos) - camera.position).Normalize();
    if (camera.target.z > camera.position.z)
    {
        rotGhost = Math::RadianToDegree(atan(view.x / view.z)) - 180;
    }
    else
    {
        rotGhost = Math::RadianToDegree(atan(view.x / view.z));
    }
   
        std::cout << "Boss" << std::endl;
        //std::cout << BossOne.MobPosX << BossOne.MobPosZ << std::endl;
        modelStack.PushMatrix();
        modelStack.Translate(xpos, 5, zpos);
        modelStack.Scale(6, 6, 6);
        modelStack.PushMatrix();
        modelStack.Rotate(rotGhost - 90, 0, 1, 0);
        RenderMesh(meshList[GEO_BOSS], true);
        modelStack.PopMatrix();
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
        modelStack.PopMatrix();
    
}
void SceneEnd::checkAttack()
{
    //combat
    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(30.f, MobOne.MobPosX, MobOne.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        MobOne.TakeDamage(Explorer::instance()->itemAttack[Explorer::instance()->i_SlotIndex - 1]);
    }

    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(30.f, MobTwo.MobPosX, MobTwo.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        MobTwo.TakeDamage(Explorer::instance()->itemAttack[Explorer::instance()->i_SlotIndex - 1]);
    }
    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(30.f, MobThree.MobPosX, MobThree.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        MobThree.TakeDamage(Explorer::instance()->itemAttack[Explorer::instance()->i_SlotIndex - 1]);
    }
    if (Application::IsKeyPressed(VK_LBUTTON) && Misc.hitting(100.f, BossOne.MobPosX, BossOne.MobPosZ, 180, camera.position.x, camera.position.z, camera.view, camera.position))
    {
        BossOne.TakeDamage(Explorer::instance()->itemAttack[Explorer::instance()->i_SlotIndex - 1]);//temporary variable is 1
    }
    Collision(BossOne.MobPosX - 20, BossOne.MobPosX + 20, BossOne.MobPosZ - 20, BossOne.MobPosZ + 20);
    Collision(MobOne.MobPosX - 4, BossOne.MobPosX + 4, MobOne.MobPosZ - 4, MobOne.MobPosZ + 4);
    Collision(MobTwo.MobPosX - 4, MobTwo.MobPosX + 4, MobTwo.MobPosZ - 4, MobTwo.MobPosZ + 4);
    Collision(MobThree.MobPosX - 4, MobThree.MobPosX + 4, MobThree.MobPosZ - 4, MobThree.MobPosZ + 4);

}
void SceneEnd::MobCheck()
{
    if (BossOne.health <= 0)
    {
        ResetMobs();
    }
    else
    {
        BossOne.Spawn = false;
    }

        if (MobOne.health > 0)
        {
            MobOne.Spawn = true;
        }
        else
        {
            MobOne.Spawn = false;
        }

        if (MobTwo.health > 0)
        {
            MobTwo.Spawn = true;
        }
        else
        {
            MobTwo.Spawn = false;
        }

        if (MobThree.health > 0)
        {
            MobThree.Spawn = true;
        }
        else
        {
            MobTwo.Spawn = false;
        }

        if (!MobOne.Spawn && !MobTwo.Spawn && !MobThree.Spawn && BossOne.health >= 0)
        {
            BossOne.Spawn = true;
        }
        else
        {
            BossOne.Spawn = false;
        }
    checkAttack();   
}

void SceneEnd::moveMob(double dt)
{
    if (MobOne.Spawn)
    {
        MobOne.move(dt, MobMS);
    }

    if (MobTwo.Spawn)
    {
        MobTwo.move(dt, MobMS);
    }
    if (MobThree.Spawn)
    {
        MobThree.move(dt, MobMS);
    }
    if (BossOne.Spawn)
    {
        BossOne.move(dt, BossMS);
    }
}

void SceneEnd::ResetMobs()
{
    std::cout << "Reset" << std::endl;
    waveCounter += 1;

    MobOne.health = 8 + waveCounter * 4;
    MobTwo.health = 8 + waveCounter * 4;
    MobThree.health = 8 + waveCounter * 4;
    BossOne.health = 32 + waveCounter * 8;

    MobMS += 5.f;
    BossMS += 5.f;

    MobOne.setSpawnGhost(25, -8);
    MobTwo.setSpawnGhost(26, 73);
    MobThree.setSpawnGhost(-22, 42);

    BossOne.setSpawnBossOne(-36, -6);
}