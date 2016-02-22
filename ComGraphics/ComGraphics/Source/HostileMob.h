#ifndef HOSTILEMOB_H
#define HOSTILEMOB_H

#include "Vector3.h"


class HostileMob
{
public:
    HostileMob();
    ~HostileMob();

    //functions
    void checkPlayerPos();
    void move(double dt, int movespeed);

    //global variables for use in entire project
    
    float MobRotateY;
    bool Spawn;

    //ghost chase variables
    float MobPosX;
    float MobPosY;
    float MobPosZ;

    //player detection variables
    float TargetDetectX;
    float TargetDetectZ;
    float mobTimeCount;
    
};
#endif

