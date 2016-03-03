#include "Explorer.h"

Explorer::Explorer()
{
	Explorer::instance()->hp = 100;
	Explorer::instance()->stamina = 100;

	Explorer::instance()->f_hpBarScaleX = 10.f;

	Explorer::instance()->i_SlotIndex = 1;

	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->itemAttack[i] = 0;
		Explorer::instance()->TotalTools.push_back(ToolUI(ToolUI::Empty));
	}

	Explorer::instance()->SavePoint = (0.f, 0.f, 0.f);

	Explorer::instance()->PlayerLife = 3;
	Explorer::instance()->isDead = false;
	
	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->b_PickUpTool[i] = false;
	}

	for (std::list<ToolUI>::iterator TS = TotalTools.begin(); TS != TotalTools.end(); ++TS)
	{
		if (TS->tool == ToolUI::Empty)
		{
			TS->tool = ToolUI::Hand;
			break;
		}
	}

	i_SuitcaseCount = 0;
	for (int i = 0; i < 5; ++i)
	{
		b_pickUpSuitCase[i] = false;
	}

	Explorer::instance()->f_FlickeringLight = 0.0f;

	for (int i = 0; i < 10; ++i)
	{
		b_SoundEffect[i] = false;
	}
}

float Explorer::getHP()
{
	return Explorer::instance()->hp;
}

float Explorer::MinusHP(float TakeDamage)
{
	Explorer::instance()->hp -= TakeDamage;
	
	if (Explorer::instance()->hp <= 0)
	{
		Explorer::instance()->hp = 0;
	}
	
	return Explorer::instance()->hp;
}

void Explorer::checkDead()
{
	if (Explorer::instance()->hp <= 0)
	{
		Explorer::instance()->isDead = true;
	}
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
		if (it->tool == ToolUI::Hand)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 8;

		else if (it->tool == ToolUI::Empty)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 0;

		return it->tool;
		break;
	case 2:
		std::advance(it, 1);
		if (it->tool == ToolUI::Hand)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 8;

		else if (it->tool == ToolUI::Empty)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 0;

		return it->tool;
		break;
	case 3:
		std::advance(it, 2);
		if (it->tool == ToolUI::Hand)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 8;

		else if (it->tool == ToolUI::Empty)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 0;

		return it->tool;
		break;
	case 4:
		std::advance(it, 3);
		if (it->tool == ToolUI::Hand)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 1;

		if (it->tool == ToolUI::Pickaxe)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 2;

		else if (it->tool == ToolUI::BaseballBat)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 4;

		else if (it->tool == ToolUI::Sword)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 8;

		else if (it->tool == ToolUI::Empty)
			Explorer::instance()->itemAttack[SlotNumber - 1] = 0;

		return it->tool;
		break;
	default:
		return it->tool;
	}
}

//combat stuff

