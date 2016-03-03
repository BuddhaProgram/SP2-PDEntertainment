/*************************************************************/
/*!
\file       Explorer.h
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Singleton class for all scenes.
*/
/*************************************************************/
#ifndef EXPLORER_H
#define EXPLORER_H
#include "ToolUI.h"
#include "Vector3.h"

/*************************************************************/
/*!
Class Explorer:
\brief
parent class for all variables with singleton
*/
/*************************************************************/
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

	int i_SlotIndex;

	int itemAttack[4];

	// Inventory for player
	ToolUI::ToolType GetToolType(int SlotNumber);
	void InsertToolSlot(ToolUI::ToolType ChooseTools);
	void RemoveToolSlot(ToolUI::ToolType RemoveTools);
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

	bool b_SoundEffect[10];
	bool b_MonsterSound[10];

private:
	Explorer(); // Default constructor
};

#endif
