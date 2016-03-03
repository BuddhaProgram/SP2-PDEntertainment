/*************************************************************/
/*!
\file       HostileMob.h
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Parent class for enemy units
*/
/*************************************************************/
#ifndef HOSTILEMOB_H
#define HOSTILEMOB_H

#include "Explorer.h"
#include "Vector3.h"
/*************************************************************/
/*!
Class HostileMob:
\brief
parent class for all enemy units
*/
/*************************************************************/
class HostileMob
{
public:
    HostileMob();//Default constructor
    ~HostileMob();//Destructor

    //functions
    void checkPlayerPos(double dt, int checkRate, int lessenSpeed, float xpos, float zpos);
    void MobCollision(float smallx, float largex, float smallz, float largez);
    

    bool Spawn;

    int health;
    float AttackDamage;

    //mob position variables
    float MobPosX;
    float MobPosY;
    float MobPosZ;

    //player detection variables
    float TargetDetectX;
    float TargetDetectZ;
    float mobTimeCount;
   
};
#endif

