#include "SoundControllerClass.h"

std::string getPath(char* sName);

SoundControllerClass::SoundControllerClass()
{
	FMOD::System_Create(&system_);
	system_->init(1024, FMOD_INIT_NORMAL, 0);
}

SoundControllerClass::~SoundControllerClass()
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		soundTable_[i].second.second->stop();
	system_->release();
	system_->close();
}

void SoundControllerClass::createSound(char* sName, bool loop)
{
	std::string name(sName);
	std::string path = getPath(sName);
	const char* sPath = path.c_str();
	std::cout << "\tAdding " << name << "..." << std::setw(40 - name.length());

	std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > apair;
	apair.first = std::string(sName);
	apair.second.first = NULL;
	apair.second.second = NULL;
	soundTable_.push_back(apair);
	std::cout << ((system_->createSound(sPath, FMOD_DEFAULT, 0, &soundTable_[soundTable_.size()-1].second.first)
				 == FMOD_OK) ? "OK" : "FAILED") << std::endl;
}

void SoundControllerClass::playSound(char* sName, bool pause)
{
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	system_->playSound(FMOD_CHANNEL_FREE, soundTable_[i].second.first, pause, &soundTable_[i].second.second);
}

void SoundControllerClass::stopSound(char* sName)
{
	int i = lookUp(std::string(sName));
		if (i == -1)
			return;
	soundTable_[i].second.second->stop();
}

void SoundControllerClass::loopSound(char* sName, bool loop)
{
	int i = lookUp(std::string(sName));
		if (i == -1)
			return;
	soundTable_[i].second.first->setMode(sName ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}

void SoundControllerClass::muteAll(bool mute)
{
	FMOD::ChannelGroup *canal;
	system_->getMasterChannelGroup(&canal);
	canal->setMute(mute);
}

unsigned int SoundControllerClass::lookUp(std::string fileName)
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == fileName)
			return i;
	std::cout << "ERROR: " << fileName << " not found !";
	return -1;
}

std::string getPath(char* sName)
{
	std::string soundPath = "media/SFX/" + std::string(sName);
	return soundPath;
}