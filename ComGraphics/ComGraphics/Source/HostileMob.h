#ifndef HOSTILEMOB_H
#define HOSTILEMOB_H


class HostileMob
{
public:
    HostileMob();
    ~HostileMob();

    //functions
    void checkTarget();
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

    Camera3 camera;
    
};
#endif

