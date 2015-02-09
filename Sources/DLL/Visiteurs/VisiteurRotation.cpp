////////////////////////////////////////////////
/// @file   VisiteurRotation.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurRotation.h"
#include "../Arbre/ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation()
///
/// Constructeur par défaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation(glm::dvec3 angles)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de rotation
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation(glm::dvec3 angles)
{
	angles_ = angles;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::~VisiteurRotation()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::~VisiteurRotation()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotation::traiter(ArbreRenduINF2990* noeud)
///
/// Cette fonction traite l'arbre de rendu pour effectuer une rotation sur ses enfants
/// selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotation::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i));
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotation::traiter(NoeudAbstrait* noeud)
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
bool VisiteurRotation::traiter(NoeudAbstrait* noeud)
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
		// LOGIQUE DE ROTATION
		if (noeud->estSelectionne())
			noeud->assignerRotation(angles_);
	}

	return true;
}