#include "MobBossOne.h"
#include "Misc.h"

misc Functions;

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
    AttackDamage = 1;
    kenaWhack = false;
}

MobBossOne::~MobBossOne()
{

}

void MobBossOne::knockback()
{
    kenaWhack = true;
}
bool MobBossOne::proximitycheck(float smallx, float largex, float smallz, float largez)
{
    //this function checks if the camera is close to a side of the object
    bool result = false;
    if ((TargetDetectX >= smallx - 2.f) && (TargetDetectX <= smallx) && (TargetDetectZ >= smallz) && (TargetDetectZ <= largez)){ result = true; }
    if ((TargetDetectX <= largex + 2.f) && (TargetDetectX >= largex) && (TargetDetectZ >= smallz) && (TargetDetectZ <= largez)){ result = true; }
    if ((TargetDetectX >= smallx) && (TargetDetectX <= largex) && (TargetDetectZ >= smallz - 2.f) && (TargetDetectZ <= smallz)){ result = true; }
    if ((TargetDetectX >= smallx) && (TargetDetectX <= largex) && (TargetDetectZ <= largez + 2.f) && (TargetDetectZ >= largez)){ result = true; }
    return result;
}
void MobBossOne::checkAttack(double dt)
{
    if (proximitycheck(MobPosX - 5, MobPosX + 5, MobPosZ - 5, MobPosZ + 5) && AttackAnimation)
    {
        attack();
    }

    if (AttackAnimation)
    {
        animtimer += ((float)(dt)* 1);
        if (animtimer >= 8)
        {
            AttackAnimation = false;
            animtimer = 0;
        }
    }

    if (!AttackAnimation)
    {
        animtimer += ((float)(dt)* 1);
        if (animtimer >= 3)
        {
            AttackAnimation = true;
            animtimer = 0;
        }
    }
}

void MobBossOne::move(double dt, int movespeed = 10)
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

        checkAttack(dt);

        CrystalAnim += 200 * (float)(dt);
    
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
    Explorer::instance()->hp -= AttackDamage;
}