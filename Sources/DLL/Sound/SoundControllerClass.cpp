#include "SoundControllerClass.h"

std::string getPath(char* sName);

SoundControllerClass::SoundControllerClass()
{
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		// Report Error
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		return;
	}

	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
}

void SoundControllerClass::createSound(char* sName)
{
	std::string pName = getPath(sName);
	const char* pSound = pName.c_str();
	sounds_[pSound];
	m_pSystem->createSound(pSound, FMOD_HARDWARE, 0, sounds_[pSound]);
}

void SoundControllerClass::playSound(char* sName, bool bLoop)
{
	std::string pName = getPath(sName);
	const char* pSound = pName.c_str();
	SoundClass mySound = *(sounds_[pSound]);
	if (!bLoop)
		mySound->setMode(FMOD_LOOP_OFF);
	else
	{
		mySound->setMode(FMOD_LOOP_NORMAL);
		mySound->setLoopCount(-1);
	}
	// Je me fais troll par intellisense
	m_pSystem->playSound(FMOD_CHANNEL_FREE, mySound, false, 0);
}

void SoundControllerClass::releaseSound(char* sName) 
{
	std::string pName = getPath(sName);
	const char* pSound = pName.c_str();
	SoundClass mySound = *(sounds_[pSound]);
	mySound->release();
}

std::string getPath(char* sName)
{
	std::string soundPath = "media/SFX/" + std::string(sName);
	return soundPath;
}