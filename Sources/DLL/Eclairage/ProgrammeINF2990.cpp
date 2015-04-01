#include "ProgrammeINF2990.h"
#include <iostream>

void ProgrammeINF2990::initialiser()
{
	// Initialiser le nuanceur de sommets
	std::cout << "============================  SOMMETS ====================== " << std::endl;
	nuanceurSommets_ = new opengl::Nuanceur();
	nuanceurSommets_->initialiser(opengl::Nuanceur::Type::NUANCEUR_VERTEX, "Nuanceurs/NuanceurSommetsINF2990.glsl");
	std::cout << nuanceurSommets_->serialiser();
	// Initialiser le nuanceur de fragments
	std::cout << "============================  FRAGMENTS ====================== " << std::endl;
	nuanceurFragments_ = new opengl::Nuanceur();
	nuanceurFragments_->initialiser(opengl::Nuanceur::Type::NUANCEUR_FRAGMENT, "Nuanceurs/NuanceurFragmentsINF2990.glsl");
	std::cout << nuanceurFragments_->serialiser();

	// Initialiser le programme
	std::cout << "============================  PROGRAMME ====================== " << std::endl;
	programme_ = new opengl::Programme;
	programme_->initialiser();
	programme_->attacherNuanceur(*nuanceurSommets_);
	programme_->attacherNuanceur(*nuanceurFragments_);



	std::cout << "in fct ProgrammeINF2990::initialiser() -- programme_->estValide() : " << programme_->estValide() << std::endl;
	
	std::cout << programme_->serialiser();
	// Checker que tout est correct
	if (0)
		EstInitialise_ = true;
	std::cout << "============================ FIN INFO ====================== " << std::endl;

}


void ProgrammeINF2990::activer()
{
	// cout Phil
	std::cout <<"Etat de validite de progNuanceur: "<< programme_->estValide() << std::endl;
	opengl::Programme::Start(*programme_);
}


void ProgrammeINF2990::desactiver()
{
	// programme->stop();
}

