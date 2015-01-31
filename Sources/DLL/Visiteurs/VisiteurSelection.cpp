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


VisiteurSelection::VisiteurSelection()
{

}

VisiteurSelection::~VisiteurSelection()
{

}


bool VisiteurSelection::traiter(ArbreRenduINF2990& arbre)
{
	for (int i = 0; i < arbre.obtenirNombreEnfants(); i++)
	{
		if (arbre.getEnfant(i) != nullptr)
			arbre.getEnfant(i)->accepterVisiteur(this);
	}
}

bool VisiteurSelection::traiter(NoeudAbstrait& noeud)
{

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