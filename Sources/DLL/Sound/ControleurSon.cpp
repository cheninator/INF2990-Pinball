////////////////////////////////////////////////////////////////////////////////////
/// @file ControleurSon.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Sons
///
////////////////////////////////////////////////////////////////////////////////////


#include "ControleurSon.h"
#define DEFAULT_FREQUENCY 44100 // Hz

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurSon::ControleurSon()
///
/// @param[in] desactiverSon Desactive tout les son et ne les load pas
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ControleurSon::ControleurSon(bool desactiverSon)
{
	sonDesactive = desactiverSon;
	if (sonDesactive)
		return;
	FMOD::System_Create(&system_);
	system_->init(1024, FMOD_INIT_NORMAL, 0);
	maxBGM_ = 1;
	maxSFX_ = 1;

	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring wBuffer(buffer);
	std::string currentFolder(wBuffer.begin(), wBuffer.end());
	std::string::size_type position = currentFolder.find_last_of("\\/");
	std::string targetPath = std::string(currentFolder).substr(0, position);
	targetPath += "\\media\\SFX\\";
	const char* d = targetPath.c_str();
	std::vector<std::string> f;

	FILE* pipe = NULL;
	std::string pCmd = "dir /B /S \"" + std::string(d) + char(34);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		return;
	}

	while (!feof(pipe))
	{
		if (fgets(buf, 256, pipe) != NULL)
		{
			f.push_back(std::string(buf));
		}
	}
	_pclose(pipe);
	for (unsigned int i = 0; i < f.size(); i++)
	{
		std::string name = f[i];
		name.erase(0, targetPath.length());
		name.erase(name.length() - 1);
		creeSon((char*)name.c_str());
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurSon::~ControleurSon()
///
/// Vide la table des sons et delete le system
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ControleurSon::~ControleurSon()
{
	if (sonDesactive)
		return;
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		soundTable_[i].second.second->stop();
	system_->release();
	system_->close();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::creeSon(char* sName)
///
/// Methode qui va chercher les fichiers son et le cree
///
/// @param[in] sName : Le nom du son
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::creeSon(char* sName)
{
	if (sonDesactive)
		return;
	std::string name(sName);

	// Check if already created
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == name)
			return;

	std::string path = getSFXPath(sName);
	const char* sPath = path.c_str();
	std::cout << "\tAdding " << name << "..." << std::setfill(' ') << std::setw(40 - name.length());

	std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > apair;
	std::string nameOfMusic = std::string(sName);
	apair.first = nameOfMusic.substr(0, nameOfMusic.size() - 4);
	apair.second.first = NULL;
	apair.second.second = NULL;
	soundTable_.push_back(apair);
	if (path.substr(path.size() - 3) == "wav")
		std::cout << ((system_->createSound(sPath, FMOD_DEFAULT, 0, &soundTable_[soundTable_.size() - 1].second.first)
		== FMOD_OK) ? "OK" : "FAILED") << std::endl;
	else
		std::cout << ((system_->createStream(sPath, FMOD_DEFAULT, 0, &soundTable_[soundTable_.size() - 1].second.first)
		== FMOD_OK) ? "OK" : "FAILED") << std::endl;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::pauseGlobal(bool pause)
///
/// On pause tout les sons
///
/// @param[in] pause : Si les son sont pause ou non
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::pauseGlobal(bool pause)
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
	{
		soundTable_[i].second.second->setPaused(pause);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::jouerSon(char* sName, bool pause)
///
/// On joue le son (ou pas)
///
/// @param[in] sName : Le nom du son
/// @param[in] pause : Si le son est pause ou non
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::jouerSon(char* sName, bool pause)
{
	if (sonDesactive)
		return;
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	system_->playSound(FMOD_CHANNEL_REUSE, soundTable_[i].second.first, pause, &soundTable_[i].second.second);
	setVolumeLimiter();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::accelererSon(char* sName, float facteurAcceleration)
///
/// On joue le son (ou pas)
///
/// @param[in] sName : Le nom du son
/// @param[in] facteurAcceleration : X acceleration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::accelererSon(char* sName, float facteurAcceleration)
{
	if (sonDesactive)
		return;
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	
	soundTable_[i].second.second->setFrequency(DEFAULT_FREQUENCY * facteurAcceleration);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::bouclerSon(char* sName, bool loop)
///
/// On boucle sur le son (ou pas)
///
/// @param[in] sName : Le nom du son
/// @param[in] loop : on boucle sur le son
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::bouclerSon(char* sName, bool loop)
{
	if (sonDesactive)
		return;
	int i = lookUp(std::string(sName));
		if (i == -1)
			return;
	soundTable_[i].second.first->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::arreterSon(char* sName)
///
/// On arrete le son (sans le detruire)
///
/// @param[in] sName : Le nom du son
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::arreterSon(char* sName)
{
	if (sonDesactive)
		return;
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	soundTable_[i].second.second->stop();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::arreterSon()
///
/// On arrete tout les sons (sans les detruire)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::arreterSon()
{
	if (sonDesactive)
		return;
	// Arret de tout les sons
	for (unsigned int i = 0; i < soundTable_.size(); i++)
	{
		soundTable_[i].second.second->stop();
	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::muteSound(char* sName, bool mute)
///
/// On mute le son
///
/// @param[in] sName : Le nom du son
/// @param[in] mute : si on mute ou non
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::muteSound(char* sName, bool mute)
{
	if (sonDesactive)
		return;
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	soundTable_[i].second.second->setMute(mute);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::sourdine(bool mute)
///
/// On mute les sons (sirectement depuis le system_)
///
/// @param[in] mute : si on mute ou non
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::sourdine(bool mute)
{
	if (sonDesactive)
		return;
	FMOD::ChannelGroup *canal;
	system_->getMasterChannelGroup(&canal);
	canal->setMute(mute);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void  ControleurSon::lookUp(std::string fileName)
///
/// @remark cherche l'index d'un son
///
/// @param[in] fileName : le string du son
///
/// @return la position dans le vecteur du son.
///
////////////////////////////////////////////////////////////////////////
int ControleurSon::lookUp(std::string fileName)
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == fileName)
			return i;
	
	creeSon((char*)fileName.c_str());

	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == fileName)
			return i;	

	std::cout << "ERROR: " << fileName << " not found !";
	return -1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void  ControleurSon::ajusterVolume(char* sName, float percent)
///
/// @remark on modifie le volume d'un son
///
/// @param[in] sName : Le nom du son
/// @param[in] percent : pourcentage du volume
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::ajusterVolume(char* sName, float percent)
{
	if (sonDesactive)
		return;
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	if (percent > 1.0)
		percent /= 100;
	if (percent > 1 || percent < 0)
		percent = -1;
	soundTable_[i].second.second->setVolume(percent);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::ajusterBGM(float percent)
///
/// @remark on modifie le volume des son de fond
///
/// @param[in] percent : pourcentage du volume
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::ajusterBGM(float percent)
{
	if (sonDesactive)
		return;
	// Si n'Est pas entre 0 et 1 mais plus tot entre 0 et 100
	if (percent > 1.0)
		percent /= 100;
	if (percent > 1 || percent < 0)
		percent = -1;
	maxBGM_ = percent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::ajusterSFX(float percent)
///
/// @remark on modifie le volume des son des effets
///
/// @param[in] percent : pourcentage du volume
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::ajusterSFX(float percent)
{
	if (sonDesactive)
		return;
	// Si n'Est pas entre 0 et 1 mais plus tot entre 0 et 100
	if (percent > 1.0)
		percent /= 100;
	if (percent > 1 || percent < 0)
		percent = -1;
	maxSFX_ = percent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::setVolumeLimiter()
///
/// @remark on met a jour le volume globale maximal
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::setVolumeLimiter()
{
	if (sonDesactive)
		return;
	setVolumeBGM();
	setVolumeSFX();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::setVolumeLimiter()
///
/// @remark on met a jour le volume maximal des musiques de fond 
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::setVolumeBGM()
{
	if (sonDesactive)
		return;
	if (maxBGM_ == -1) return;
	FMOD_MODE mode = FMOD_LOOP_OFF;
	for (unsigned int i = 0; i < soundTable_.size(); i++)
	{
		soundTable_[i].second.first->getMode(&mode);
		if (mode == FMOD_LOOP_NORMAL)
			soundTable_[i].second.second->setVolume(maxBGM_);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::setVolumeSFX()
///
/// @remark on met a jour le volume maximal des effets sonores 
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ControleurSon::setVolumeSFX()
{
	if (sonDesactive)
		return;
	if (maxSFX_ == -1) return;
	FMOD_MODE mode = FMOD_LOOP_NORMAL;
	for (unsigned int i = 0; i < soundTable_.size(); i++)
	{
		soundTable_[i].second.first->getMode(&mode);
		if (mode != FMOD_LOOP_NORMAL)
			soundTable_[i].second.second->setVolume(maxSFX_);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurSon::getSFXPath(char* sName)
///
/// ajout media/Fonts/ au string qu'il recoit 
///
/// @param[in] sName : Le nom du son
///
/// @return le nouveau string.
///
////////////////////////////////////////////////////////////////////////
std::string ControleurSon::getSFXPath(char* sName)
{
	std::string soundPath = "media/SFX/" + std::string(sName);
	return soundPath;
}