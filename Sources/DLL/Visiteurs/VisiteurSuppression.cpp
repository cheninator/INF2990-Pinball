////////////////////////////////////////////////
/// @file   VisiteurSuppression.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurSuppression.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::VisiteurSuppression()
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::VisiteurSuppression()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::~VisiteurSuppression()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::~VisiteurSuppression()
{
	delete arbreTemp;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSuppression::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour supprimer ses enfants
/// selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement, ou false si on ne permet pas la sauvegarde
///
/// @return Retourne true ou false
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSuppression::traiter(ArbreRenduINF2990* arbre)
{
	arbreTemp = arbre;

	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	arbreTemp = nullptr;

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSuppression::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement.
///
/// @param[in] table : Le noeud de type Table à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSuppression::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnés de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de la table
		table->getEnfant(i)->accepterVisiteur(this);
	}

	for (unsigned int i = 0; i < suppression.size(); i++)
	{
		arbreTemp->effacer(suppression[i]);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSuppression::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi traités. Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement.
///
/// @param[in] noeud : Noeud de l'arbre à traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSuppression::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		if ((noeud->obtenirType() == "portail") && (noeud->getTwin() != nullptr))
			suppression.push_back(noeud->getTwin());

		suppression.push_back(noeud);
	}

	return true;
}