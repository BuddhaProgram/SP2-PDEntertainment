#include "ToolSection.h"

ToolSection::ToolSection()
{
	SlotOne = ToolUI(ToolUI::Empty);
	SlotTwo = ToolUI(ToolUI::Empty);
	SlotThree = ToolUI(ToolUI::Empty);
	SlotFour = ToolUI(ToolUI::Empty);
	
	TotalTools.push_back(SlotOne);
	TotalTools.push_back(SlotTwo);
	TotalTools.push_back(SlotThree);
	TotalTools.push_back(SlotFour);
}

ToolSection::~ToolSection()
{

}

void ToolSection::InsertToolSlot(ToolUI::ToolType ChooseTools)
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

bool ToolSection::CheckForDoubleTool(ToolUI::ToolType DoubleTool)
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

ToolUI::ToolType ToolSection::GetToolType(int SlotNumber)
{
	switch (SlotNumber)
	{
	case 1:
		return SlotOne.tool;
		break;
	case 2:
		return SlotTwo.tool;
		break;
	case 3:
		return SlotThree.tool;
		break;
	case 4:
		return SlotFour.tool;
		break;
	}
}