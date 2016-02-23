#ifndef EXPLORER_H
#define EXPLORER_H
#include "ToolUI.h"

class Explorer
{
public:
	static Explorer* instance(){static Explorer data; return &data; }

	virtual void setHP(float currHP);
	virtual void setStamina(float currStam);
	virtual float getHP();
	virtual float getStamina();
    virtual void takeDamage(float damage);
	float stamina;
	float hp;

	float f_hpBarScaleX;
	float f_hpBarTranslateX;
	float f_staminaBar;

	ToolUI::ToolType GetToolType(int SlotNumber);
	void InsertToolSlot(ToolUI::ToolType ChooseTools);
	bool CheckForDoubleTool(ToolUI::ToolType DoubleTool);

	std::list<ToolUI> TotalTools;

private:
	Explorer();
};

#endif