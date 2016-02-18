#ifndef SWITCHLIGHTPUZZLE_H
#define SWITCHLIGHTPUZZLE_H

class SwitchLightPuzzle
{
	public:
		SwitchLightPuzzle();
		~SwitchLightPuzzle();

		void SwitchPuzzleOne(bool One, bool Two, bool Three);
		bool PuzzleOne(bool solvedOne);

		bool b_PuzzleOneSwitchOne;
		bool b_PuzzleOneSwitchTwo;
		bool b_PuzzleOneSwitchThree;
		bool b_PuzzleOneOpen;
};

#endif