#include "ItemStat.h"

ToolSection::ToolSection()
{
	for (int i = 0; i < 4; ++i)
	{
		TotalTools.push_back(ToolUI(ToolUI::Empty));
	}
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
	std::list<ToolUI>::iterator it = TotalTools.begin();
	switch (SlotNumber)
	{
	case 1:
		return it->tool;
		break;
	case 2:
		std::advance(it, 1);
		return it->tool;
		break;
	case 3:
		std::advance(it, 2);
		return it->tool;
		break;
	case 4:
		std::advance(it, 3);
		return it->tool;
		break;
	}
}