#ifndef __FACADE_SOUND_CONTROLLER_CLASS_H__
#define __FACADE_SOUND_CONTROLLER_CLASS_H__

#include <fmod.h>
#include <fmod.hpp>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

class ControleurSon
{
public:
	// Pointer to the FMOD instance

	ControleurSon( bool desactiverSon );
	~ControleurSon();
	void creeSon(char* sName);
	void jouerSon(char* sName, bool pause = false);
	void accelererSon(char* sName, float facteurAcceleration);
	void bouclerSon(char* sName, bool loop = true);
	void arreterSon(char* sName);
	void sourdine(bool mute);

	void ajusterBGM(float percent);
	void ajusterSFX(float percent);
	

private:
	int lookUp(std::string fileName);
	void setVolumeLimiter();
	void setVolumeBGM();
	void setVolumeSFX();
	std::string getSFXPath(char* sName);

	FMOD::System* system_;
	std::vector< std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > > soundTable_;
	std::vector<int> backGroundMusic_;
	std::vector<int> specialEffectSounds_;
	float maxBGM_;
	float maxSFX_;

	bool sonDesactive;
};

#endif //__FACADE_SOUND_CONTROLLER_CLASS_H__