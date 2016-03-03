/*************************************************************/
/*!
\file       ToolUI.h
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class for Tools
*/
/*************************************************************/
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