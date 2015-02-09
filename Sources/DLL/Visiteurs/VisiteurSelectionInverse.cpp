////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurSelectionInverse.h"
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
VisiteurSelectionInverse::VisiteurSelectionInverse()
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
VisiteurSelectionInverse::VisiteurSelectionInverse(glm::dvec3 pointDansLeMonde, int valeurStencil)
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
VisiteurSelectionInverse::~VisiteurSelectionInverse()
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
bool VisiteurSelectionInverse::traiter(ArbreRenduINF2990* arbre)
{
	// Visiter les enfants de l'arbre
	//std::cout << "Visite d'un ArbreRenduINF2990 avec " << arbre->obtenirNombreEnfants() << " enfants" << std::endl;
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		//std::cout << "appel de accepterVisiteur sur l'enfant " << i << " de l'ArbreRendu2990" << std::endl;
		arbre->getEnfant(i)->accepterVisiteur(this);

		// Puisque getEnfant(i) retourne un NoeudAbstrait*, traiter va faire le traiter de NoeudAbstrait donc ce qui suit ne marche pas
		// std::cout << "appel de traiter sur l'enfant " << i << " de l'ArbreRendu2990" << std::endl;
		// traiter(arbre->getEnfant(i));

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
bool VisiteurSelectionInverse::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnés de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		//std::cout << "appel de accepterVisiteur sur l'enfant " << i << " de la table" << std::endl;
		table->getEnfant(i)->accepterVisiteur(this);
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
bool VisiteurSelectionInverse::traiter(NoeudAbstrait* noeud)
{
	double distance = glm::dot(pointDansLeMonde_ - noeud->obtenirPositionRelative(), pointDansLeMonde_ - noeud->obtenirPositionRelative());
	distance = sqrt(distance);
	std::cout << "VisiteurSelectionInverse::traiter() d'un noeudAbstrait avec identifiant " << noeud->getNumero() << std::endl;
	std::cout << noeud->obtenirPositionRelative().x << ","<< noeud->obtenirPositionRelative().y << "," << noeud->obtenirPositionRelative().z << ",      Distance:" << distance << std::endl;

	if (valeurStencil_ == noeud->getNumero() && noeud->estSelectionnable() /*&& noeud->estModifiable()*/)
	{
		std::cout << "Noeud de type " << noeud->getType() << " selectionne avec CTRL CLICK " << std::endl;
		if (noeud->estSelectionne())
		{
			noeud->assignerSelection(false);
		}
		else
		{
			noeud->assignerSelection(true);
		}
	}

		if (noeud->estSelectionne())
		{
			nbObjetsSelectionne_++;
		}

	// voir requi 3.2.4.2 

	return true;

}

