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

   
}

void SceneLevelTwo::RenderDoor()
{
    modelStack.PushMatrix();
    modelStack.Translate(204, 0, 59);
    modelStack.Scale(4.9f, 4, 5);
    RenderMesh(meshList[GEO_SLIDEDOORTOP], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(204, 0, 59);
    modelStack.Scale(4.9f, 4, 5);
    RenderMesh(meshList[GEO_SLIDEDOORBTM], false);
    modelStack.PopMatrix();

    Collision(190, 216, 54, 60);

    modelStack.PushMatrix();
    modelStack.Translate(204, anima.DoorSlideTop, -51);
    modelStack.Scale(4.9f, 4, 5);
    RenderMesh(meshList[GEO_SLIDEDOORTOP], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(204, anima.DoorSlideBtm, -51);
    modelStack.Scale(4.9f, 4, 5);
    RenderMesh(meshList[GEO_SLIDEDOORBTM], false);
    modelStack.PopMatrix();
}

void SceneLevelTwo::checkDoor1()
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

void SceneLevelTwo::RenderGhost1()
{
    modelStack.PushMatrix();
    modelStack.Translate(Ghost.MobPosX, Ghost.MobPosY, Ghost.MobPosZ);
    RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();
}

