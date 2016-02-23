#ifndef MOBGHOST_H
#define MOBGHOST_H

#include "HostileMob.h"


class MobGhost : public HostileMob
{
public:
    MobGhost();
    ~MobGhost();

    void setSpawnGhost(float xpos, float zpos);
    void move(double dt, int movespeed);
    void knockback();
    void TakeDamage(int damage);

private:
    bool kenaWhack;


    

};

#endif