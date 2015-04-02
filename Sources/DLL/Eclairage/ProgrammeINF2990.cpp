#include "ProgrammeINF2990.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"

#include <iostream>

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
	

	// Checker que tout est correct
	if (programme_->estValide() && programme_->estInitialise())
	{
		EstInitialise_ = true;
		std::cout << "Le programme est valide" << std::endl;
		int monIntTest = 0;
		programme_->assignerUniforme("monIntTest", monIntTest);
	}
}


void ProgrammeINF2990::activer()
{
	// std::cout <<"Etat de validite de progNuanceur: "<< programme_->estValide() << std::endl;
	assert(programme_ != nullptr && "Activation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Start(*programme_);
	//std::cout << programme_->serialiser() << std::endl;
}


void ProgrammeINF2990::desactiver()
{
	assert(programme_ != nullptr && "Desactivation d'un programme de nuanceurs pas initialise");
	opengl::Programme::Stop(*programme_);
}

