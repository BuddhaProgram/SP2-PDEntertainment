#include "CutSceneOne.h"
#include "OBJAnimation.h"

//renders the default sky box



void CutSceneOne::RenderCutSceneOne()
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