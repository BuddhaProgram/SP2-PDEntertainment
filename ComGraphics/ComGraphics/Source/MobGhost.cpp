/*************************************************************/
/*!
\file       HostileMob.cpp
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Function definitions for class MobGhost
*/
/*************************************************************/
#include "MobGhost.h"

#include "Misc.h"

MobGhost::MobGhost()
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
    mobTimeCount = 0.f;
    mobTimeCount2 = 0.f;
    AttackDamage = 10;
    health = 8;
    canHit = true;
}

MobGhost::~MobGhost()
{

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
bool MobGhost::proximitycheck(float smallx, float largex, float smallz, float largez)
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
This is the function that inflicts damage on the player's health

\param Damage 
Takes in the amount of damage to be dealt to the player's health
*/
/****************************************************************************/
void MobGhost::attack(float Damage)
{
	this->AttackDamage = Damage;
	Explorer::instance()->MinusHP((float)(AttackDamage));
    canHit = false;
}
/****************************************************************************/
/*!
\brief
This is the function that checks if the player is within range of the mob's attack

*/
/****************************************************************************/
void MobGhost::checkAttack()
{
    if (proximitycheck(MobPosX - 5, MobPosX + 5, MobPosZ - 5, MobPosZ + 5) && canHit)
    {
        attack(AttackDamage);
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
    
    checkAttack();

    if (!canHit)
    {
        mobTimeCount2 += ((float)(1 * dt));
        if (mobTimeCount2 >= 1.f)
        {
            canHit = true;
            mobTimeCount2 = 0.f;
        }
    }

    if (health <= 0)
    {
        Spawn = false;
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

void MobGhost::setSpawnGhost(float xpos, float zpos)
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

void MobGhost::TakeDamage(int damage)
{
	health -= damage;
}
