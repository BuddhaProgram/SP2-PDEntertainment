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

	int itemAttack[4];
	ToolUI::ToolType GetToolType(int SlotNumber);
	void InsertToolSlot(ToolUI::ToolType ChooseTools);
	bool CheckForDoubleTool(ToolUI::ToolType DoubleTool);

	std::list<ToolUI> TotalTools;

	unsigned int PlayerLife;
	bool isDead;
	bool checkSavePoint[4];

	void checkDead();
	void ExplorerSavePoint(Vector3 pos);
	Vector3 SavePoint;

private:
	Explorer();
};

#endif
