////////////////////////////////////////////////
/// @file   VisiteurSelectionInverseMultiple.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurSelectionInverseMultiple.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionInverseMultiple::VisiteurSelectionInverseMultiple()
///
/// Constructeur par defaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionInverseMultiple::VisiteurSelectionInverseMultiple()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionInverseMultiple::VisiteurSelectionInverseMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] selectionBasGauche : Le vecteur de selection
/// @param[in] selectionHautDroit : Le vecteur de selection
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionInverseMultiple::VisiteurSelectionInverseMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit)
:nbObjetsSelectionne_{ 0 }
{
	selectionBasGauche_ = selectionBasGauche;
	selectionHautDroit_ = selectionHautDroit;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelectionInverseMultiple::~VisiteurSelectionInverseMultiple()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelectionInverseMultiple::~VisiteurSelectionInverseMultiple()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionInverseMultiple::traiter(ArbreRenduINF2990* arbre)
///
/// @brief Cette fonction traite l'arbre de rendu pour selectionner ses enfants.
///
/// @param[in] arbre Noeud arbre a traiter
///
/// @return Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionInverseMultiple::traiter(ArbreRenduINF2990* arbre)
{
	// Traiter les enfants de l'arbre de rendu
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionInverseMultiple::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionInverseMultiple::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnes de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelectionInverseMultiple::traiter(NoeudAbstrait* noeud)
///
///	Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants 
/// ont des enfants, ils seront aussi traites. Cette fonction retourne true 
/// si l'operation s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSelectionInverseMultiple::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionnable())
	{
		// Obtenir origine du noeud
		glm::dvec3 origine = noeud->obtenirPositionRelative();

		// Obtenir les 4 coins de la boite englobante
		glm::dvec3 v1, v2, v3, v4;
		noeud->obtenirVecteursBoite(v1, v2, v3, v4);

		// Definir leur position dans le monde
		v1.x = v1.x + origine.x;
		v1.y = v1.y + origine.y;
		v2.x = v2.x + origine.x;
		v2.y = v2.y + origine.y;
		v3.x = v3.x + origine.x;
		v3.y = v3.y + origine.y;
		v4.x = v4.x + origine.x;
		v4.y = v4.y + origine.y;

		bool estAInverser = false;

		// Verifier si un des coin est a l'interieur du rectangle elastique
		if (utilitaire::DANS_LIMITESXY(v1.x, selectionBasGauche_.x, selectionHautDroit_.x,
			v1.y, selectionBasGauche_.y, selectionHautDroit_.y) ||
			utilitaire::DANS_LIMITESXY(v2.x, selectionBasGauche_.x, selectionHautDroit_.x,
			v2.y, selectionBasGauche_.y, selectionHautDroit_.y) ||
			utilitaire::DANS_LIMITESXY(v3.x, selectionBasGauche_.x, selectionHautDroit_.x,
			v3.y, selectionBasGauche_.y, selectionHautDroit_.y) ||
			utilitaire::DANS_LIMITESXY(v4.x, selectionBasGauche_.x, selectionHautDroit_.x,
			v4.y, selectionBasGauche_.y, selectionHautDroit_.y))
		{
			estAInverser = true;
		}
		else
		{
			glm::dvec3 selectionHautGauche(selectionBasGauche_.x, selectionHautDroit_.y, 0.0);
			glm::dvec3 selectionBasDroit(selectionHautDroit_.x, selectionBasGauche_.y, 0.0);

			// Verifier si un des coin du rectangle elastique est a l'interieur de la boite du noeud
			if (noeud->pointEstDansBoite(selectionBasGauche_) ||
				noeud->pointEstDansBoite(selectionHautDroit_) ||
				noeud->pointEstDansBoite(selectionHautGauche) ||
				noeud->pointEstDansBoite(selectionBasDroit))
			{
				estAInverser = true;
			}
			else
			{
				// Verifier s'il y a intersection entre un des segments du carre elastique
				// et un des cotes de la boite englobante du noeud
				if (utilitaire::intersectionDeuxSegments(selectionBasGauche_, selectionHautGauche, v1, v2) ||
					utilitaire::intersectionDeuxSegments(selectionBasGauche_, selectionHautGauche, v2, v3) ||
					utilitaire::intersectionDeuxSegments(selectionBasGauche_, selectionHautGauche, v3, v4) ||
					utilitaire::intersectionDeuxSegments(selectionBasGauche_, selectionHautGauche, v4, v1) ||
					utilitaire::intersectionDeuxSegments(selectionHautGauche, selectionHautDroit_, v1, v2) ||
					utilitaire::intersectionDeuxSegments(selectionHautGauche, selectionHautDroit_, v2, v3) ||
					utilitaire::intersectionDeuxSegments(selectionHautGauche, selectionHautDroit_, v3, v4) ||
					utilitaire::intersectionDeuxSegments(selectionHautGauche, selectionHautDroit_, v4, v1) ||
					utilitaire::intersectionDeuxSegments(selectionHautDroit_, selectionBasDroit, v1, v2) ||
					utilitaire::intersectionDeuxSegments(selectionHautDroit_, selectionBasDroit, v2, v3) ||
					utilitaire::intersectionDeuxSegments(selectionHautDroit_, selectionBasDroit, v3, v4) ||
					utilitaire::intersectionDeuxSegments(selectionHautDroit_, selectionBasDroit, v4, v1) ||
					utilitaire::intersectionDeuxSegments(selectionBasDroit, selectionBasGauche_, v1, v2) ||
					utilitaire::intersectionDeuxSegments(selectionBasDroit, selectionBasGauche_, v2, v3) ||
					utilitaire::intersectionDeuxSegments(selectionBasDroit, selectionBasGauche_, v3, v4) ||
					utilitaire::intersectionDeuxSegments(selectionBasDroit, selectionBasGauche_, v4, v1))
				{
					estAInverser = true;
				}
			}
		}

		if (estAInverser)
		{
			// std::cout << "Noeud de type " << noeud->getType() << " selection inverse " << std::endl;
			noeud->assignerSelection(!noeud->estSelectionne());
		}

		if (noeud->estSelectionne())
		{
			nbObjetsSelectionne_++;
		}
	}

	return true;
}