////////////////////////////////////////////////
/// @file   VisiteurAgrandissement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurAgrandissement.h"
#include "../Arbre/ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::VisiteurAgrandissement()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAgrandissement::VisiteurAgrandissement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::VisiteurAgrandissement(glm::dvec3 homothethie)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] homothethie : Le facteur d'agrandissement
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAgrandissement::VisiteurAgrandissement(glm::dvec3 homothethie)
{
	homothetie_ = homothethie;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::~VisiteurAgrandissement()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAgrandissement::~VisiteurAgrandissement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour effectuer un agrandissement
/// sur les objets selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i));
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudAbstrait* arbre)
///
/// Cette fonction traite les enfants de l'arbre de rendu pour effectuer 
/// un agrandissement
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudAbstrait* noeud)
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
		// LOGIQUE D'AGRANDISSEMENT
		noeud->assignerEchelle(homothetie_);
	}

	return true;
}
