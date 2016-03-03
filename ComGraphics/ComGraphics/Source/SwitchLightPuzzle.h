/*************************************************************/
/*!
\file       SwitchLightPuzzle.h
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class for SwitchLightPuzzle
*/
/*************************************************************/
#ifndef SWITCHLIGHTPUZZLE_H
#define SWITCHLIGHTPUZZLE_H

/*************************************************************/
/*!
Class SwitchLightPuzzle:
\brief
Class for SwitchLightPuzzle
*/
/*************************************************************/
class SwitchLightPuzzle
{
	public:
		SwitchLightPuzzle();
		~SwitchLightPuzzle();

		bool SwitchPuzzleOne();
		bool SwitchPuzzleTwo();

		bool b_PuzzleOne[3];
		bool b_PuzzleTwo[5];
};

#endif