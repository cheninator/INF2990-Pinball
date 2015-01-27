#include "VisiteurRotation.h"
#include "../Arbre/Noeuds/NoeudButoir.h"
#include "../Arbre/Noeuds/NoeudCible.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudPalette.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudRessort.h"
#include "../Arbre/Noeuds/NoeudTrou.h"

bool VisiteurRotation::traiter(NoeudButoir& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudCible& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudGenerateurBille& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudMur& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudPalette& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudPortail& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudRessort& noeud)
{
	noeud.setAngle(angle_);
	return true;
}

bool VisiteurRotation::traiter(NoeudTrou& noeud)
{
	noeud.setAngle(angle_);
	return true;
}