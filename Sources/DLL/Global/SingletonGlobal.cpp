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

	pointsTotales_ += pointsPartie_;

	pointsPartie_ = 0;

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