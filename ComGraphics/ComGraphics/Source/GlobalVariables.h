/*************************************************************/
/*!
\file       GlobalVariables.h
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class created for all scenes to share variables.
*/
/*************************************************************/
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

/*************************************************************/
/*!
Class Explorer:
\brief
parent class for all variables in GlobalVariables
*/
/*************************************************************/
class GlobalVariables
{
	public:
		GlobalVariables();
		~GlobalVariables();


		float RotateX;
		float f_Worldspin;

		bool b_LockSwing = false;
		bool b_LockSwingDebounce = false;
		bool start_Animation = false;


        float f_SwitchDebounce;

		float f_SwitchRotateOne;
		float f_SwitchRotateTwo;
		float f_SwitchRotateThree;
		float f_SwitchRotateFour;
		float f_SwitchRotateFive;

		bool b_SwitchAnimate[5];

		float f_redScreenTimer;

		float f_rotatingTool;

		float f_SuitcaseRotateY;
		float f_savePointRotateY;
};

#endif