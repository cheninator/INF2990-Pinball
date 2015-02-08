////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurDeselectionnerTout.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour visiter ses enfants
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudTable* noeud)
///
/// Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeselectionnerTout::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudAbstrait* noeud)
///
/// Ce visiteur désélectionne tous les noeuds
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeselectionnerTout::traiter(NoeudAbstrait* noeud)
{
	noeud->assignerSelection(false);
	return true;
}

