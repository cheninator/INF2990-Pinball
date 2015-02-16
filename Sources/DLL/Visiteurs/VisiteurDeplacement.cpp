////////////////////////////////////////////////
/// @file   VisiteurDeplacement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement()
///
/// Constructeur par défaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 dep)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de deplacement
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 dep)
{
	deplacement_ = dep;
	estDansLaTable_ = false;
	estDuplication_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::~VisiteurDeplacement()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::~VisiteurDeplacement()
{

}


//////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour deplacer ses enfants selectionnés.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu à traiter.
///
/// @return Retourne toujours true.
///
//////////////////////////////////////////////////////////////////////////////////
bool VisiteurDeplacement::traiter(ArbreRenduINF2990* arbre)
{
	// Traiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table pour deplacer ses enfants selectionnés.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu à traiter.
///
/// @return Retourne toujours true.
///
//////////////////////////////////////////////////////////////////////////////////
bool VisiteurDeplacement::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnés de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu. Si ses enfants ont 
/// des enfants, ils seront aussi traités. Cette fonction retourne true pour dire 
/// que l'opération s'est faite correctement
///
/// @param[in] noeud : Noeud de l'arbre à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeplacement::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		glm::dvec3 nouvellePosition{ noeud->obtenirPositionRelative() + deplacement_ };
		noeud->assignerPositionRelative(nouvellePosition);

		if (estDansLaTable_ || !estDuplication_)
			noeud->assignerImpossible(false);
		else
			noeud->assignerImpossible(true);
	}

	return true;
}

void VisiteurDeplacement::setEstDansLaTable(bool b)
{
	estDansLaTable_ = b;
}

void VisiteurDeplacement::setEstDuplication(bool b)
{
	estDuplication_ = b;
}
