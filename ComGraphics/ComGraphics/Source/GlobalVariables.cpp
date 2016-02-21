#include "GlobalVariables.h"

GlobalVariables::GlobalVariables()
{
	RotateX = 0.0f;
	b_LockSwing = false;
	b_LockSwingDebounce = false;
	start_Animation = false;

	i_SlotIndex = 1;
	i_numScene = 0;
}

GlobalVariables::~GlobalVariables()
{

}