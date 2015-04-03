///////////////////////////////////////////////////////////////////////////////
/// @file ControleurLumieres.cpp
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////


#include "ControleurLumieres.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurLumieres::ControleurLumieres()
///
/// @return 
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
/// @return 
///
////////////////////////////////////////////////////////////////////////
ControleurLumieres::~ControleurLumieres()
{
	lumAmbiante_->disable();
	lumDirectionnelle_->disable();
	lumSpot_->disable();
	delete lumAmbiante_;
	delete lumDirectionnelle_;
	delete lumSpot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::initialiserLumieres() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::initialiserLumieres()
{
	// Gros de la job: setter toutes les propriétés des 3 lumieres.


	// Initialiser lumAmbiante
	lumAmbiante_->setAmbientColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	lumAmbiante_->setDiffuseColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	lumAmbiante_->setSpecularColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	// Initialiser lumDirectionnelle
	lumDirectionnelle_->setAmbientColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumDirectionnelle_->setDiffuseColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	lumDirectionnelle_->setSpecularColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	lumDirectionnelle_->setPosition({ 200.0f, -47.0f, 110.0f, 1.0f });
	lumDirectionnelle_->setDirection({ 0.0f, 0.0f, -1.0f, 1.0f });

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
/// @fn void ControleurLumieres::definirLumieres() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::definirLumieres()
{
	lumAmbiante_->enable();
	lumAmbiante_->definir();

	lumDirectionnelle_->enable();
	lumDirectionnelle_->definir();

	lumSpot_->enable();
	lumSpot_->definir();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerAmbiante() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerAmbiante()
{
	lumAmbiante_->enable();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverAmbiante() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverAmbiante()
{
	lumAmbiante_->enable();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerDirectionnelle() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerDirectionnelle()
{
	lumDirectionnelle_->enable();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverDirectionnnelle() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverDirectionnelle()
{
	lumDirectionnelle_->enable();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::activerSpot() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::activerSpot()
{
	lumSpot_->enable();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumieres::desactiverSpot() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumieres::desactiverSpot()
{
	lumSpot_->enable();
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
	lumSpot_->setExponent(lumSpot_->getExponent() + 0.1);
	lumDirectionnelle_->setPosition(lumDirectionnelle_->getPosition() + glm::fvec4{ 0.0f, 0.0f, 10.0f, 0.0f });
	
}
