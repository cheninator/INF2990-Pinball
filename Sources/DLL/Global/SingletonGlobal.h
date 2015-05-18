////////////////////////////////////////////////
/// @file   SingletonGlobal.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup SingletonGlobal
////////////////////////////////////////////////

#ifndef __SINGLETONGLOBAL_H__
#define __SINGLETONGLOBAL_H__

#include "../Sound/ControleurSon.h"
#include "../Application/FacadeModele.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include <sstream>
#include "glm\glm.hpp"

#define SoundControl SingletonGlobal::obtenirInstance()->obtenirControleurSon()

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

	/// Libere l'instance unique de la classe.
	static void libererInstance();

	/// AJOUTER VOS GET/SET sur les variables ici
	//int getNombreDeBillesDisponibles() { return nombreDeBillesDisponibles_; };

	//int getPointsTotales() { return pointsTotales_; };
	//void setPointsTotales(int pointsTotales) { pointsTotales_ = pointsTotales; };

	int getPointsPartie() const { return pointsPartie_; };

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

	void retirerBille() { billesCourantes_--; billesPerdus_++; };
	void ajouterBille() { billesCourantes_++; };
	void afficherBille();
	int obtenirBille() const { return billesCourantes_; };
	int obtenirNombreDeBillesPerdus() const { return billesPerdus_; };
	void resetBille()  { billesCourantes_ = 0; };

	void updateBilles();
	void setAnimation(bool animer) { animer_ = animer; };
	bool obtenirAnimation() const { return animer_; };

	void spawnBille(glm::dvec3 position, glm::dvec3 echelle, NoeudAbstrait* portail);

	std::string obtenirPathTemp() { objectPathCreated_ ? NULL : getAndSetTempObjDirectory(); return objectPath_; };

	void finGeneration() { enCoursDeGeneration_ = false; };

	void activerSon() { desactiverSon = false; };
	ControleurSon*  obtenirControleurSon();

	double obtenirTableMaxX() const;
	double obtenirTableMaxY() const;
	double obtenirTableMinX() const;
	double obtenirTableMinY() const;
	double obtenirTableMinZ() const;

	void setBoiteTable(utilitaire::BoiteEnglobante boiteTable) { boiteTable_ = boiteTable; };
protected:
	/// Constructeur vide declare protected.
	SingletonGlobal() {   boiteTable_.coinMax = { 0, 0, 0 }; boiteTable_.coinMin = { 0, 0, 0 };   };

	/// Destructeur vide declare protected.
	~SingletonGlobal() { delete mySound_; };

private:

	void getAndSetTempObjDirectory();

	static SingletonGlobal* singleton_;

	/// Constructeur par copie declare mais non defini.
	SingletonGlobal(const SingletonGlobal&) = delete;

	/// Operateur d'assignation declare mais non defini.
	SingletonGlobal& operator=(const SingletonGlobal&) = delete;

	/// AJOUTER VOS VARIABLES GLOBAL ICI

	int pointsPartie_{ 0 };
	int billesPerdus_{ 0 };

	int collisionPointsCirculaire_{ 0 };
	int collisionPointsTriangulaire_{ 0 };
	int collisionPointsCible_{ 0 };
	int collisionPointsPartieGagner_{ 0 };
	int collisionPointsNouvelleBille_{ 0 };

	int billesCourantes_{ 0 };

	bool animer_{ true };

	std::string objectPath_;
	bool objectPathCreated_{ false };
	bool enCoursDeGeneration_{ 0 };
	std::vector<std::pair<std::pair<glm::dvec3, glm::dvec3>, NoeudAbstrait*>> launchSequence_;

	// Controleur de son
	bool desactiverSon{ true };
	ControleurSon* mySound_{ nullptr };

	utilitaire::BoiteEnglobante boiteTable_;
};

#endif // __SINGLETONGLOBAL_H__