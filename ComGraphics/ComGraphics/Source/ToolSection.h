#ifndef TOOLSECTION_H
#define TOOLSECTION_H

#include "ToolUI.h"
#include <list>

class ToolSection
{
	public:
		ToolSection();
		~ToolSection();

		void InsertToolSlot(ToolUI::ToolType ChooseTools);
		ToolUI::ToolType GetToolType(int SlotNumber);
		bool CheckForDoubleTool(ToolUI::ToolType DoubleTool);

		std::list<ToolUI> TotalTools;
};

#endif