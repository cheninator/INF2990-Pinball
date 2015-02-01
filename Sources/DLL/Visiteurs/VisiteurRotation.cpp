#include "VisiteurRotation.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudButoir.h"
#include "../Arbre/Noeuds/NoeudCible.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudPalette.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRessort.h"
#include "../Arbre/Noeuds/NoeudTrou.h"


VisiteurRotation::VisiteurRotation()
{
	angle_ = 0.0;
	axe_ = 'x';
	sensPositif_ = true;
}

VisiteurRotation::VisiteurRotation(float angle, char axe, bool sensPositif)
{
	angle_ = angle;
	axe_ = axe;
	sensPositif_ = sensPositif;
}

VisiteurRotation::~VisiteurRotation()
{

}

bool VisiteurRotation::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		// Déplacer UNIQUEMENT les noeuds selectionnes
		if (noeud->getEnfant(i) != nullptr && noeud->getEnfant(i)->estSelectionnable())
			noeud->getEnfant(i)->accepterVisiteur(this);

		else
			return false;
	}

	return true;
}



////////////// TO DO


bool VisiteurRotation::traiter(NoeudAbstrait* noeud)
{

	return true;
}

bool VisiteurRotation::traiter(NoeudButoir* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudCible* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudGenerateurBille* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudMur* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudPalette* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudPortail* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudRessort* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudTrou* noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudTable* noeud)
{
	return false;
}