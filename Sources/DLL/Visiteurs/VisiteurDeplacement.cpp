////////////////////////////////////////////////
/// @file   VisiteurDeplacement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
#include "../Arbre/ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement()
///
/// VIDE
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
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de deplacement
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 dep)
{
	deplacement_ = dep;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::~VisiteurDeplacement()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::~VisiteurDeplacement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour deplacer ses enfants
/// selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeplacement::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i));
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(NoeudAbstrait* noeud)
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
bool VisiteurDeplacement::traiter(NoeudAbstrait* noeud)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Si l'élément est une table, visiter ses enfants
	if (nom == "table")
	{
		// Traiter les enfants selectionnés de la table
		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			if (noeud->chercher(i)->estSelectionne())
				traiter(noeud->chercher(i));
		}
	}

	else
	{
		// LOGIQUE DE DÉPLACEMENT
		noeud->assignerPositionRelative(deplacement_);
	}

	return true;
}
