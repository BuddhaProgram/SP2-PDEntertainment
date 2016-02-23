#ifndef TOOLSECTION_H
#define TOOLSECTION_H

#include "ToolUI.h"
#include <list>

class ToolSection
{
	public:
		ToolSection();
		~ToolSection();

		ToolUI::ToolType GetToolType(int SlotNumber);
		void InsertToolSlot(ToolUI::ToolType ChooseTools);
		bool CheckForDoubleTool(ToolUI::ToolType DoubleTool);

		std::list<ToolUI> TotalTools;

};

#endif