////////////////////////////////////////////////
/// @file   VisiteurSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurPossibilite.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
///
/// Constructeur par défaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurPossibilite::VisiteurPossibilite()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurPossibilite::~VisiteurPossibilite()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// faite correctement.
///
/// @param[in] arbre : L'arbre de rendu à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurPossibilite::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurPossibilite::traiter(NoeudTable* table)
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
/// Ce visiteur désélectionne un noeud.
///
/// @param[in] noeud : Noeud de l'arbre à traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurPossibilite::traiter(NoeudAbstrait* noeud)
{
	glm::dvec3 coinsEnglobant[4];
	glm::dvec3 position = noeud->obtenirPositionRelative();
	glm::dvec3 point;
	noeud->obtenirVecteursBoite(coinsEnglobant[0], coinsEnglobant[1], coinsEnglobant[2], coinsEnglobant[3]);
	
	for (int i = 0; i < 4; i++)
	{
		point = position + coinsEnglobant[i];
		if (!(108 < point.x && point.x < 272
			&& -190 < point.y && point.y < 96)) // Si le point n'est pas dans la table, alors le noeud est impossible.
		{
			noeud->assignerImpossible(true);
			return true; // Si on trouve un point illégal, le noeud est impossible, on a fini.
		}
	}

	// Si tous les points ont passé le test,
	noeud->assignerImpossible(false);

	return true;
}

