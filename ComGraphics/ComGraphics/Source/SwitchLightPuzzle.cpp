/*************************************************************/
/*!
\file       SwitchLightPuzzle.cpp
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class definition for class SwitchLightPuzzle.h
*/
/*************************************************************/
#include "SwitchLightPuzzle.h"

/*************************************************************/
/*!
\brief
Default constructor for class SwitchLightPuzzle.h
*/
/*************************************************************/
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

/*************************************************************/
/*!
\brief
Default destructor for class SwitchLightPuzzle.h
*/
/*************************************************************/
SwitchLightPuzzle::~SwitchLightPuzzle()
{

}

/*************************************************************/
/*!
\brief
Returns a true or false depending on the bool array

\return
Returns true if b_PuzzleOne array are all true
Returns false if one of b_PuzzleOne size in the array is false
/*************************************************************/
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

/*************************************************************/
/*!
\brief
Returns a true or false depending on the bool array

\return
Returns true if b_PuzzleTwo array are all true
Returns false if one of b_PuzzleTwo size in the array is false
/*************************************************************/
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