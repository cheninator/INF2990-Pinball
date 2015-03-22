////////////////////////////////////////////////
/// @file SingletonGlobal.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup Global
////////////////////////////////////////////////

#include "SingletonGlobal.h"

SingletonGlobal* SingletonGlobal::singleton_{ nullptr };
////////////////////////////////////////////////////////////////////////
///
/// @fn SingletonGlobal* SingletonGlobal::obtenirInstance()
///
/// Cette fonction retourne l'instance unique de la classe. Si l'instance
/// n'existe pas, elle est créée. Ainsi, une seule instance sera créée.
/// Cette fonction n'est pas "thread-safe".
///
/// @return L'instance unique de la classe.
///
////////////////////////////////////////////////////////////////////////
SingletonGlobal* SingletonGlobal::obtenirInstance()
{
	if (singleton_ == nullptr){
		singleton_ = new SingletonGlobal();
	}
	return singleton_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::resetConfigurationCollision()
///
/// Permet de mettre a jour les valeurs des points pour chaque collision
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::resetConfigurationCollision(int collisionPointsCirculaire,
	int collisionPointsTriangulaire,
	int collisionPointsCible,
	int collisionPointsPartieGagner,
	int collisionPointsNouvelleBille)
{
	collisionPointsCirculaire_ = collisionPointsCirculaire;
	collisionPointsTriangulaire_ = collisionPointsTriangulaire;
	collisionPointsCible_ = collisionPointsCible;
	collisionPointsPartieGagner_ = collisionPointsPartieGagner;
	collisionPointsNouvelleBille_ = collisionPointsPartieGagner;
	//nombreDeBillesDisponibles_ = FacadeModele::obtenirInstance()->obtenirConfiguration()[5];
	//nombreDeBillesGagner_ = 0;

	//pointsTotales_ += pointsPartie_;
	pointsPartie_ = 0;
	enCoursDeGeneration_ = 0;
	launchSequence_.clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::updateBilles()
///
/// Met a jour le gestionaire de billes
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::updateBilles()
{
	if (enCoursDeGeneration_ == 0 && launchSequence_.size() > 0)
	{
		launchSequence_.back().second->genererBille();
		enCoursDeGeneration_++;
		afficherBille();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::spawnBille(glm::dvec3 position, glm::dvec3 echelle, NoeudAbstrait* portail)
///
/// Gere le moment de création d'une bille (pour respecter la regle des une secondes)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::spawnBille(glm::dvec3 position, glm::dvec3 echelle, NoeudAbstrait* portail)
{
	launchSequence_.push_back({ { position, echelle }, portail });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::afficherBille()
///
/// Affiche la bille
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::afficherBille()
{
	glm::dvec3 position = launchSequence_.back().first.first;
	glm::dvec3 scale = launchSequence_.back().first.second;
	launchSequence_.pop_back();
	FacadeModele::obtenirInstance()->creeBille(position, scale);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::libererInstance()
///
/// Détruit l'instance unique de la classe.  Cette fonction n'est pas
/// "thread-safe".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::libererInstance()
{
	delete singleton_;
	singleton_ = 0;
	//free(objectPath_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::getAndSetTempObjDirectory()
///
/// Ecrit la valeur du path courant + /zones/zoneTemp.bin dans une variable
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::getAndSetTempObjDirectory()
{
	objectPathCreated_ = true;
	// Dont ask
	// http://stackoverflow.com/questions/875249/how-to-get-current-directory
	// https://vajris.wordpress.com/2012/10/15/conversion-tchar-wstring-string-string/
	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring wBuffer(buffer);
	std::string currentFolder(wBuffer.begin(), wBuffer.end());
	std::string::size_type position = currentFolder.find_last_of("\\/");
	std::string targetPath = std::string(currentFolder).substr(0, position);
	targetPath += "\\zones\\zoneTemp.bin";
	objectPath_ = targetPath;
}

/*
////////////////////////////////////////////////////////////////////////
///
/// @fn void SingletonGlobal::checkBille()
///
/// Fait toute les verifivatiosn de partie
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SingletonGlobal::checkBille()
{
if (pointsPartie_ > nombreDeBillesGagner_ * collisionPointsNouvelleBille_ + collisionPointsNouvelleBille_)
nombreDeBillesGagner_++;
}
*/
