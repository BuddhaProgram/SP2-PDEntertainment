#include "HostileMob.h"


HostileMob::HostileMob()
{
    //global variables for use in entire project
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

HostileMob::~HostileMob()
{
    
}

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

void HostileMob::MobCollision(float smallx, float largex, float smallz, float largez)
{
    if ((MobPosX >= smallx) && (MobPosX <= largex) && (MobPosZ >= smallz) && (MobPosZ <= smallz + 3.f)){ MobPosZ = smallz; }
    if ((MobPosX >= smallx) && (MobPosX <= largex) && (MobPosZ <= largez) && (MobPosZ >= largez - 3.f)){ MobPosZ = largez; }
    if ((MobPosZ >= smallz) && (MobPosZ <= largez) && (MobPosX >= smallx) && (MobPosX <= smallx + 3.f)){ MobPosX = smallx; }
    if ((MobPosZ >= smallz) && (MobPosZ <= largez) && (MobPosX <= largex) && (MobPosX >= largex - 3.f)){ MobPosX = largex; }
}


