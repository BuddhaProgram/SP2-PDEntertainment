#ifndef SWITCHLIGHTPUZZLE_H
#define SWITCHLIGHTPUZZLE_H

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