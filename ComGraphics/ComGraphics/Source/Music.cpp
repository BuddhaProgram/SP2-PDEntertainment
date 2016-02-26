#include "Music.h"

Music::Music()
{
	engine = irrklang::createIrrKlangDevice();
	BackgroundMusic = {"Music//MainMenu.mp3", ""};
}

Music::~Music()
{
	engine->drop();
}

void Music::init()
{
	BackGround = engine->addSoundSourceFromFile(BackgroundMusic[0].c_str());
	BackGround->setDefaultVolume(1.0f);
}

void Music::OpeningMusic()
{
	engine->play2D(BackGround, true);
}