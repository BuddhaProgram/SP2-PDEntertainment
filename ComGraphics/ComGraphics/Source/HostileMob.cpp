#include "Assignment3.h"
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


void HostileMob::checkTarget()
{
    TargetDetectX = camera.position.x;
    TargetDetectZ = camera.position.z;
}

void HostileMob::move(double dt)
{
    mobTimeCount += ((float)(dt) * 5);
    if (mobTimeCount >= 1)
    {
    checkTarget();
    mobTimeCount = 0;
    }
    
    Vector3 start = Vector3(MobPosX, MobPosY, MobPosZ);
    Vector3 end = Vector3(TargetDetectX, camera.position.y, TargetDetectZ);
    Vector3 toNorm = end - start;
    Vector3 mob = start;

    float distance = sqrt(MobPosX * TargetDetectX + MobPosY * camera.position.y + TargetDetectZ * MobPosZ);
    Vector3 direction = toNorm.Normalize();

    mob += direction * (float)(100 * dt);

    MobPosX = mob.x;
    MobPosZ = mob.z;

    //MobRotateY = -camera.target.z;
}