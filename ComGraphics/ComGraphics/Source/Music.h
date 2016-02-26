#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include <string>
#include "../irrKlang/include/irrKlang.h"

class Music
{
	public:
		Music();
		~Music();

		void init();
		void OpeningMusic();

		irrklang::ISoundEngine *engine;
		irrklang::ISoundSource *BackGround;
		std::vector<std::string> BackgroundMusic;
};

#endif