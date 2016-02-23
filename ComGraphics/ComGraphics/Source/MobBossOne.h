#ifndef MOBBOSSONE_H
#define MOBBOSSONE_H

#include "HostileMob.h"


class MobBossOne : public HostileMob
{
public:
    MobBossOne();
    ~MobBossOne();

    void setSpawnBossOne(float xpos, float zpos);
    void move(double dt, int movespeed);
    void attack();
    void knockback();
    void TakeDamage(int damage);

private:
    bool kenaWhack;
    bool AttackAnimation;




};

#endif