////////////////////////////////////////////////
/// @file   VisiteurCentreDeMasse.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurCentreDeMasse.h"
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
VisiteurCentreDeMasse::VisiteurCentreDeMasse()
:centreDeMasse_{ 0, 0, 0 },
nbNoeuds_{ 0 }
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
VisiteurCentreDeMasse::~VisiteurCentreDeMasse()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(ArbreRenduINF2990* noeud)
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurCentreDeMasse::traiter(ArbreRenduINF2990* noeud)
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
bool VisiteurCentreDeMasse::traiter(NoeudTable* table)
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
bool VisiteurCentreDeMasse::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		centreDeMasse_ += noeud->obtenirPositionRelative();
		nbNoeuds_++;
	}

	return true;
}