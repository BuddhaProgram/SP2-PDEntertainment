#include "Music.h"

Music::Music()
{

}

Music::~Music()
{
	engine->drop();
	engine = 0;
}

void Music::init()
{
	engine = irrklang::createIrrKlangDevice();
	BackgroundMusic = MusicReadFromText("MusicFile.txt");

	int i = 0;
	for (std::vector<std::string>::iterator it = BackgroundMusic.begin(); it != BackgroundMusic.end(); ++it)
	{
		BackGround.push_back(engine->addSoundSourceFromFile((*it).c_str()));
		BackGround[i]->setDefaultVolume(1.0f);

		++i;
	}

}

void Music::OpeningMusic(int index, bool loop)
{
	engine->play2D(BackGround[index], loop);
}

void Music::DropMusic()
{
	int i = 0;
	for (std::vector<std::string>::iterator it = BackgroundMusic.begin(); it != BackgroundMusic.end(); ++it)
	{
		engine->drop();
	}
}

std::vector<std::string> Music::MusicReadFromText(std::string link)
{
	std::ifstream inData;
	inData.open(link, std::ifstream::in);
	std::vector<std::string> musicName;

	if (!inData)
	{
		std::cout << "Error Opening" << link << std::endl;
		exit(1);
	}

	if (inData.good())
	{
		while (inData.good())
		{
			std::string data;
			std::getline(inData, data);
			musicName.push_back(data);
		}
	}

	inData.close();
	return musicName;
}