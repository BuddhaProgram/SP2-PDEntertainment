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

void HostileMob::checkPlayerPos(double dt, int checkRate = 1, int lessenSpeed = 1)
{
    mobTimeCount += (((float)(dt)* checkRate) / lessenSpeed);
    if (mobTimeCount >= 1)
    {
        TargetDetectX = camera.position.x;
        TargetDetectZ = camera.position.z;
        mobTimeCount = 0;
    }
}



