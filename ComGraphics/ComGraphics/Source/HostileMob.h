#ifndef HOSTILEMOB_H
#define HOSTILEMOB_H

#include "Scene.h"
#include "Camera3.h"
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "OBJAnimation.h"
#include "PlayerStat.h"
#include "ToolSection.h"

class HostileMob
{
public:
    HostileMob();
    ~HostileMob();

    //functions
    void checkPlayerPos();
    void move(double dt);

    //global variables for use in entire project
    bool Spawn;
    float MobRotateY;

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

