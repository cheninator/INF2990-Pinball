////////////////////////////////////////////////
/// @file   SingletonGlobal.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup SingletonGlobal
////////////////////////////////////////////////

#ifndef __SINGLETONGLOBAL_H__
#define __SINGLETONGLOBAL_H__

#include "../Application/FacadeModele.h"

///////////////////////////////////////////////////////////////////////////
/// @class SingletonGlobal
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class SingletonGlobal
{

public:

	/// Obtient l'instance unique de la classe.
	static SingletonGlobal* obtenirInstance();

	/// Libère l'instance unique de la classe.
	static void libererInstance();

	/// AJOUTER VOS GET/SET sur les variables ici
	//int getNombreDeBillesDisponibles() { return nombreDeBillesDisponibles_; };

	//int getPointsTotales() { return pointsTotales_; };
	//void setPointsTotales(int pointsTotales) { pointsTotales_ = pointsTotales; };

	int getPointsPartie() { return pointsPartie_; };
	
	void setPointsPartie(int pointsPartie) { pointsPartie_ = pointsPartie; };

	//void checkBille() {};

	void collisionButoirCirculaire() { pointsPartie_ += collisionPointsCirculaire_; /*checkBille();*/ };
	void collisionButoirTriangulaire() { pointsPartie_ += collisionPointsTriangulaire_; /*checkBille();*/ };
	void collisionButoirCible() { pointsPartie_ += collisionPointsCible_; /*checkBille();*/ };

	void resetConfigurationCollision(int collisionPointsCirculaire,
											int collisionPointsTriangulaire,
											int collisionPointsCible,
											int collisionPointsPartieGagner,
											int collisionPointsNouvelleBille);

	void retirerBille() { billesCourantes_--; };
	void ajouterBille() { billesCourantes_++; };
	int obtenirBille() { return billesCourantes_; };
	void resetBille()  { billesCourantes_ = 0; };

	void setAnimation(bool animer) { animer_ = animer; };
	bool obtenirAnimation() { return animer_; };
protected:

	/// Constructeur vide déclaré protected.
	SingletonGlobal() {};

	/// Destructeur vide déclaré protected.
	~SingletonGlobal() {};

private:

	static SingletonGlobal* singleton_;

	/// Constructeur par copie déclaré mais non défini.
	SingletonGlobal(const SingletonGlobal&) = delete;

	/// Opérateur d'assignation déclaré mais non défini.
	SingletonGlobal& operator=(const SingletonGlobal&) = delete;

	/// AJOUTER VOS VARIABLES GLOBAL ICI
	
	//int nombreDeBillesGagner_{ 0 };
	//int nombreDeBillesDisponibles_{ 0 };

	//int pointsTotales_{ 0 };
	int pointsPartie_{ 0 };

	int collisionPointsCirculaire_{ 0 };
	int collisionPointsTriangulaire_{ 0 };
	int collisionPointsCible_{ 0 };
	int collisionPointsPartieGagner_{ 0 };
	int collisionPointsNouvelleBille_{ 0 };

	int billesCourantes_{ 0 };

	bool animer_{ true };
};

#endif // __SINGLETONGLOBAL_H__