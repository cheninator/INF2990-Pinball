#include "SoundControllerClass.h"

std::string getPath(char* sName);

SoundControllerClass::SoundControllerClass()
{
	FMOD_System_Create(&system_);
	FMOD_System_Init(system_, 1024, FMOD_INIT_NORMAL, NULL);
}

SoundControllerClass::~SoundControllerClass()
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		FMOD_Sound_Release(soundTable_[i].second);
	FMOD_System_Close(system_);
	FMOD_System_Release(system_);
}

void SoundControllerClass::createSound(char* sName, bool loop)
{
	std::string path = getPath(sName);
	const char* sPath = path.c_str();
	std::cout << " Adding " << std::string(sName) << "...   ";

	std::pair<std::string, FMOD_SOUND *> apair;
	apair.first = std::string(sName);
	apair.second = NULL;
	soundTable_.push_back(apair);

	FMOD_RESULT resultat;
	resultat = FMOD_System_CreateSound(system_, "C:\ambiant.wav", FMOD_LOOP_NORMAL, 0, &soundTable_.back().second);
	std::cout << resultat << std::endl;
}

void SoundControllerClass::playSound(char* sName, bool stop)
{
	unsigned int position = lookUp(std::string(sName));
	position = lookUp("ambiant.wav");
	FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, soundTable_[position].second, stop, NULL);
}

void SoundControllerClass::loopSound(char* sName, int loop)
{
	unsigned int position = lookUp(std::string(sName));
	FMOD_Sound_SetLoopCount(soundTable_[position].second, loop);
}

void SoundControllerClass::stopSound(char* sName) 
{
}

void SoundControllerClass::muteAll(bool mute)
{
	FMOD_CHANNELGROUP *canal;
	FMOD_System_GetMasterChannelGroup(system_, &canal);
	FMOD_ChannelGroup_SetMute(canal, mute);
}

unsigned int SoundControllerClass::lookUp(std::string fileName)
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == fileName)
			return i;
	return -1;
}

std::string getPath(char* sName)
{
	std::string soundPath = "media/SFX/" + std::string(sName);
	return soundPath;
}