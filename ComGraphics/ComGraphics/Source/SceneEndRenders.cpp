#include "SceneEnd.h"
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



//void SceneEnd::

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
    RenderSkyBox();

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
			}
		}
	}
}