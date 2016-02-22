#include "SceneLevelOneB.h"
#include "OBJAnimation.h"

// Rendering of Floor for all Scenes.
void SceneLevelOneB::RenderFloor()
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



//void SceneLevelOneB::
// renders the Starting level


void SceneLevelOneB::RenderScene()
{
   


    //------------------------------------------------------------------------
    //top quads

    RenderRightWall(63, 47, -43, 1);//1
    RenderDownWall(-10, -43, 62, 2);//2
    RenderLeftWall(63, 47, -10, 3);//3
    RenderUpWall(-10, -35, 47, 4);//4
    RenderUpWall(-38, -43, 47, 5);//5

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


    //TOP QUAD END
    //-----------------------------------------------------
}




void SceneLevelOneB::RenderGhost1()
{
    /* modelStack.PushMatrix();
    modelStack.Translate(Ghost.MobPosX, Ghost.MobPosY, Ghost.MobPosZ);
    RenderMesh(meshList[GEO_GHOST1], true);
    modelStack.PopMatrix();*/
}

