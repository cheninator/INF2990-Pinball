#include "VisiteurDeplacement.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudButoir.h"
#include "../Arbre/Noeuds/NoeudCible.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudPalette.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRessort.h"
#include "../Arbre/Noeuds/NoeudTrou.h"

VisiteurDeplacement::VisiteurDeplacement()
{
	deplacement_[0] = 0.0;
	deplacement_[1] = 0.0;
	deplacement_[2] = 0.0;
}

VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 dep)
{
	deplacement_ = dep;
}

VisiteurDeplacement::~VisiteurDeplacement()
{

}

bool VisiteurDeplacement::traiter(ArbreRenduINF2990& noeud)
{
	for (unsigned int i = 0; i < noeud.obtenirNombreEnfants(); i++)
	{
		// Déplacer UNIQUEMENT les noeuds selectionnes
		if (noeud.getEnfant(i) != nullptr && noeud.getEnfant(i)->estSelectionnable())
			noeud.getEnfant(i)->accepterVisiteur(this);

		else
			return false;
	}

	return true;
}


bool VisiteurDeplacement::traiter(NoeudAbstrait& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudButoir& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudCible& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudGenerateurBille& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudMur& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudPalette& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudPortail& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudRessort& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudTrou& noeud)
{
	noeud.assignerPositionRelative(deplacement_);
	return true;
}

bool VisiteurDeplacement::traiter(NoeudTable& noeud)
{
	return false;
}