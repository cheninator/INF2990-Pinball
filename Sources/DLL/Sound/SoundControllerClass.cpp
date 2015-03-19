#include "SoundControllerClass.h"

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

void SoundControllerClass::createSound(char* pFile)
{
	std::string soundPath = "media/SFX/" + std::string(pFile);
	const char* pSound = soundPath.c_str();
	sounds_[pSound];
	m_pSystem->createSound(pSound, FMOD_HARDWARE, 0, sounds_[pSound]);
}

void SoundControllerClass::playSound(SoundClass pSound, bool bLoop)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}
	// Je me fais troll par intellisense
	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, 0);
}

void SoundControllerClass::releaseSound(SoundClass pSound) {
	pSound->release();
}