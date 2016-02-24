#ifndef HOSTILEMOB_H
#define HOSTILEMOB_H

#include "Explorer.h"
#include "Vector3.h"



class HostileMob
{
public:
    HostileMob();
    ~HostileMob();

    //functions
    void checkPlayerPos(double dt, int checkRate, int lessenSpeed, float xpos, float zpos);
    

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

