/*************************************************************/
/*!
\file       HostileMob.cpp
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Function definitions for class HostileMob
*/
/*************************************************************/
#include "HostileMob.h"

/*************************************************************/
/*!
\brief 
Default constructor for class HostileMob
*/
/*************************************************************/
HostileMob::HostileMob()
{
    Spawn = false;

    //mob position variables
    MobPosX = 0;
    MobPosY = 6;
    MobPosZ = 15;

    //player detection variables
    TargetDetectX = 0;
    TargetDetectZ = 0;

    //timer variable
    mobTimeCount = 0;

    health = 1;
}
/*************************************************************/
/*!
\brief
Destructor for class HostileMob
*/
/*************************************************************/

HostileMob::~HostileMob()
{
    
}
/*************************************************************/
/*!
\brief
Checks for player position and updates TargetDetectX and TargetDetectZ accordingly

\param double dt
Delta time
\param int checkRate, lessenspeed
variables that adjust the Frequency of checks 
\param xpos,zpos 
takes in the camera position on the x and z axis
*/
/*************************************************************/
void HostileMob::checkPlayerPos(double dt, int checkRate = 1, int lessenSpeed = 1, float xpos = 0, float zpos = 0)
{
    mobTimeCount += (((float)(dt)* checkRate) / lessenSpeed);
    if (mobTimeCount >= 1)
    {
        TargetDetectX = xpos;
        TargetDetectZ = zpos;
        mobTimeCount = 0;
    }
}

/****************************************************************************/
/*!
\brief
This Function checks for camera position and relative target and stops 'movement'

\param smallx
the smaller x value of the AABB bounding box

\param largex
the larger x value of the AABB bounding box

\param smallz
the smaller z value of the AABB bounding box

\param largez
the larger z value of the AABB bounding box
*/
/****************************************************************************/
>>>>>>> origin/master
void HostileMob::MobCollision(float smallx, float largex, float smallz, float largez)
{
    if ((MobPosX >= smallx) && (MobPosX <= largex) && (MobPosZ >= smallz) && (MobPosZ <= smallz + 3.f)){ MobPosZ = smallz; }
    if ((MobPosX >= smallx) && (MobPosX <= largex) && (MobPosZ <= largez) && (MobPosZ >= largez - 3.f)){ MobPosZ = largez; }
    if ((MobPosZ >= smallz) && (MobPosZ <= largez) && (MobPosX >= smallx) && (MobPosX <= smallx + 3.f)){ MobPosX = smallx; }
    if ((MobPosZ >= smallz) && (MobPosZ <= largez) && (MobPosX <= largex) && (MobPosX >= largex - 3.f)){ MobPosX = largex; }
}


