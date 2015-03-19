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
	std::pair<SoundClass*, char*> pSound;
	sounds_.push_back(pSound);
	m_pSystem->createSound(sounds_[sounds_.size() - 1].second, FMOD_HARDWARE, 0, sounds_[sounds_.size()-1].first);
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