#include "PlayerStat.h"

PlayerStat::PlayerStat()
{
	hp = 100;
	PlayerStat::instance()->stamina = 100;
}

float PlayerStat::getHP()
{
	return hp;
}

float PlayerStat::getStamina()
{
	return PlayerStat::instance()->stamina;
}

void PlayerStat::setHP(float HP)
{
	hp = HP;
}

void PlayerStat::setStamina(float Stam)
{
	PlayerStat::instance()->stamina = Stam;
}