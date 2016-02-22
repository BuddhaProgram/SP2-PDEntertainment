#ifndef MOBGHOST_H
#define MOBGHOST_H

#include "HostileMob.h"


class MobGhost : HostileMob
{
public:
    MobGhost();
    ~MobGhost();

    void setSpawnGhost(int xpos, int zpos);
    void move(double dt, int movespeed);
    void knockback();
    void TakeDamage(int damage);


    

};

#endif