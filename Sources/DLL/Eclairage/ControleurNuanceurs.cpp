///////////////////////////////////////////////////////////////////////////////
/// @file ControleurNuanceurs.cpp
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////

#include "ControleurNuanceurs.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"

#include <iostream>

ControleurNuanceurs* ControleurNuanceurs::instance_{ nullptr };

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurNuanceurs* ControleurNuanceurs::obtenirInstance() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ControleurNuanceurs* ControleurNuanceurs::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new ControleurNuanceurs();

	return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::libererInstance() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurNuanceurs::~ControleurNuanceurs() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ControleurNuanceurs::~ControleurNuanceurs()
{
	// Les destructeurs s'occuppent de relacher les ressources OpenGL liés aux objets.
	desactiver();
	delete programme_;
	delete nuanceurSommets_;
	delete nuanceurFragments_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::initialiser() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::initialiser()
{
	// Initialiser le nuanceur de sommets
	nuanceurSommets_ = new opengl::Nuanceur();
	nuanceurSommets_->initialiser(opengl::Nuanceur::Type::NUANCEUR_VERTEX, "Nuanceurs/NuanceurSommetsINF2990.glsl");
	
	// Initialiser le nuanceur de fragments
	nuanceurFragments_ = new opengl::Nuanceur();
	nuanceurFragments_->initialiser(opengl::Nuanceur::Type::NUANCEUR_FRAGMENT, "Nuanceurs/NuanceurFragmentsINF2990.glsl");

	// Initialiser le programme
	programme_ = new opengl::Programme();
	programme_->initialiser();
	programme_->attacherNuanceur(*nuanceurSommets_);
	programme_->attacherNuanceur(*nuanceurFragments_);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::activer() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::activer()
{
	assert(programme_ != nullptr && "Activation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Start(*programme_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::desactiver() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::desactiver()
{
	assert(programme_ != nullptr && "Desactivation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Stop(*programme_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerColorShift(int colorShift)// TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerColorShift(int colorShift)
{
	programme_->assignerUniforme("colorShift", colorShift);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleurNuanceurs::assignerEtatNoeud(int etat) // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerEtatNoeud(int etat)
{
	programme_->assignerUniforme("etatNoeud", etat);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurNuanceurs::assignerNumeroNoeud(int numero) // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ControleurNuanceurs::assignerNumeroNoeud(int numero)
{
	programme_->assignerUniforme("numeroNoeud", numero);
}
