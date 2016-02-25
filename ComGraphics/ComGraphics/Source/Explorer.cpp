#include "Explorer.h"

Explorer::Explorer()
{
	Explorer::instance()->hp = 100;
	Explorer::instance()->stamina = 100;

	Explorer::instance()->f_hpBarScaleX = 10.f;

	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->itemAttack[i] = 0;
	}

	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->TotalTools.push_back(ToolUI(ToolUI::Empty));
	}

	Explorer::instance()->SavePoint = (0.f, 0.f, 0.f);
}

float Explorer::getHP()
{
	return Explorer::instance()->hp;
}

float Explorer::getStamina()
{
	return Explorer::instance()->stamina;
}

void Explorer::setHP(float HP)
{
	Explorer::instance()->hp = HP;
}

void Explorer::setStamina(float Stam)
{
	Explorer::instance()->stamina = Stam;
}

void Explorer::InsertToolSlot(ToolUI::ToolType ChooseTools)
{
	if (CheckForDoubleTool(ChooseTools) == false)
	{
		for (std::list<ToolUI>::iterator TS = TotalTools.begin(); TS != TotalTools.end(); ++TS)
		{
			if (TS->tool == ToolUI::Empty)
			{
				TS->tool = ChooseTools;
				break;
			}
		}
	}
}

bool Explorer::CheckForDoubleTool(ToolUI::ToolType DoubleTool)
{
	for (std::list<ToolUI>::iterator TS = TotalTools.begin(); TS != TotalTools.end(); ++TS)
	{
		if (TS->tool == DoubleTool)
		{
			return true;
		}
	}

	return false;
}

ToolUI::ToolType Explorer::GetToolType(int SlotNumber)
{
	std::list<ToolUI>::iterator it = TotalTools.begin();
	switch (SlotNumber)
	{
	case 1:
		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		return it->tool;
		break;
	case 2:
		std::advance(it, 1);
		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		return it->tool;
		break;
	case 3:
		std::advance(it, 2);
		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		return it->tool;
		break;
	case 4:
		std::advance(it, 3);
		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		return it->tool;
		break;
	default:
		return it->tool;
	}
}

//combat stuff

void Explorer::ExplorerSavePoint(Vector3 pos)
{
	SavePoint = pos;
}