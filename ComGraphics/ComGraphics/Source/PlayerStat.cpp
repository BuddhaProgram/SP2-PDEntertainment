#include "PlayerStat.h"

PlayerStat::PlayerStat()
{
	PlayerStat::instance()->hp = 5;
	PlayerStat::instance()->stamina = 100;
}

float PlayerStat::getHP()
{
	return PlayerStat::instance()->hp;
}

float PlayerStat::getStamina()
{
	return PlayerStat::instance()->stamina;
}

void PlayerStat::setHP(float HP)
{
	PlayerStat::instance()->hp = HP;
}

void PlayerStat::setStamina(float Stam)
{
	PlayerStat::instance()->stamina = Stam;
}