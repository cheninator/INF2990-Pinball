#include "VisiteurSelection.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudButoir.h"
#include "../Arbre/Noeuds/NoeudCible.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudPalette.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRessort.h"
#include "../Arbre/Noeuds/NoeudTrou.h"

#include <iostream>


VisiteurSelection::VisiteurSelection(glm::dvec3 pointDansLeMonde)
:pointDansLeMonde_{ pointDansLeMonde },
noeudSelection_{new NoeudComposite()}
{

}

VisiteurSelection::~VisiteurSelection()
{

}

bool VisiteurSelection::traiter(ArbreRenduINF2990& arbre)
{
	std::cout << "visite d'un arbre avec " << arbre.obtenirNombreEnfants()<< " enfants." << std::endl;
	for (unsigned int i = 0; i < arbre.obtenirNombreEnfants(); i++)
	{
		if (arbre.getEnfant(i) != nullptr )
			arbre.getEnfant(i)->accepterVisiteur(this);
	}
	// Aucun traitement a faire pour la racine de l'arbre;
	
	return true;
}

bool VisiteurSelection::traiter(NoeudAbstrait& noeud)
{
	double distance = glm::dot(pointDansLeMonde_ - noeud.obtenirPositionRelative(), pointDansLeMonde_ - noeud.obtenirPositionRelative());
	distance = sqrt(distance);
	std::cout << "visite d'un noeudAbstrait" << " a la position : ";
	std::cout << noeud.obtenirPositionRelative().x <<","
			<< noeud.obtenirPositionRelative().y << "," 
			<< noeud.obtenirPositionRelative().z << ",      Distance:" << distance << std::endl;
	
	if (distance < 30)
	{

		std::cout << "noeud Selectionne !" << std::endl;
		noeudSelection_->ajouter(&noeud);
	}

	return true;
}

bool VisiteurSelection::traiter(NoeudButoir& noeud)
{
	return true;
}

bool VisiteurSelection::traiter(NoeudCible& noeud)
{
	return true;
}

bool VisiteurSelection::traiter(NoeudGenerateurBille& noeud)
{
	return true;
}

bool VisiteurSelection::traiter(NoeudMur& noeud)
{
	return true;
}

bool VisiteurSelection::traiter(NoeudPalette& noeud)
{
	return true;
}

bool VisiteurSelection::traiter(NoeudPortail& noeud)
{

	return true;
}

bool VisiteurSelection::traiter(NoeudRessort& noeud)
{

	return true;
}

bool VisiteurSelection::traiter(NoeudTrou& noeud)
{

	return true;
}

bool VisiteurSelection::traiter(NoeudTable& noeud)
{
	return false;
}