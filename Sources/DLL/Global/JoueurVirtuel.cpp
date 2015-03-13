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
JoueurVirtuel::JoueurVirtuel()
{

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
	palettesDroite_.clear();
	palettesGauche_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JoueurVirtuel::jouer(std::vector<NoeudAbstrait*> listeBilles)
///
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void JoueurVirtuel::jouer(const std::vector<NoeudAbstrait*>& listeBilles)
{
	billes_ = listeBilles;
	bool detecter = false;

	/// Traiter les palettes gauches
	for (unsigned int i = 0; i < palettesGauche_.size() && !detecter; i++)
		detecter = palettesGauche_[i]->accepterJoueurVirtuel(this);
	
	/// Activer toutes les palettes gauches
	if (detecter)
	{
		for (unsigned int j = 0; j < palettesGauche_.size(); j++)
			palettesGauche_[j]->activer();

		detecter = false;
	}

	/// Traiter les palettes droites
	for (unsigned int i = 0; i < palettesDroite_.size() && !detecter; i++)
		palettesDroite_[i]->accepterJoueurVirtuel(this);

	/// Activer les palettes droites
	if (detecter)
	{
		for (unsigned int j = 0; j < palettesGauche_.size(); j++)
			palettesDroite_[j]->activer();
	}

	/// Traiter d'autres collisions potentiel
	/// TO DO : Gerer les collisions avec d'autres objets qu'une bille

}

bool JoueurVirtuel::traiter(NoeudPaletteG* noeud)
{
	if (noeud->obtenirInitial())
		noeud->assignerAngleOriginal(noeud->obtenirRotation().z);

	for (unsigned int i = 0; i < billes_.size(); i++)
	{
		glm::dvec3 positionPalette = noeud->obtenirPositionRelative();
		glm::dvec3 positionBille = billes_[i]->obtenirPositionRelative();
		positionPalette.z = 0.0; // Les positions utilisees ici doivent etre en 2D
		positionBille.z = 0.0; // Les positions utilisees ici doivent etre en 2D

		glm::dvec3 vecteur = positionBille - positionPalette;
		double distance = glm::length(vecteur);

		double angleEnRadian = noeud->obtenirAngleZOriginal()* utilitaire::PI_180;
		glm::dvec3 directionPalette = { -cos(angleEnRadian), -sin(angleEnRadian), 0 }; // Une palette pas tournee a un axe { - 1, 0, 0}
		glm::dvec3 vecteurProjete = glm::proj(vecteur, directionPalette);
		glm::dvec3 vecteurNormal = vecteur - vecteurProjete;
		std::vector<glm::dvec3> boite = noeud->obtenirVecteursEnglobants();
		double longueurPalette = boite[0].x - boite[2].x;

		double distanceProjetee = glm::length(vecteurProjete);
		double distanceNormale = glm::length(vecteurNormal);
		glm::dvec3 produitVectoriel;

		if (noeud->fonctionDroitePaletteOriginale(billes_[i]) > 0// << vrai si on la bille est au dessus de la droite definie par la palette. C<est ce qui fait que les palettes n'activent pas par en dessous.
			&& glm::dot(directionPalette, vecteur) < 0
			&& asin(glm::length(produitVectoriel) / glm::length(vecteur)) < sin(60 * utilitaire::PI_180)
			&& distance < longueurPalette
			)
			return true;
	}

	return false;

}

bool JoueurVirtuel::traiter(NoeudPaletteD* noeud)
{
	return false;
}

void JoueurVirtuel::assignerPalettes(const std::set<NoeudPaletteG*>& gauche, const std::set<NoeudPaletteD*>& droite)
{
	palettesGauche_.clear();
	palettesDroite_.clear();

	std::set<NoeudPaletteG*>::iterator iterG = gauche.begin();
	std::set<NoeudPaletteD*>::iterator iterD = droite.begin();

	for (; iterG != gauche.end(); iterG++)
		palettesGauche_.push_back(*iterG);

	for (; iterD != droite.end(); iterD++)
		palettesDroite_.push_back(*iterD);

}
