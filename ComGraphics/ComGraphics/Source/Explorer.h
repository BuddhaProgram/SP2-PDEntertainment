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
	virtual float getStamina();

	float stamina;
	float hp;
	float f_hpBarScaleX;


	ToolUI::ToolType GetToolType(int SlotNumber);
	void InsertToolSlot(ToolUI::ToolType ChooseTools);
	bool CheckForDoubleTool(ToolUI::ToolType DoubleTool);

	std::list<ToolUI> TotalTools;

	void ExplorerSavePoint(Vector3 pos);
	Vector3 SavePoint;

private:
	Explorer();
};

#endif
