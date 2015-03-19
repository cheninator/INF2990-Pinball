#ifndef __FACADE_SOUND_CONTROLLER_CLASS_H__
#define __FACADE_SOUND_CONTROLLER_CLASS_H__

#include <fmod.h>
#include <fmod.hpp>
#include <stdlib.h>
#include <vector>

// MERCI
// http://openclassrooms.com/courses/apprenez-a-programmer-en-c/jouer-du-son-avec-fmod
// https://cuboidzone.wordpress.com/2013/07/26/tutorial-implementing-fmod/
// MUCH LOVE
typedef FMOD::Sound* SoundClass;
class SoundControllerClass
{
public:
	// Pointer to the FMOD instance

	SoundControllerClass();
	void createSound(char* pFile);
	void playSound(SoundClass pSound, bool bLoop = false);
	void releaseSound(SoundClass pSound);

private:
	FMOD::System* m_pSystem;
	std::vector<std::pair<SoundClass*, char*>> sounds_;
};

#endif //__FACADE_SOUND_CONTROLLER_CLASS_H__