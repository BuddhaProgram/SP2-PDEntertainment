/*************************************************************/
/*!
\file       HostileMob.cpp
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Function definitions for MobBossOne
*/
/*************************************************************/
#include "MobBossOne.h"

/*************************************************************/
/*!
\brief
Default constructor for class MobBossOne
*/
/*************************************************************/

MobBossOne::MobBossOne()
{
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

    health = 32;
    AttackDamage = 3;
    AttackAnimation = true;
    BossDies = false;
}
/*************************************************************/
/*!
\brief
Destructor for class HostileMob
*/
/*************************************************************/
MobBossOne::~MobBossOne()
{

}

void MobBossOne::knockback()
{
    kenaWhack = true;
}
/****************************************************************************/
/*!
\brief
This Function checks for camera position being near the edges of a AABB bounding box
, with a current allowance of 2.f.

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
/****************************************************************************/
/*!
\brief
This is the function that controls the boss attack cycle and checks if teh player is within the range of the boss's attack

\param dt
Delta time
*/
/****************************************************************************/
void MobBossOne::checkAttack(double dt)
{
    if (proximitycheck(MobPosX - 20, MobPosX + 20, MobPosZ - 20, MobPosZ + 20) && AttackAnimation)
    {
        attack(AttackDamage);
    }

    if (AttackAnimation)
    {
        animtimer += ((float)(dt));
        if (animtimer >= 8)
        {
            AttackAnimation = false;
            animtimer = 0;
        }
    }

    if (!AttackAnimation)
    {
        animtimer += ((float)(dt));
        if (animtimer >= 3)
        {
            AttackAnimation = true;
            animtimer = 0;
        }
    }
}
/****************************************************************************/
/*!
\brief
This function sets a target location for the mob to move towards and moves it towards the location by the specified movements speed

\param dt
Delta time
\param movespeed
The speed of the mob

*/
/****************************************************************************/
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
        if (health <= 0)
        {
            Spawn = false;
            BossDies = true;
        }
        else
        {
            BossDies = false;
        }
    
}
/****************************************************************************/
/*!
\brief
This is the function that takes in the spawn point of the mob in graph paper coordinates and converts it into world space

\param xpos, zpos
coordinates of spawn point in graph paper coordinates
*/
/****************************************************************************/
void MobBossOne::setSpawnBossOne(float xpos, float zpos)
{
    MobPosX = xpos * 8;
    MobPosZ = -(zpos * 8);
}
/****************************************************************************/
/*!
\brief
This is the function that minuses the specified damage from the mob's health

\param damage
the amount of damage to be dealt to the mob
*/
/****************************************************************************/
void MobBossOne::TakeDamage(int damage)
{
	health -= damage;
}
/****************************************************************************/
/*!
\brief
This is the function that inflicts damage on the player's health

\param Damage
Takes in the amount of damage to be dealt to the player's health
*/
/****************************************************************************/
void MobBossOne::attack(float damage)
{
   
	this->AttackDamage = damage;
	Explorer::instance()->MinusHP((float)(AttackDamage));
    
}