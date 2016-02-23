#include "ToolUI.h"

ToolUI::ToolUI()
{
	tool = Empty;
	ID = 0;
}

ToolUI::ToolUI(ToolType tool)
{
	this->tool = tool;
}

ToolUI::~ToolUI()
{
	
}