///////////////////////////////////////////////////////////////////////////////
/// @file ProgrammeINF2990.cpp
/// @author The ballers
/// @date 2015-03-20
/// @version 1.0
///
/// @ingroup Eclairage
///////////////////////////////////////////////////////////////////////////////


#include "ProgrammeINF2990.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"

#include <iostream>

ProgrammeINF2990* ProgrammeINF2990::instance_{ nullptr };

ProgrammeINF2990* ProgrammeINF2990::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new ProgrammeINF2990();

	return instance_;
}

void ProgrammeINF2990::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ProgrammeINF2990::~ProgrammeINF2990() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ProgrammeINF2990::~ProgrammeINF2990()
{
	// Les destructeurs s'occuppent de relacher les ressources OpenGL liés aux objets.
	desactiver();
	delete programme_;
	delete nuanceurSommets_;
	delete nuanceurFragments_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProgrammeINF2990::initialiser() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ProgrammeINF2990::initialiser()
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
/// @fn void ProgrammeINF2990::activer() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ProgrammeINF2990::activer()
{
	// std::cout <<"Etat de validite de progNuanceur: "<< programme_->estValide() << std::endl;
	assert(programme_ != nullptr && "Activation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Start(*programme_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProgrammeINF2990::desactiver() // TODO PHIL
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void ProgrammeINF2990::desactiver()
{
	assert(programme_ != nullptr && "Desactivation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Stop(*programme_);
}

