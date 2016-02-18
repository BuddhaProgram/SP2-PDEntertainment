#include "SPGame.h"


//renders the default sky box
void SPGame::RenderSkyBox()
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

//renders planetfloor
void SPGame::RenderPlanetFloor()
{
    modelStack.PushMatrix();
    modelStack.PushMatrix();
    modelStack.Translate(-7.4, 0, -7.4);
    for (int a = 0, z = 1; a < 20; a++, z++)
    {
        for (int i = 0, x = 1; i < 20; i++, x++)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z * 7.4);
            // modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_PLANETFLOOR], true);
            modelStack.PopMatrix();
        }
    }
    modelStack.PopMatrix();
    for (int a = 0, z = -1.5; a < 20; a++, z--)
    {
        for (int i = 0, x = 0.5; i < 20; i++, x++)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z *7.4);
            //modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_PLANETFLOOR], true);
            modelStack.PopMatrix();
        }
    }
    for (int a = 0, z = 0.5; a < 20; a++, z++)
    {
        for (int i = 0, x = -1.5; i < 20; i++, x--)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z *7.4);
            //modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_PLANETFLOOR], true);
            modelStack.PopMatrix();

        }
    }
    for (int a = 0, z = -1.5; a < 20; a++, z--)
    {
        for (int i = 0, x = -1.5; i < 20; i++, x--)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z *7.4);
            // modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_PLANETFLOOR], true);
            modelStack.PopMatrix();
        }
    }
    modelStack.PopMatrix();
}

//renders facility floor
void SPGame::RenderFacilityFloor()
{
    modelStack.PushMatrix();
    

    modelStack.PushMatrix();
    modelStack.Translate(-7.4, 0, -7.4);
    for (int a = 0, z = 1; a < 20; a++, z++)
    {
        for (int i = 0, x = 1; i < 20; i++, x++)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z * 7.4);
            // modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_FACILITYFLOOR], true);
            modelStack.PopMatrix();
        }
    }
    modelStack.PopMatrix();
    for (int a = 0, z = -1.5; a < 20; a++, z--)
    {
        for (int i = 0, x = 0.5; i < 20; i++, x++)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z *7.4);
            //modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_FACILITYFLOOR], true);
            modelStack.PopMatrix();
        }
    }
    for (int a = 0, z = 0.5; a < 20; a++, z++)
    {
        for (int i = 0, x = -1.5; i < 20; i++, x--)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z *7.4);
            //modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_FACILITYFLOOR], true);
            modelStack.PopMatrix();

        }
    }
    for (int a = 0, z = -1.5; a < 20; a++, z--)
    {
        for (int i = 0, x = -1.5; i < 20; i++, x--)
        {
            modelStack.PushMatrix();
            modelStack.Translate(x * 7.4, 0, z *7.4);
            // modelStack.Scale(1.5, 1, 1.5);		
            RenderMesh(meshList[GEO_FACILITYFLOOR], true);
            modelStack.PopMatrix();
        }
    }
    modelStack.PopMatrix();
}


// renders the Starting level
void SPGame::RenderSceneStart()
{
    //basic renders
    RenderPlanetFloor();
    RenderSkyBox();

    //structure renders
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -90);
    modelStack.Scale(6, 6, 4);
    RenderMesh(meshList[GEO_FACILITYOUT], true);
    modelStack.PopMatrix();

    //object renders


    //Enemy renders
    if (Ghost.Spawn)
    {
        RenderGhost1();
    }



}

//render the exit level
void SPGame::RenderSceneEnd()
{
    //basic renders
    RenderPlanetFloor();
    RenderSkyBox();

    //structure renders
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 90);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(6, 6, 4);
    RenderMesh(meshList[GEO_FACILITYOUT], true);
    modelStack.PopMatrix();

    //object renders


    //Enemy renders
    if (Ghost.Spawn)
    {
        RenderGhost1();
    }
}

void SPGame::RenderLevel1()
{
    //basic renders
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 0, camera.position.z);//move the floor with the player
	RenderFacilityFloor();
	modelStack.PopMatrix();
	RenderSkyBox();

    //structure renders

    //object renders


    //Enemy renders

    if (Ghost.Spawn)
    {
        RenderGhost1();
    }
}

void SPGame::RenderGhost1()
{
    modelStack.PushMatrix();
    modelStack.Translate(Ghost.MobPosX, Ghost.MobPosY, Ghost.MobPosZ);
    modelStack.Rotate(RotateY, 0, 1, 0);
    RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();
}