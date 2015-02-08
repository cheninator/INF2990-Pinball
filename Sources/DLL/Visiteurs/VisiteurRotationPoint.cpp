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
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>


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
/// @param[in] dev : Le vecteur des rotation
///
/// @param[in] centreRotation : Point autour duquel tourner les objets
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::VisiteurRotationPoint(glm::dvec3 angles, glm::dvec3 centreRotation)
:centreRotation_{ centreRotation }
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
		noeud->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(NoeudTable* noeud)
///
/// Cette fonction traite la table pour effectuer une rotation sur ses enfants
/// selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotationPoint::traiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->getEnfant(i)->accepterVisiteur(this);
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
		if (noeud->estSelectionne() /*&& noeud->estModifiable()*/ )
		{
			// LOGIQUE DE ROTATION AUTOUR D'UN POINT
			// Changer la position du noeud
			glm::dvec3 positionInitiale = noeud->obtenirPositionRelative();
			glm::dvec3 vecteurInitial = positionInitiale - centreRotation_;
			double angleEnRadian = -angles_[2] * 2 * 3.14156 / 360;
			glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
												glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
												glm::dvec3{       0.0      ,       0.0        , 1.0 } };

			glm::dvec3 vecteurFinal = transform * vecteurInitial;
			glm::dvec3 positionFinale = centreRotation_ + vecteurFinal;

			noeud->assignerPositionRelative(positionFinale);

			// Changer l'orientation du noeud
			noeud->assignerRotation(angles_);
		}

	return true;
}