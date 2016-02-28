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
			Sword,
			Hand,
			Empty,
			Max_ToolType,
		};

		ToolUI();
		ToolUI(ToolType tool);
		~ToolUI();

		ToolType tool;
};
#endif