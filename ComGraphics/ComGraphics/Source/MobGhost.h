/*************************************************************/
/*!
\file       MobGhost.h
\author     Shem Ang Yi Ruey
\par        email: shem0710@gmail.com
\brief
Class for "ghost" type enemy
*/
/*************************************************************/
#ifndef MOBGHOST_H
#define MOBGHOST_H

#include "HostileMob.h"
/*************************************************************/
/*!
Class HostileMob:
\brief
Class for "ghost" type enemy
*/
/*************************************************************/
class MobGhost : public HostileMob
{
public:
    MobGhost();
    ~MobGhost();

    void setSpawnGhost(float xpos, float zpos);
    void move(double dt, int movespeed);
    void knockback();
    void TakeDamage(int damage);
    void checkAttack();
    bool proximitycheck(float smallx, float largex, float smallz, float largez);
    void attack(float Damage);

    bool canHit;

    float mobTimeCount2;
private:
    bool kenaWhack;


    

};

#endif