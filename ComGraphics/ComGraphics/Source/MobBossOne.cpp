#include "MobBossOne.h"

MobBossOne::MobBossOne()
{
    //global variables for use in entire project
    Spawn = false;

    //mob position variables
    MobPosX = 1;
    MobPosY = 6;
    MobPosZ = 1;

    //player detection variables
    TargetDetectX = 0;
    TargetDetectZ = 0;

    //timer variable
    mobTimeCount = 0;

    health = 10;
    AttackDamage = 30;
    kenaWhack = false;
}

MobBossOne::~MobBossOne()
{

}

void MobBossOne::knockback()
{
    kenaWhack = true;
}

void MobBossOne::move(double dt, int movespeed = 10)
{
    if (!AttackAnimation)
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

        /*if (Misc.WithinArea(MobPosX - 10, MobPosX + 10, MobPosZ - 10, MobPosZ + 10))
        {
            AttackAnimation = true;
        }*/
    }
}

void MobBossOne::setSpawnBossOne(float xpos, float zpos)
{
    MobPosX = xpos * 8;
    MobPosZ = -(zpos * 8);
}
void MobBossOne::TakeDamage(int damage)
{
    health = health - damage;
}

void MobBossOne::attack()
{
    AttackAnimation = true;
    //Explorer::takeDamage(AttackDamage);
}