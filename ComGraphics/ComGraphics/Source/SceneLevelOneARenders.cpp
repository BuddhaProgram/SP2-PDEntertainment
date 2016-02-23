#include "SceneLevelOneA.h"
#include "OBJAnimation.h"



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



//void SceneLevelOneA::
// renders the Starting level


void SceneLevelOneA::RenderScene()
{
    modelStack.PushMatrix();
    modelStack.Translate(120, 5, 75);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_SPAWNPOINT], true);
    modelStack.PopMatrix();
    RenderFloorCeiling();

    //bottom left quadron
    modelStack.PushMatrix();
    modelStack.Translate(0, -7, 0);
    modelStack.Scale(1, 2.2, 1);
    RenderUpWall(-2, -5, -55, 1);//1 
    RenderRightWall(-49, -55, -5, 2);//2
    RenderUpWall(-5, -8, -49, 3);//3
    RenderRightWall(-38, -49, -8, 4);//4
    RenderUpWall(-8, -28, -38, 5);//5
    RenderRightWall(-28, -38, -26, 6);//6
    RenderUpWall(-26, -38, -28, 7);//7
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
	modelStack.Translate(0, 0, 500);
	modelStack.Scale(6, 6.1f, 4);
	RenderMesh(meshList[GEO_FACILITYOUT], true);
	modelStack.PopMatrix();

}

void SceneLevelOneA::TestDoorRender()
{
	modelStack.PushMatrix();
	modelStack.Translate(180, anima.DoorSlideTop, 188);
	modelStack.Scale(4.9f, 2, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(180, anima.DoorSlideBtm, 188);
	modelStack.Scale(4.9f, 2, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-191, anima.DoorSlideTop_2, 228);
	modelStack.Scale(4.9f, 2, 5);
	RenderMesh(meshList[GEO_SLIDEDOORTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-191, anima.DoorSlideBtm_2, 228);
	modelStack.Scale(4.9f, 2, 5);
	RenderMesh(meshList[GEO_SLIDEDOORBTM], false);
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
	modelStack.Translate(0, 3 + anima.RubbleCollapse, 450);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[GEO_RUBBLE], false);
	modelStack.PopMatrix();
}

