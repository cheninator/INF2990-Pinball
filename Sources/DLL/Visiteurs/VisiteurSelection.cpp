////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurSelection.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurSelection(glm::dvec3 pointDansLeMonde)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de deplacement
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection(glm::dvec3 pointDansLeMonde, int valeurStencil)
:nbObjetsSelectionne_{ 0 }
{
	pointDansLeMonde_ = pointDansLeMonde;
	valeurStencil_ = valeurStencil;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::~VisiteurSelection()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::~VisiteurSelection()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour visiter ses enfants
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. 
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
{
	if (valeurStencil_ == noeud->getNumero() && noeud->estSelectionnable() /*&& noeud->estModifiable()*/)
		noeud->assignerSelection(true);
	else
		noeud->assignerSelection(false);

	if (noeud->estSelectionne()) 
		nbObjetsSelectionne_++;

	return true;
}

