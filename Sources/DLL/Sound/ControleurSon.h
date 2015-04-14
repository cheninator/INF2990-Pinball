//////////////////////////////////////////////////////////////////////////////
/// @file ControleurSon.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Sons
///
//////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////
/// @class ControleurSon
/// @brief Structure de donnee qui contient des sons. Offre des interfaces utiles.
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class ControleurSon
{
public:
	/// Constructeur
	ControleurSon( bool desactiverSon );

	/// Destructeur
	~ControleurSon();

	/// Creation de sons
	void creeSon(char* sName);

	/// Joue un son
	void jouerSon(char* sName, bool pause = false);

	/// Accelere la vitesse du play d'un son
	void accelererSon(char* sName, float facteurAcceleration);

	/// Boucle sur un son
	void bouclerSon(char* sName, bool loop = true);

	/// Arrete un son
	void arreterSon(char* sName);

	/// Arreter tout les sons
	void arreterSon();

	/// Mute un son
	void muteSound(char* sName, bool mute);

	/// Mute tout les sons
	void sourdine(bool mute);

	/// Pause tout les sons
	void pauseGlobal(bool pause);

	/// Ajuste le volume d'un son
	void ajusterVolume(char* sName, float pourcentage);

	/// Ajuste le volume des BGM
	void ajusterBGM(float percent);

	/// Ajuste le volume des SFX
	void ajusterSFX(float percent);
	

private:
	
	/// Cherche un son dans le vecteur 
	int lookUp(std::string fileName);
	
	/// Limite globalement le volume max
	void setVolumeLimiter();
	
	/// Limite globalement le volume des BGM
	void setVolumeBGM();
	
	/// Limite globalement le volume des SFX
	void setVolumeSFX();
	
	/// Retourne le path d'un fichier sonore
	static std::string getSFXPath(char* sName);

	/// Le FMOS SYSTEM des sons
	FMOD::System* system_;
	
	/// Structure liant le no du son, le pointeur vers le son et le canal du son dans un vecteur
	std::vector < std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > > soundTable_;

	/// Volume maximale des BGM
	float maxBGM_;

	/// Volume maximale des SFX
	float maxSFX_;

	/// Desactiver les sons
	bool sonDesactive;
};

#endif //__FACADE_SOUND_CONTROLLER_CLASS_H__