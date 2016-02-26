#include "GlobalVariables.h"

GlobalVariables::GlobalVariables()
{
	RotateX = 0.0f;
	f_Worldspin = 0.0f;

	b_LockSwing = false;
	b_LockSwingDebounce = false;
	start_Animation = false;
	
	i_SlotIndex = 1;
    f_SwitchDebounce = 0.0f;

	f_SwitchRotateOne = 0.0f;
	f_SwitchRotateTwo = 0.0f;
	f_SwitchRotateThree = 0.0f;

	for (int i = 0; i < 5; ++i)
	{
		b_SwitchAnimate[i] = false;
	}
}

GlobalVariables::~GlobalVariables()
{

}