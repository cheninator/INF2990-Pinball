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
VisiteurSelection::VisiteurSelection(glm::dvec3 pointDansLeMonde)
{
	pointDansLeMonde_ = pointDansLeMonde;
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
/// Cette fonction traite l'arbre de rendu pour selectionner ses enfants
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(ArbreRenduINF2990* arbre)
{
	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		traiter(arbre->getEnfant(i));
	}

	return true;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi traités.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Si l'élément est une table, visiter ses enfants
	if (nom == "table")
	{
		// Traiter les enfants selectionnés de la table
		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			if (noeud->chercher(i)->estSelectionnable())
				traiter(noeud->chercher(i));
		}
	}

	else
	{
		// LOGIQUE DE SÉLECTION

		double distance = glm::dot(pointDansLeMonde_ - noeud->obtenirPositionRelative(), pointDansLeMonde_ - noeud->obtenirPositionRelative());
		distance = sqrt(distance);
		std::cout << "visite d'un noeudAbstrait" << " a la position : ";
		std::cout << noeud->obtenirPositionRelative().x << ","
			<< noeud->obtenirPositionRelative().y << ","
			<< noeud->obtenirPositionRelative().z << ",      Distance:" << distance << std::endl;

		if (distance < 30)
		{
			std::cout << "noeud Selectionne !" << std::endl;
			noeud->assignerSelection(true);
		}
		
	}

	return true;


}