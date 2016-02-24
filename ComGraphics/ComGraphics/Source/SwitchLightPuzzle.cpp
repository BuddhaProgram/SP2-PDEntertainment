#include "SwitchLightPuzzle.h"

SwitchLightPuzzle::SwitchLightPuzzle()
{
	for (int i = 0; i < 3; ++i)
	{
		b_PuzzleOne[i] = false;
	}

	for (int i = 0; i < 5; ++i)
	{
		b_PuzzleTwo[i] = false;
	}
}

SwitchLightPuzzle::~SwitchLightPuzzle()
{

}

bool SwitchLightPuzzle::SwitchPuzzleOne()
{
	for (int i = 0; i < 3; ++i)
	{
		if (b_PuzzleOne[i] == false)
		{
			return false;
			break;
		}
	}

	return true;
}

bool SwitchLightPuzzle::SwitchPuzzleTwo()
{
	for (int i = 0; i < 5; ++i)
	{
		if (b_PuzzleTwo[i] == false)
		{
			return false;
			break;
		}
	}

	return true;
}