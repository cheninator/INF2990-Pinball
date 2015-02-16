////////////////////////////////////////////////
/// @file   VisiteurRotationPoint.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurRotationPoint.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::VisiteurRotationPoint()
///
/// Constructeur par defaut (Vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::VisiteurRotationPoint()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotationPoint::VisiteurRotationPoint(glm::dvec3 angles, glm::dvec3 centreRotation)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] dev : Le vecteur des rotations.
///
/// @param[in] centreRotation : Point autour duquel tournent les objetss
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
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotationPoint::~VisiteurRotationPoint()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour effectuer une rotation sur 
///	les enfants selectionnes. Cette fonction retourne true pour dire que 
/// l'operation s'est faite correctement.
///
/// @param[in] arbre : L'arbre de rendu a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotationPoint::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(NoeudTable* table)
///
/// Cette fonction traite la table pour effectuer une rotation sur ses enfants
/// selectionnes. Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotationPoint::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurRotationPoint::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu. Si ses enfants ont 
/// des enfants, ils seront aussi traites. Cette fonction retourne true 
/// si l'operation s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurRotationPoint::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
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
		noeud->assignerRotation(noeud->obtenirRotation().y == 0 ? angles_ : -angles_);
	}

	return true;
}