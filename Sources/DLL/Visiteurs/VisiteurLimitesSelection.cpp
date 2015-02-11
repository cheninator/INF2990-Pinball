////////////////////////////////////////////////
/// @file   VisiteurCentreDeMasse.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurLimitesSelection.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCentreDeMasse::VisiteurCentreDeMasse()
///
/// Constructeur.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurLimitesSelection::VisiteurLimitesSelection()
:xMin_{ 2000 },
 xMax_{ -2000 },
 yMin_{ 2000 },
 yMax_{ -2000 }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCentreDeMasse::~VisiteurCentreDeMasse()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurLimitesSelection::~VisiteurLimitesSelection()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(ArbreRenduINF2990* noeud)
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurLimitesSelection::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// faite correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurLimitesSelection::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(NoeudAbstrait* noeud)
/// @brief Calcule le centre de masse (tous les noeuds ont une masse de 1)
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurLimitesSelection::traiter(NoeudAbstrait* noeud)
{
	glm::dvec3 position{ noeud->obtenirPositionRelative() };
	if (noeud->estSelectionne())
	{
		if (position.x > xMax_)
			xMax_ = position.x;

		if (position.x < xMin_)
			xMin_ = position.x;

		if (position.y > yMax_)
			yMax_ = position.y;

		if (position.y < yMin_)
			yMin_ = position.y;
	}

	return true;
}