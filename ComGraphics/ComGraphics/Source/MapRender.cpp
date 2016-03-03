#include "SceneLevelOneA.h"
#include "SceneLevelOneB.h"
#include "SceneLevelTwo.h"
#include "SceneEnd.h"
/*************************************************************/
/*!
\file       MapRender.cpp
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Function definitions for map rendering
*/
/*************************************************************/

/****************************************************************************/
/*!
\brief
This is the function that Renders a positive Z facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space 

\param xPosLarge
Takes in the larger x coordinate
\param xPosSmall
Takes in the smaller x coordinate
\param zPos 
Takes in the z position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
//these codes use x and z coordinates according to GRAPH PAPER COORDINATES and not actual z,x coords.
void SceneLevelOneA::RenderDownWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber)//positive Z facing wall
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

	CollZLarge[wallNumber - 1] = (float)zPosActual + 4;
	CollZSmall[wallNumber - 1] = (float)zPosActual - 4;

    //generate
    for (int count = 0; count < xMaxCount; count++)
    {
        if (count == 0)
        {
            xPosActual = ((xPosSmall * 8) + 4);
			CollXSmall[wallNumber - 1] = (float)xPosActual - 5;
        }
        if(count > 0)
        {
            xPosActual = xPosActual + 8;
        }
        if (count == xMaxCount - 1)
        {
			CollXLarge[wallNumber - 1] = (float)xPosActual + 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, (float)zPosActual);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a negative Z facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param xPosLarge
Takes in the larger x coordinate
\param xPosSmall
Takes in the smaller x coordinate
\param zPos
Takes in the z position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelOneA::RenderUpWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber)//negative Z facing Wall
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
	CollZLarge[wallNumber - 1] = (float)zPosActual + 4;
	CollZSmall[wallNumber - 1] = (float)zPosActual - 4;

    //generate
    for (int count = 0; count < xMaxCount; count++)
    {
        if (count == 0)
        {
            xPosActual = ((xPosSmall * 8) + 4);
			CollXSmall[wallNumber - 1] = (float)xPosActual - 5;
        }
        if (count > 0)
        {
            xPosActual = xPosActual + 8;
        }
        if (count == xMaxCount - 1)
        {
			CollXLarge[wallNumber - 1] = (float)xPosActual + 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, (float)zPosActual);
        modelStack.Rotate(180, 0, 1, 0);
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
/****************************************************************************/
/*!
\brief
This is the function that Renders a positive x facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param zPosLarge
Takes in the larger z coordinate
\param zPosSmall
Takes in the smaller z coordinate
\param xPos
Takes in the x position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelOneA::RenderRightWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber)// positive X facing wall
{
    
    int zMaxCount = zPosLarge - zPosSmall;
    int zPosActual;
    int xPosActual = 0;


    //finds the actual x coord
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
	CollXLarge[wallNumber - 1] = (float)xPosActual + 4;
	CollXSmall[wallNumber - 1] = (float)xPosActual - 4;

    //generate
    for (int count = 0; count < zMaxCount; count++)
    {
        if (count == 0)
        {
            zPosActual = ((zPosSmall * 8));
			CollZLarge[wallNumber - 1] = -((float)zPosActual) + 5;
        }
        if (count > 0)
        {
            zPosActual = zPosActual + 8;
        }
        if (count == zMaxCount - 1)
        {
			CollZSmall[wallNumber - 1] = -((float)zPosActual) - 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, -(float)zPosActual);
        modelStack.Rotate(-90, 0, 1, 0);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a negative x facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param zPosLarge
Takes in the larger z coordinate
\param zPosSmall
Takes in the smaller z coordinate
\param xPos
Takes in the x position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelOneA::RenderLeftWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber)//negative X facing wall
{
    int zMaxCount = zPosLarge - zPosSmall;
    int zPosActual;
    int xPosActual = 0;


    //finds the actual x coord
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
	CollXLarge[wallNumber - 1] = (float)xPosActual + 4;
	CollXSmall[wallNumber - 1] = (float)xPosActual - 4;

    //generate
    for (int count = 0; count < zMaxCount; count++)
    {
        if (count == 0)
        {
            zPosActual = ((zPosSmall * 8));
			CollZLarge[wallNumber - 1] = -((float)zPosActual) + 5;
        }
        if (count > 0)
        {
            zPosActual = zPosActual + 8;
        }
        if (count == zMaxCount - 1)
        {
			CollZSmall[wallNumber - 1] = -((float)zPosActual) - 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, -(float)zPosActual);
        modelStack.Rotate(-90, 0, 1, 0);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a positive Z facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param xPosLarge
Takes in the larger x coordinate
\param xPosSmall
Takes in the smaller x coordinate
\param zPos
Takes in the z position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
//these codes use x and z coordinates according to DRAWN COORDINATES and not actual z,x coords
void SceneLevelOneB::RenderDownWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber)//positive Z facing wall
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

	CollZLarge[wallNumber - 1] = (float)zPosActual + 4;
	CollZSmall[wallNumber - 1] = (float)zPosActual - 4;

    //generate
    for (int count = 0; count < xMaxCount; count++)
    {
        if (count == 0)
        {
            xPosActual = ((xPosSmall * 8) + 4);
			CollXSmall[wallNumber - 1] = (float)xPosActual - 5;
        }
        if (count > 0)
        {
            xPosActual = xPosActual + 8;
        }
        if (count == xMaxCount - 1)
        {
			CollXLarge[wallNumber - 1] = (float)xPosActual + 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, (float)zPosActual);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a negative Z facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param xPosLarge
Takes in the larger x coordinate
\param xPosSmall
Takes in the smaller x coordinate
\param zPos
Takes in the z position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelOneB::RenderUpWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber)//negative Z facing Wall
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
	CollZLarge[wallNumber - 1] = (float)zPosActual + 4;
	CollZSmall[wallNumber - 1] = (float)zPosActual - 4;

    //generate
    for (int count = 0; count < xMaxCount; count++)
    {
        if (count == 0)
        {
            xPosActual = ((xPosSmall * 8) + 4);
			CollXSmall[wallNumber - 1] = (float)xPosActual - 5;
        }
        if (count > 0)
        {
            xPosActual = xPosActual + 8;
        }
        if (count == xMaxCount - 1)
        {
			CollXLarge[wallNumber - 1] = (float)xPosActual + 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, (float)zPosActual);
        modelStack.Rotate(180, 0, 1, 0);
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
/****************************************************************************/
/*!
\brief
This is the function that Renders a positive x facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param zPosLarge
Takes in the larger z coordinate
\param zPosSmall
Takes in the smaller z coordinate
\param xPos
Takes in the x position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/

void SceneLevelOneB::RenderRightWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber)// positive X facing wall
{

    int zMaxCount = zPosLarge - zPosSmall;
    int zPosActual;
    int xPosActual = 0;


    //finds the actual x coord
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
	CollXLarge[wallNumber - 1] = (float)xPosActual + 4;
	CollXSmall[wallNumber - 1] = (float)xPosActual - 4;

    //generate
    for (int count = 0; count < zMaxCount; count++)
    {
        if (count == 0)
        {
            zPosActual = ((zPosSmall * 8));
			CollZLarge[wallNumber - 1] = -((float)zPosActual) + 5;
        }
        if (count > 0)
        {
            zPosActual = zPosActual + 8;
        }
        if (count == zMaxCount - 1)
        {
			CollZSmall[wallNumber - 1] = -((float)zPosActual) - 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, -(float)zPosActual);
        modelStack.Rotate(-90, 0, 1, 0);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a negative x facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param zPosLarge
Takes in the larger z coordinate
\param zPosSmall
Takes in the smaller z coordinate
\param xPos
Takes in the x position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelOneB::RenderLeftWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber)//negative X facing wall
{
    int zMaxCount = zPosLarge - zPosSmall;
    int zPosActual;
    int xPosActual = 0;


    //finds the actual x coord
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
	CollXLarge[wallNumber - 1] = (float)xPosActual + 4;
	CollXSmall[wallNumber - 1] = (float)xPosActual - 4;

    //generate
    for (int count = 0; count < zMaxCount; count++)
    {
        if (count == 0)
        {
            zPosActual = ((zPosSmall * 8));
			CollZLarge[wallNumber - 1] = -((float)zPosActual) + 5;
        }
        if (count > 0)
        {
            zPosActual = zPosActual + 8;
        }
        if (count == zMaxCount - 1)
        {
			CollZSmall[wallNumber - 1] = -((float)zPosActual) - 5;
        }

        modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, -(float)zPosActual);
        modelStack.Rotate(-90, 0, 1, 0);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a positive Z facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param xPosLarge
Takes in the larger x coordinate
\param xPosSmall
Takes in the smaller x coordinate
\param zPos
Takes in the z position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/

//these codes use x and z coordinates according to DRAWN COORDINATES and not actual z,x coords
void SceneLevelTwo::RenderDownWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber)//positive Z facing wall
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

	CollZLarge[wallNumber - 1] = (float)zPosActual + 4;
	CollZSmall[wallNumber - 1] = (float)zPosActual - 4;

	//generate
	for (int count = 0; count < xMaxCount; count++)
	{
		if (count == 0)
		{
			xPosActual = ((xPosSmall * 8) + 4);
			CollXSmall[wallNumber - 1] = (float)xPosActual - 5;
		}
		if (count > 0)
		{
			xPosActual = xPosActual + 8;
		}
		if (count == xMaxCount - 1)
		{
			CollXLarge[wallNumber - 1] = (float)xPosActual + 5;
		}

		modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, (float)zPosActual);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a negative Z facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param xPosLarge
Takes in the larger x coordinate
\param xPosSmall
Takes in the smaller x coordinate
\param zPos
Takes in the z position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelTwo::RenderUpWall(int xPosLarge, int xPosSmall, int zPos, int wallNumber)//negative Z facing Wall
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
	CollZLarge[wallNumber - 1] = (float)zPosActual + 4;
	CollZSmall[wallNumber - 1] = (float)zPosActual - 4;

	//generate
	for (int count = 0; count < xMaxCount; count++)
	{
		if (count == 0)
		{
			xPosActual = ((xPosSmall * 8) + 4);
			CollXSmall[wallNumber - 1] = (float)xPosActual - 5;
		}
		if (count > 0)
		{
			xPosActual = xPosActual + 8;
		}
		if (count == xMaxCount - 1)
		{
			CollXLarge[wallNumber - 1] = (float)xPosActual + 5;
		}

		modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, (float)zPosActual);
		modelStack.Rotate(180, 0, 1, 0);
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
/****************************************************************************/
/*!
\brief
This is the function that Renders a positive x facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param zPosLarge
Takes in the larger z coordinate
\param zPosSmall
Takes in the smaller z coordinate
\param xPos
Takes in the x position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelTwo::RenderRightWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber)// positive X facing wall
{

	int zMaxCount = zPosLarge - zPosSmall;
	int zPosActual;
	int xPosActual = 0;


	//finds the actual x coord
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
	CollXLarge[wallNumber - 1] = (float)xPosActual + 4;
	CollXSmall[wallNumber - 1] = (float)xPosActual - 4;

	//generate
	for (int count = 0; count < zMaxCount; count++)
	{
		if (count == 0)
		{
			zPosActual = ((zPosSmall * 8));
			CollZLarge[wallNumber - 1] = -((float)zPosActual) + 5;
		}
		if (count > 0)
		{
			zPosActual = zPosActual + 8;
		}
		if (count == zMaxCount - 1)
		{
			CollZSmall[wallNumber - 1] = -((float)zPosActual) - 5;
		}

		modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, -(float)zPosActual);
		modelStack.Rotate(-90, 0, 1, 0);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders a negative x facing wall and outputs the coordinates needed to set it's collision. Additionally, this function takes in graph paper coordinates and coverts it into world space

\param zPosLarge
Takes in the larger z coordinate
\param zPosSmall
Takes in the smaller z coordinate
\param xPos
Takes in the x position of the wall
/param wll number
Takes in the assigned number for the wall
*/
/****************************************************************************/
void SceneLevelTwo::RenderLeftWall(int zPosLarge, int zPosSmall, int xPos, int wallNumber)//negative X facing wall
{
	int zMaxCount = zPosLarge - zPosSmall;
	int zPosActual;
	int xPosActual = 0;


	//finds the actual x coord
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
	CollXLarge[wallNumber - 1] = (float)xPosActual + 4;
	CollXSmall[wallNumber - 1] = (float)xPosActual - 4;

	//generate
	for (int count = 0; count < zMaxCount; count++)
	{
		if (count == 0)
		{
			zPosActual = ((zPosSmall * 8));
			CollZLarge[wallNumber - 1] = -((float)zPosActual) + 5;
		}
		if (count > 0)
		{
			zPosActual = zPosActual + 8;
		}
		if (count == zMaxCount - 1)
		{
			CollZSmall[wallNumber - 1] = -((float)zPosActual) - 5;
		}

		modelStack.PushMatrix();
		modelStack.Translate((float)xPosActual, 0, -(float)zPosActual);
		modelStack.Rotate(-90, 0, 1, 0);

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
/****************************************************************************/
/*!
\brief
This is the function that Renders the single wall for the final level and sets its collision

\param xpos
Takes in the x position of the wall
\param zpos
Takes in the zpos of the wall

*/
/****************************************************************************/
void SceneEnd::RenderDownWall(int xPos, int zPos)//positive Z facing wall
{
    modelStack.PushMatrix();
    modelStack.Scale(1, 8, 1);

    modelStack.PushMatrix();
	modelStack.Translate((float)xPos, 0, (float)zPos);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(8, 8, 1000);
    RenderMesh(meshList[GEO_FACILITYOUTWALL], true);
    modelStack.PopMatrix();
    modelStack.PopMatrix();

}


