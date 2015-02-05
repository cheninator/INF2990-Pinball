////////////////////////////////////////////////
/// @file   VisiteurRotationPoint.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurRotationPoint.h"
#include "../Arbre/ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::VisiteurRotationPoint()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::VisiteurRotationPoint()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::VisiteurRotationPoint(glm::dvec3 dep)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de rotation
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::VisiteurRotationPoint(glm::dvec3 angles)
{
	angles_ = angles;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::~VisiteurRotationPoint()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::~VisiteurRotationPoint()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(ArbreRenduINF2990* noeud)
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
bool VisiteurRotationPoint::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i));
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(NoeudAbstrait* noeud)
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
bool VisiteurRotationPoint::traiter(NoeudAbstrait* noeud)
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
		if (noeud->estSelectionne());
		noeud->assignerRotation(angles_);
	}

	return true;
}