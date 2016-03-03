#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../irrKlang/include/irrKlang.h"

class Music
{
	public:
		Music();
		~Music();

		void init();
		void OpeningMusic(int index, bool loop);
		void DropMusic();
		std::vector<std::string>MusicReadFromText(std::string link);

		irrklang::ISoundEngine *engine;
		std::vector<irrklang::ISoundSource*> BackGround;
		std::vector<std::string> BackgroundMusic;
};

#endif