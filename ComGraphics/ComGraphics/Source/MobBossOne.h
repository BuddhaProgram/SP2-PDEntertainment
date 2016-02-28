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
    void attack(float damage);
    void knockback();
    void TakeDamage(int damage);
    void checkAttack(double dt);
    bool proximitycheck(float smallx, float largex, float smallz, float largez);
    bool AttackAnimation;
    float CrystalAnim;

	bool BossDies;

private:
    bool kenaWhack;
    
    float animtimer;




};

#endif