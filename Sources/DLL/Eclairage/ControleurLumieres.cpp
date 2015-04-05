///////////////////////////////////////////////////////////////////////////////
/// @file ControleurLumieres.cpp
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////


#include "ControleurLumieres.h"
#include "ControleurNuanceurs.h"
#include <iostream>

#define LUMIERE_OFF 0
#define LUMIERE_ON 1


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurLumieres::ControleurLumieres()
/// 
/// @brief Assigne des poignees openGL choisies aux trois lumieres
///
////////////////////////////////////////////////////////////////////////
ControleurLumieres::ControleurLumieres()
{
	lumAmbiante_ = new Lumiere(GL_LIGHT1);
	lumDirectionnelle_ = new Lumiere(GL_LIGHT2);
	lumSpot_ = new Lumiere(GL_LIGHT3);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurLumieres::~ControleurLumieres()
///
/// @brief Destructeur, detruit les lumieres.
///
////////////////////////////////////////////////////////////////////////
ControleurLumieres::~ControleurLumieres()
{
	delete lumAmbiante_;
	delete lumDirectionnelle_;
	delete lumSpot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::initialiserLumieres() 
/// 
/// @Brief Place les lumieres et definit leur proprietes.
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::initialiserLumieres()
{
	// Initialiser lumAmbiante
	lumAmbiante_->setAmbientColor({ 0.05f, 0.05f, 0.05f, 1.0f });
	lumAmbiante_->setDiffuseColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	lumAmbiante_->setSpecularColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	// Initialiser lumDirectionnelle
	lumDirectionnelle_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumDirectionnelle_->setDiffuseColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	lumDirectionnelle_->setSpecularColor({ 0.5f, 0.5f, 0.7f, 1.0f });

	lumDirectionnelle_->setPosition({ 200.0f, -47.0f, 110.0f, 1.0f });
	lumDirectionnelle_->setDirection({ 0.1f, 0.0f, -1.0f, 1.0f });

	// Inisialiser lumSpot
	lumSpot_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f }); 
	lumSpot_->setDiffuseColor({ 0.4f, 0.4f, 0.3f, 1.0f }); 
	lumSpot_->setSpecularColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	   
	lumSpot_->setPosition({ 200.0f, -47.0f, 400.0f, 1.0f });
	lumSpot_->setDirection({ 0.0f, 0.0f, -1.0f, 1.0f });
	lumSpot_->setCutoffAngle(10.0f);
	lumSpot_->setExponent(0.2f);

	lumSpot_->setAttenuation({ 1.0f, 1.0f, 0.1f });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::definirLumieres()
/// 
/// @brief Envoi les donnees des lumieres au serveur openGL
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::definirLumieres()
{
	lumAmbiante_->definir();
	lumDirectionnelle_->definir();
	lumSpot_->definir();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerAmbiante() 
/// 
/// @brief Active le calcul de lumiere ambiante dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerAmbiante()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatAmbiante(LUMIERE_ON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverAmbiante() // TODO PHIL
///
/// @brief Desactive le calcul de lumiere ambiante dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverAmbiante()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatAmbiante(LUMIERE_OFF);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerDirectionnelle() 
/// 
/// @brief Active le calcul de lumiere directionnelle dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerDirectionnelle()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatDirectionnelle(LUMIERE_ON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverDirectionnelle() 
///
/// @brief Desactive le calcul de lumiere directionnelle dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverDirectionnelle()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatDirectionnelle(LUMIERE_OFF);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerSpot() 
///
/// @brief Active le calcul de lumiere spot dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerSpot()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatSpot(LUMIERE_ON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverSpot()
///
/// @brief Desactive le calcul de lumiere spot dans le nuanceur
/// 
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverSpot()
{
	ControleurNuanceurs::obtenirInstance()->assignerEtatSpot(LUMIERE_OFF);
}

void ControleurLumieres::touche1()
{
	std::cout << "ControleurLumieres::touche1()" << std::endl;
	// lumDirectionnelle_->setPosition(lumDirectionnelle_->getPosition() + glm::fvec4{ +10.0f, 0.0f, 0.0f, 0.0f });
	lumSpot_->setCutoffAngle(lumSpot_->getCutoffAngle() - 1);
}

void ControleurLumieres::touche2()
{
	std::cout << "ControleurLumieres::touche2()" << std::endl;
	lumSpot_->setCutoffAngle(lumSpot_->getCutoffAngle() + 1);
}

void ControleurLumieres::touche3()
{
	std::cout << "ControleurLumieres::touche3()" << std::endl;
	desactiverSpot();// lumSpot_->setExponent(lumSpot_->getExponent() + 0.1);
	// lumDirectionnelle_->setPosition(lumDirectionnelle_->getPosition() + glm::fvec4{ 0.0f, 0.0f, 10.0f, 0.0f });
	
}
