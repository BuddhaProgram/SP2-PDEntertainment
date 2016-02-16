#ifndef PLAYERSTAT_H
#define PLAYERSTAT_H

class PlayerStat
{
public:
	static PlayerStat* instance(){static PlayerStat data; return &data; }

	virtual void setHP(float currHP);
	virtual void setStamina(float currStam);
	virtual float getHP();
	virtual float getStamina();
	float stamina;
	float hp;
private:
	PlayerStat();
};

#endif