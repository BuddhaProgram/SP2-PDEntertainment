#include "SwitchLightPuzzle.h"

SwitchLightPuzzle::SwitchLightPuzzle()
{
	b_PuzzleOneSwitchOne = false;
	b_PuzzleOneSwitchTwo = false;
	b_PuzzleOneSwitchThree = false;
	b_PuzzleOneOpen = false;
}

SwitchLightPuzzle::~SwitchLightPuzzle()
{

}

void SwitchLightPuzzle::SwitchPuzzleOne(bool One, bool Two, bool Three)
{
	if (One == true && Two == true == Three == true)
	{
		b_PuzzleOneOpen = true;
	}

	else
		b_PuzzleOneOpen = false;
}

bool SwitchLightPuzzle::PuzzleOne(bool solvedOne)
{
	if (solvedOne == true)
		return true;

	else
		return false;
}