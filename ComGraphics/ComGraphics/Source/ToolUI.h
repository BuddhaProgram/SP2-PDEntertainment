#ifndef TOOLUI_H
#define TOOLUI_H

#include <vector>
#include <list>

class ToolUI
{
	public:
		enum ToolType
		{
			Pickaxe,
			BaseballBat,
			Empty,
			Max_ToolType,
		};

		int ID;
		ToolUI();
		ToolUI(ToolType tool);
		~ToolUI();

		ToolType tool;
};
#endif