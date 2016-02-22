#include "MobGhost.h"

MobGhost::MobGhost()
{
    //global variables for use in entire project
    Spawn = false;

    //mob position variables
    MobPosX = 0;
    MobPosY = 6;
    MobPosZ = 0;

    //player detection variables
    TargetDetectX = 0;
    TargetDetectZ = 0;

    //timer variable
    mobTimeCount = 0;

    health = 2;
}

MobGhost::~MobGhost()
{

}

void MobGhost::move(double dt, int movespeed)
{
    //note: target detect x and y is player position, its function is in scene cpp file
    Vector3 start = Vector3(MobPosX, MobPosY, MobPosZ);
    Vector3 end = Vector3(TargetDetectX, 15, TargetDetectZ);
    Vector3 toNorm = end - start;
    Vector3 mob = start;

    float distance = sqrt(MobPosX * TargetDetectX + MobPosY * 15 + TargetDetectZ * MobPosZ);
    Vector3 direction = toNorm.Normalize();

    mob += direction * (float)(movespeed * dt);

    MobPosX = mob.x;
    MobPosZ = mob.z;
}

void MobGhost::setSpawnGhost(int xpos, int zpos)
{
    MobPosX = xpos;
    MobPosZ = zpos;
}
void MobGhost::TakeDamage(int damage)
{
    health = health - damage;
}