#include "SPGame.h"

int yScale = 2;
//these codes use x and z coordinates according to DRAWN COORDINATES and not actual z,x coords
void SPGame::RenderDownWall(int xPosLarge, int xPosSmall, int zPos)//positive Z facing wall
{
    zPos = -zPos;
    int xMaxCount = xPosLarge - xPosSmall;
    int zPosActual;
    int xPosActual;

    
    //finds the actual z coord
    if (zPos == 0)
    {
        zPosActual = 0;
    }
    else if (zPos < 0)
    {
        zPosActual = (zPos * 8) + 4;
    }
    else if (zPos > 0)
    {
        zPosActual = (zPos * 8) + 4;
    }

    //generate
    for (int count = 0; count < xMaxCount; count++)
    {
        if (count == 0)
        {
            xPosActual = ((xPosSmall * 8) + 4);
        }
        if(count > 0)
        {
            xPosActual = xPosActual + 8;
        }
     

        modelStack.PushMatrix();
        modelStack.Translate(xPosActual, -8, zPosActual);
        modelStack.Scale(1, yScale, 1);

        modelStack.PushMatrix();
        modelStack.Translate(0, 8, 0);
        modelStack.Rotate(90, 1, 0, 0);
        modelStack.Rotate(90, 0, 1, 0);
        modelStack.Scale(8, 8, 8);
        RenderMesh(meshList[GEO_FACILITYWALLS], true);
        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }
}
void SPGame::RenderUpWall(int xPosLarge, int xPosSmall, int zPos)//negative Z facing Wall
{
    zPos = -zPos;
    int xMaxCount = xPosLarge - xPosSmall;
    int zPosActual;
    int xPosActual;


    //finds the actual z coord
    if (zPos == 0)
    {
        zPosActual = 0;
    }
    else if (zPos < 0)
    {
        zPosActual = (zPos * 8) + 4;
    }
    else if (zPos > 0)
    {
        zPosActual = (zPos * 8) + 4;
    }

    //generate
    for (int count = 0; count < xMaxCount; count++)
    {
        if (count == 0)
        {
            xPosActual = ((xPosSmall * 8) + 4);
        }
        if (count > 0)
        {
            xPosActual = xPosActual + 8;
        }

        modelStack.PushMatrix();
        modelStack.Translate(xPosActual, -8, zPosActual);
        modelStack.Rotate(180, 0, 1, 0);
        modelStack.Scale(1, yScale, 1);

        modelStack.PushMatrix();
        modelStack.Translate(0, 8, 0);
        modelStack.Rotate(90, 1, 0, 0);
        modelStack.Rotate(90, 0, 1, 0);
        modelStack.Scale(8, 8, 8);
        RenderMesh(meshList[GEO_FACILITYWALLS], true);
        modelStack.PopMatrix();

        modelStack.PopMatrix();

    }
 
}
void SPGame::RenderRightWall(int zPosLarge, int zPosSmall, int xPos)// positive X facing wall
{
    
    int zMaxCount = zPosLarge - zPosSmall;
    int zPosActual;
    int xPosActual = 0;


    //finds the actual z coord
    if (xPos == 0)
    {
        xPosActual = 0;
    }
    else if (xPos < 0)
    {
        xPosActual = (xPos * 8);
    }
    else if (xPos > 0)
    {
        xPosActual = xPos * 8;
    }

    //generate
    for (int count = 0; count < zMaxCount; count++)
    {
        if (count == 0)
        {
            zPosActual = ((zPosSmall * 8));
        }
        if (count > 0)
        {
            zPosActual = zPosActual + 8;
        }

        modelStack.PushMatrix();
        modelStack.Translate(xPosActual, -8, -zPosActual);
        modelStack.Rotate(-90, 0, 1, 0);
        modelStack.Scale(1, yScale, 1);

        modelStack.PushMatrix();
        modelStack.Translate(0, 8, 0);
        modelStack.Rotate(-90, 1, 0, 0);
        modelStack.Rotate(90, 0, 1, 0);
        modelStack.Scale(8, 8, 8);
        RenderMesh(meshList[GEO_FACILITYWALLS], true);
        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }
   
}
void SPGame::RenderLeftWall(int zPosLarge, int zPosSmall, int xPos)//negative X facing wall
{
    int zMaxCount = zPosLarge - zPosSmall;
    int zPosActual;
    int xPosActual = 0;


    //finds the actual z coord
    if (xPos == 0)
    {
        xPosActual = 0;
    }
    else if (xPos < 0)
    {
        xPosActual = (xPos * 8);
    }
    else if (xPos > 0)
    {
        xPosActual = xPos * 8;
    }

    //generate
    for (int count = 0; count < zMaxCount; count++)
    {
        if (count == 0)
        {
            zPosActual = ((zPosSmall * 8));
        }
        if (count > 0)
        {
            zPosActual = zPosActual + 8;
        }

        modelStack.PushMatrix();
        modelStack.Translate(xPosActual, -8, -zPosActual);
        modelStack.Rotate(-90, 0, 1, 0);
        modelStack.Scale(1, yScale, 1);

        modelStack.PushMatrix();
        modelStack.Translate(0, 8, 0);
        modelStack.Rotate(90, 1, 0, 0);
        modelStack.Rotate(90, 0, 1, 0);
        modelStack.Scale(8, 8, 8);
        RenderMesh(meshList[GEO_FACILITYWALLS], true);
        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }
}