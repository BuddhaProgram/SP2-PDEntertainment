#ifndef HOSTILEMOB_H
#define HOSTILEMOB_H

#include "Vector3.h"
#include "MatrixStack.h"
#include "Camera3.h"

class HostileMob
{
public:
    HostileMob();
    ~HostileMob();

    //functions
    void checkPlayerPos(double dt, int checkRate, int lessenSpeed);
    

    bool Spawn;

    int health;

    //mob position variables
    float MobPosX;
    float MobPosY;
    float MobPosZ;

    //player detection variables
    float TargetDetectX;
    float TargetDetectZ;
    float mobTimeCount;

    Camera3 camera;
};
#endif

