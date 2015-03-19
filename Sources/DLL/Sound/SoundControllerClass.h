#ifndef __FACADE_SOUND_CONTROLLER_CLASS_H__
#define __FACADE_SOUND_CONTROLLER_CLASS_H__

#include <fmod.h>
#include <fmod.hpp>
#include <stdlib.h>
#include <vector>
#include <map>

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
	void createSound(char* sName);
	void playSound(char* sName, bool bLoop = false);
	void releaseSound(char* sName);

private:
	FMOD::System* m_pSystem;
	std::map<const char*, SoundClass*> sounds_;
};

#endif //__FACADE_SOUND_CONTROLLER_CLASS_H__