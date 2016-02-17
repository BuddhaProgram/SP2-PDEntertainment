
#include "HostileMob.h"


HostileMob::HostileMob()
{
    //global variables for use in entire project
    Spawn = false;
    MobRotateY;

    //mob position variables
    MobPosX = 0;
    MobPosY = 6;
    MobPosZ = 15;

    //player detection variables
    TargetDetectX = 0;
    TargetDetectZ = 0;

    //timer variable
    mobTimeCount = 0;
}

HostileMob::~HostileMob()
{

}




void HostileMob::move(double dt)
{
   //note: target detect x and y is player position, its function is in assignment3.cpp
    Vector3 start = Vector3(MobPosX, MobPosY, MobPosZ);
    Vector3 end = Vector3(TargetDetectX, 15, TargetDetectZ);
    Vector3 toNorm = end - start;
    Vector3 mob = start;

    float distance = sqrt(MobPosX * TargetDetectX + MobPosY * 15 + TargetDetectZ * MobPosZ);
    Vector3 direction = toNorm.Normalize();

    mob += direction * (float)(200 * dt);

    MobPosX = mob.x;
    MobPosZ = mob.z;
    //MobRotateY = -camera.target.z;
}