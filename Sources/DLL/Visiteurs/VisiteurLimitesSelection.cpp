////////////////////////////////////////////////
/// @file   VisiteurLimitesSelection.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurLimitesSelection.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurLimitesSelection::VisiteurLimitesSelection()
///
/// Constructeur qui initialise les valeurs par defaut
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
/// @fn VisiteurLimitesSelection::~VisiteurLimitesSelection()
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
/// @fn bool VisiteurLimitesSelection::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] arbre : L'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurLimitesSelection::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurLimitesSelection::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement
///
/// @param[in] table : La table a traiter.
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
/// @fn bool VisiteurLimitesSelection::traiter(NoeudAbstrait* noeud)
/// @brief Calcule la limite de la selection.
///
/// @param[in] noeud : Le noeud a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurLimitesSelection::traiter(NoeudAbstrait* noeud)
{
	glm::dvec3 position{ noeud->obtenirPositionRelative() };

	if (noeud->estSelectionne())
	{	
		std::vector<glm::dvec3> boite = noeud->obtenirVecteursEnglobants();

		if (boite.size() == 1)
		{
			double rayon = boite[0].x;
			boite.push_back({ -rayon, 0, 0 });
			boite.push_back({ 0, rayon, 0 });
			boite.push_back({ 0, -rayon, 0 });
		}

		for (int i = 0; i < boite.size(); i++)
		{
			boite[i] += position;

			if (boite[i].x > xMax_)
				xMax_ = boite[i].x;

			if (boite[i].x < xMin_)
				xMin_ = boite[i].x;

			if (boite[i].y > yMax_)
				yMax_ = boite[i].y;

			if (boite[i].y < yMin_)
				yMin_ = boite[i].y;
		}
	}

	return true;
}