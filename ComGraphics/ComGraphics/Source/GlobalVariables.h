#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H


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

		int i_SlotIndex;
        float f_SwitchDebounce;

		float f_SwitchRotateOne;
		float f_SwitchRotateTwo;
		float f_SwitchRotateThree;

		bool b_SwitchAnimate[5];
};

#endif