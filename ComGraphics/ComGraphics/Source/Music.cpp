/*************************************************************/
/*!
\file       Music.cpp
\author     Ng Jun Guo
\par        email: ng_junguo901@hotmail.com
\brief
Class created for Music.h
*/
/*************************************************************/
#include "Music.h"

/*************************************************************/
/*!
\brief
Default constructor for class Music
*/
/*************************************************************/
Music::Music()
{

}

/*************************************************************/
/*!
\brief
Default destructor for class Music
*/
/*************************************************************/
Music::~Music()
{
	engine->drop();
	engine = 0;
}

/*************************************************************/
/*!
\brief
Declaration of variables
*/
/*************************************************************/
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

/*************************************************************/
/*!
\brief
Used to play music from sound source
\param int index, bool loop
int index is used to determine which music slot to play
bool loop is used to determine if the music will loop
*/
/*************************************************************/
void Music::OpeningMusic(int index, bool loop)
{
	engine->play2D(BackGround[index], loop);
}

/*************************************************************/
/*!
\brief
Using a text file to store the string of the music name, and use
it to play it through a string vector
\param std::string link
std::string link is the file name in the solution folder
\return musicName
Texts inside the textfile will be converted to a string vector
and will be put into musicName, and returns it
*/
/*************************************************************/
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