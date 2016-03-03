#ifndef EXPLORER_H
#define EXPLORER_H
#include "ToolUI.h"
#include "Vector3.h"


class Explorer
{
public:
	static Explorer* instance(){static Explorer data; return &data; }

	virtual void setHP(float currHP);
	virtual void setStamina(float currStam);
	virtual float getHP();
	virtual float MinusHP(float TakeDamage);
	virtual float getStamina();

	float stamina;
	float hp;
	float f_hpBarScaleX;

	int i_SlotIndex;

	int itemAttack[4];
	ToolUI::ToolType GetToolType(int SlotNumber);
	void InsertToolSlot(ToolUI::ToolType ChooseTools);
	bool CheckForDoubleTool(ToolUI::ToolType DoubleTool);

	std::list<ToolUI> TotalTools;
	bool b_PickUpTool[3];

	int i_SuitcaseCount;
	bool b_pickUpSuitCase[5];

	unsigned int PlayerLife;
	bool isDead;

	void checkDead();
	Vector3 SavePoint;

	float f_FlickeringLight;

	bool b_ActivateMusic[10];

private:
	Explorer();
};

#endif
