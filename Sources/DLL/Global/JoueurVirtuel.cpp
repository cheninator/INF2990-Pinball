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
#include "Gl/gl.h"
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"


////////////////////////////////////////////////////////////////////////
///
/// @fn JoueurVirtuel::JoueurVirtuel()
///
/// Constructeur par défaut
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
	billes_.clear();
	palettesDroite_.clear();
	palettesGauche_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JoueurVirtuel::jouer(std::vector<NoeudAbstrait*> listeBilles)
///
///	Méthode qui implémente la logique du comportement que doit adopter
///	le joueur virtuel.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void JoueurVirtuel::jouer(const std::vector<NoeudAbstrait*>& listeBilles)
{
	billes_.clear();
	billes_ = listeBilles;
	bool detecter = false;

	/// Traiter les palettes gauches
	for (unsigned int i = 0; i < palettesGauche_.size() && !detecter; i++)
		detecter = palettesGauche_[i]->accepterJoueurVirtuel(this);
	
	/// Activer toutes les palettes gauches
	if (detecter)
	{
		for (unsigned int j = 0; j < palettesGauche_.size(); j++)
			palettesGauche_[j]->activerAI();

		detecter = false;
	}

	/// Traiter les palettes droites
	for (unsigned int i = 0; i < palettesDroite_.size() && !detecter; i++)
		detecter = palettesDroite_[i]->accepterJoueurVirtuel(this);

	/// Activer les palettes droites
	if (detecter)
	{
		for (unsigned int j = 0; j < palettesGauche_.size(); j++)
			palettesDroite_[j]->activerAI();
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool JoueurVirtuel::traiter(NoeudPaletteG* noeud)
///
///	Méthode qui retourne vrai lorsque la palette passé en paramètre
///	detecte une bille proche de sa position. Faux autrement
///
/// @return True ou false selon si la palette detecte une bille proche
///
////////////////////////////////////////////////////////////////////////
bool JoueurVirtuel::traiter(NoeudPaletteG* noeud)
{
	/// Traiter toutes les billes que connait le joueur virtuel
	for (unsigned int i = 0; i < billes_.size(); i++)
	{
		if (noeud->estActiveeParBille(billes_[i]))
			return true;
	}

	return false;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool JoueurVirtuel::traiter(NoeudPaletteD* noeud)
///
///	Méthode qui retourne vrai lorsque la palette passé en paramètre
///	detecte une bille proche de sa position. Faux autrement
///
/// @return True ou false selon si la palette detecte une bille proche
///
////////////////////////////////////////////////////////////////////////
bool JoueurVirtuel::traiter(NoeudPaletteD* noeud)
{
	/// Traiter toutes les billes que connait le joueur virtuel
	for (unsigned int i = 0; i < billes_.size(); i++)
	{
		if (noeud->estActiveeParBille(billes_[i]))
			return true;
	}

	return false;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool JoueurVirtuel::assignerPalettes(const std::set<NoeudPaletteG*>& gauche, const std::set<NoeudPaletteD*>& droite)
///
///	Méthode qui assigne au joueur virtuel sa liste de palette
///
/// @param[in] gauche, droite : ses palettes gauches et droites
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
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