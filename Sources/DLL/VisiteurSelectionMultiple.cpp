////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurSelectionMultiple.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionMultiple::VisiteurSelectionMultiple()
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
VisiteurSelectionMultiple::VisiteurSelectionMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit)
:nbObjetsSelectionne_{ 0 }
{
	selectionBasGauche_ = selectionBasGauche;
	selectionHautDroit_ = selectionHautDroit;
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
VisiteurSelectionMultiple::~VisiteurSelectionMultiple()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour selectionner ses enfants
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionMultiple::traiter(ArbreRenduINF2990* arbre)
{
	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}

bool VisiteurSelectionMultiple::traiter(NoeudTable* table)
{;
	// Traiter les enfants selectionn�s de la table
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
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi trait�s.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionMultiple::traiter(NoeudAbstrait* noeud)
{
	std::cout << "visite d'un noeudAbstrait avec identifiant " << noeud->getNumero() << std::endl;

	glm::dvec3 origineNoeud = noeud->obtenirPositionRelative();

	if (utilitaire::DANS_LIMITESXY(origineNoeud.x, selectionBasGauche_.x, selectionBasGauche_.x,
		                           origineNoeud.y, selectionBasGauche_.y, selectionBasGauche_.y))
	{
		std::cout << "Noeud de type " << noeud->getType() << " selectionne " << std::endl;
		noeud->assignerSelection(true);
		nbObjetsSelectionne_++;
	}
	else
	{
		noeud->assignerSelection(false);
	}

	return true;
}