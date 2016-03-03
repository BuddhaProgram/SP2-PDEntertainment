/*************************************************************/
/*!
\file       ToolUI.cpp
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class definition for ToolUI.cpp
*/
/*************************************************************/
#include "ToolUI.h"

/*************************************************************/
/*!
\brief
Default constructor for class ToolUI
*/
/*************************************************************/
ToolUI::ToolUI()
{
	tool = Empty;
}

/*************************************************************/
/*!
\brief
Overloaded constructor for class ToolUI
*/
/*************************************************************/
ToolUI::ToolUI(ToolType tool)
{
	this->tool = tool;
}

/*************************************************************/
/*!
\brief
Default destructor for class ToolUI
*/
/*************************************************************/
ToolUI::~ToolUI()
{
	
}
