/*************************************************************/
/*!
\file       MobBossOne.h
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Class for "Boss" type enemy
*/
/*************************************************************/

#ifndef MOBBOSSONE_H
#define MOBBOSSONE_H

#include "HostileMob.h"
/*************************************************************/
/*!
Class MobBossOne:
\brief
Class for "Boss" type enemy
*/
/*************************************************************/

class MobBossOne : public HostileMob
{
public:
    MobBossOne();
    ~MobBossOne();

    void setSpawnBossOne(float xpos, float zpos);
    void move(double dt, int movespeed);
    void attack(float damage);
    void TakeDamage(int damage);
    void checkAttack(double dt);
    bool proximitycheck(float smallx, float largex, float smallz, float largez);
    bool AttackAnimation;
    float CrystalAnim;
    bool BossDies;
	void knockback();
	bool kenaWhack;
private:
    
    float animtimer;




};

#endif