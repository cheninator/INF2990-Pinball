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
class ControleurSon
{
public:
	// Pointer to the FMOD instance

	ControleurSon();
	~ControleurSon();
	void creeSon(char* sName, bool loop = false);
	void jouerSon(char* sName, bool pause = false);
	void bouclerSon(char* sName, bool loop = true);
	void arreterSon(char* sName);
	void sourdine(bool mute);

	void ajusterBGM(float percent);
	void ajusterSFX(float percent);
	

private:
	unsigned int lookUp(std::string fileName);
	void setVolumeLimiter();
	void setVolumeBGM();
	void setVolumeSFX();

	FMOD::System* system_;
	std::vector< std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > > soundTable_;
	std::vector<int> backGroundMusic_;
	std::vector<int> specialEffectSounds_;
	float maxBGM_;
	float maxSFX_;
};

#endif //__FACADE_SOUND_CONTROLLER_CLASS_H__