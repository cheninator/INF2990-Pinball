////////////////////////////////////////////////
/// @file   VisiteurAgrandissement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurCentreDeMasse.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include <iostream>




////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCentreDeMasse::VisiteurCentreDeMasse(glm::dvec3 homothethie)
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
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCentreDeMasse::~VisiteurCentreDeMasse()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurCentreDeMasse::traiter(ArbreRenduINF2990* arbre)
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
/// @fn bool VisiteurSelection::traiter(NoeudTable* noeud)
///
/// Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
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
/// @fn bool VisiteurCentreDeMasse::traiter(NoeudAbstrait* arbre)
///
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