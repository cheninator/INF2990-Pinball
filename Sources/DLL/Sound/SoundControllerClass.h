#ifndef __FACADE_SOUND_CONTROLLER_CLASS_H__
#define __FACADE_SOUND_CONTROLLER_CLASS_H__

#include "fmod.h"
#include "fmod.hpp"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
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
	~SoundControllerClass();
	void createSound(char* sName, bool loop = false);
	void playSound(char* sName, bool pause = false);
	void loopSound(char* sName, bool loop = true);
	void stopSound(char* sName);
	void muteAll(bool mute);

	unsigned int lookUp(std::string fileName);

private:
	FMOD::System* system_;
	std::vector< std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > > soundTable_;

};

#endif //__FACADE_SOUND_CONTROLLER_CLASS_H__