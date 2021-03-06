/*************************************************************/
/*!
\file       GlobalVariables.cpp
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Singleton class definition for class GlobalVariables.h
*/
/*************************************************************/
#include "GlobalVariables.h"

/*************************************************************/
/*!
\brief
Default constructor for class GlobalVariables.h
*/
/*************************************************************/
GlobalVariables::GlobalVariables()
{
	RotateX = 0.0f;
	f_Worldspin = 0.0f;

	b_LockSwing = false;
	b_LockSwingDebounce = false;
	start_Animation = false;
	
    f_SwitchDebounce = 0.0f;

	f_SwitchRotateOne = 0.0f;
	f_SwitchRotateTwo = 0.0f;
	f_SwitchRotateThree = 0.0f;
	f_SwitchRotateFour = 0.0f;
	f_SwitchRotateFive = 0.0f;

	for (int i = 0; i < 5; ++i)
	{
		b_SwitchAnimate[i] = false;
	}

	f_redScreenTimer = 0.0f;

	f_SuitcaseRotateY = 0.0f;
}

/*************************************************************/
/*!
\brief
Default destructor for class GlobalVariables.h
*/
/*************************************************************/
GlobalVariables::~GlobalVariables()
{

}