#include "VisiteurRotation.h"
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

//
// TO DO
//

bool VisiteurRotation::traiter(NoeudAbstrait& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudButoir& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudCible& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudGenerateurBille& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudMur& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudPalette& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudPortail& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudRessort& noeud)
{
	return true;
}

bool VisiteurRotation::traiter(NoeudTrou& noeud)
{
	return true;
}