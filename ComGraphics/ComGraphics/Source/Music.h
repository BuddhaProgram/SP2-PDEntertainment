/*************************************************************/
/*!
\file       Music.h
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class created for Music
*/
/*************************************************************/
#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../irrKlang/include/irrKlang.h"

/*************************************************************/
/*!
Class Music:
\brief
parent class for Music
*/
/*************************************************************/
class Music
{
	public:
		Music();
		~Music();

		void init();
		void OpeningMusic(int index, bool loop);
		std::vector<std::string>MusicReadFromText(std::string link);

		irrklang::ISoundEngine *engine;
		std::vector<irrklang::ISoundSource*> BackGround;
		std::vector<std::string> BackgroundMusic;
};

#endif