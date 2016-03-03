/*************************************************************/
/*!
\file       Explorer.cpp
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Singleton class definition for class Explorer.h
*/
/*************************************************************/
#include "Explorer.h"

/*************************************************************/
/*!
\brief
Default constructor for class Explorer.h
*/
/*************************************************************/
Explorer::Explorer()
{
	// Health and Stamina
	Explorer::instance()->hp = 100;
	Explorer::instance()->stamina = 100;

	// Used to count the mouse scroll
	Explorer::instance()->i_SlotIndex = 1;

	// Setting inventory slots and item attack value to NIL.
	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->itemAttack[i] = 0;
		Explorer::instance()->TotalTools.push_back(ToolUI(ToolUI::Empty));
	}

	for (std::list<ToolUI>::iterator TS = TotalTools.begin(); TS != TotalTools.end(); ++TS)
	{
		if (TS->tool == ToolUI::Empty)
		{
			TS->tool = ToolUI::Hand;
			break;
		}
	}

	// An extra point in case player has 3 lives and wish to continue the game.
	Explorer::instance()->SavePoint = (0.f, 0.f, 0.f);

	// A player has 3 lives per game.
	Explorer::instance()->PlayerLife = 3;
	Explorer::instance()->isDead = false;
	
	// Bool to see if item has been picked up.
	for (int i = 0; i < 4; ++i)
	{
		Explorer::instance()->b_PickUpTool[i] = false;
	}

	// Bool to see if suitcase has been picked up.
	i_SuitcaseCount = 0;
	for (int i = 0; i < 5; ++i)
	{
		b_pickUpSuitCase[i] = false;
	}

	// Flickering light timer for light flickering
	Explorer::instance()->f_FlickeringLight = 0.0f;

	// Bool to lock sound effects and monster sound
	for (int i = 0; i < 10; ++i)
	{
		Explorer::instance()->b_SoundEffect[i] = false;
		Explorer::instance()->b_MonsterSound[i] = false;
	}
}

/*************************************************************/
/*!
\brief
Gets the variable HP.

\return hp
Returns the value of the variable hp inside the singleton class
/*************************************************************/
float Explorer::getHP()
{
	return Explorer::instance()->hp;
}

/*************************************************************/
/*!
\brief
Gets the variable HP.

\param float TakeDamage
Takes in the param and is used to minus the hp of the player

\return hp
Returns the value of the variable hp inside the singleton class
after hp is deducted by param TakeDamage
/*************************************************************/
float Explorer::MinusHP(float TakeDamage)
{
	Explorer::instance()->hp -= TakeDamage;
	
	if (Explorer::instance()->hp <= 0)
	{
		Explorer::instance()->hp = 0;
	}
	
	return Explorer::instance()->hp;
}

/*************************************************************/
/*!
\brief
Checks if the player is dead.
/*************************************************************/
void Explorer::checkDead()
{
	if (Explorer::instance()->hp <= 0)
	{
		Explorer::instance()->isDead = true;
	}
}

/*************************************************************/
/*!
\brief
Gets the player's Stamina

\return stamina
Returns the value of the variable stamina inside the singleton class
/*************************************************************/
float Explorer::getStamina()
{
	return Explorer::instance()->stamina;
}

/*************************************************************/
/*!
\brief
Setting player's HP

\param float HP
HP is used to set the value of player's hp
/*************************************************************/
void Explorer::setHP(float HP)
{
	Explorer::instance()->hp = HP;
}

/*************************************************************/
/*!
\brief
Setting player's HP

\param float Stam
Stam is used to set the value of player's stamina
/*************************************************************/
void Explorer::setStamina(float Stam)
{
	Explorer::instance()->stamina = Stam;
}

/*************************************************************/
/*!
\brief
Inserting the tools into the inventory slot

\param ToolUI::ToolType ChooseTools
ChooseTools from the enum inside class ToolUI is used and
will be slotted inside if there is no item present in the inventory
/*************************************************************/
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

/*************************************************************/
/*!
\brief
Removing the tools in the inventory

\param ToolUI::ToolType RemoveTool
RemoveTool from the enum inside class ToolUI is used and
will be removed inside the inventory
/*************************************************************/
void Explorer::RemoveToolSlot(ToolUI::ToolType RemoveTool)
{
	for (std::list<ToolUI>::iterator TS = TotalTools.begin(); TS != TotalTools.end(); ++TS)
	{
		if (TS->tool != ToolUI::Hand)
		{
			TS->tool = RemoveTool;
		}
	}
}

/*************************************************************/
/*!
\brief
Checks for double tool

\param ToolUI::ToolType DoubleTool
DoubleTool from the enum inside class ToolUI is used and
will be used to check if tool is already present in the
inventory.

\return
returns true if tool is already present inside the inventory
Returns false if tool is not present inside the inventory
/*************************************************************/
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

/*************************************************************/
/*!
\brief
Checks which slot is the tool is in and points to it.

\param int SlotNumber
SlotNumber is used to determine which number is it and points
to the inventory slot.

\return
returns the pointer of tool type inside class ToolUI. Also returns
the value of the item attack value.
/*************************************************************/
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

