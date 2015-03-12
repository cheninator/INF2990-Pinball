////////////////////////////////////////////////
/// @file   JoueurVirtuel.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Global
////////////////////////////////////////////////

#include "JoueurVirtuel.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include "../Arbre/Noeuds/NoeudPaletteG.h"
#include "../Arbre/Noeuds/NoeudPaletteD.h"
#include "../QuadTree/QuadTree.h"
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"
#include "Gl/gl.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn JoueurVirtuel::JoueurVirtuel()
///
/// 
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
JoueurVirtuel::JoueurVirtuel(QuadTree* quad)
{
	quad_ = quad;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JoueurVirtuel::~JoueurVirtuel()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
JoueurVirtuel::~JoueurVirtuel()
{
	quad_ = nullptr;
}


bool JoueurVirtuel::traiter(NoeudPaletteG* noeud)
{
	// Retourne les objets qui sont dans le même quad que la palette
	std::list<NoeudAbstrait*> resultat = quad_->retrieve((NoeudAbstrait*)noeud);
	std::list<NoeudAbstrait*>::iterator iter;

	for (iter = resultat.begin(); iter != resultat.end(); iter++)
	{
		if ((*iter)->obtenirType() == "bille")
		{
			glm::dvec3 positionPalette = noeud->obtenirPositionRelative();
			glm::dvec3 positionBille = (*iter)->obtenirPositionRelative();
			glm::dvec3 vecteur = positionBille - positionPalette;
			double distance = glm::length(vecteur);

			double angleEnRadian = noeud->obtenirAngleZOriginal() * 2 * 3.1415926535897932384626433832795 / 360;
			glm::dvec3 directionPalette = { -cos(angleEnRadian), -sin(angleEnRadian), 0 }; // Une palette pas tournee a un axe { - 1, 0, 0}
			glm::dvec3 vecteurProjete = glm::proj(vecteur, directionPalette);
			glm::dvec3 vecteurNormal = vecteur - vecteurProjete;

			double distanceProjetee = glm::length(vecteurProjete);
			double distanceNormale = glm::length(vecteurNormal);

			// positionBille.y > pente * positionBille.x + b <====> la bille est au dessus de la droite definie par la palette au repos.
			if (noeud->fonctionDroitePalette(*iter) > 0		// << vrai si on la bille est au dessus de la droite definie par la palette. C<est ce qui fait que les palettes n'activent pas par en dessous.
				&& positionBille.x < positionPalette.x + 80 // << essayer de remplacer par glm::length(glm::proj(vecteur, directionPalette)) < longueurPalette
				&& positionBille.y < positionPalette.y + 10
				)
				noeud->activer();
		}

	}

	return true;

}

bool JoueurVirtuel::traiter(NoeudPaletteD* noeud)
{
	return false;
}
