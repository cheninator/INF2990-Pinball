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
void JoueurVirtuel::jouer(const std::vector<NoeudAbstrait*>& listeBilles, const std::set<NoeudPaletteG*>& listePalettesGauches, const std::set<NoeudPaletteD*>& listePalettesDroites, float temps)
{
	// Le joueur pourrait posséder des pointeurs vers listePalettesGJ2_ et listePalettesDJ2_ de facadeModele.
	billes_.clear();
	billes_ = listeBilles;
	bool detecter = false;

	/// Traiter les palettes gauches
	// Si le bouton n'est pas pesé, faire la vérification habituelle
	if (!boutonGauche_)
	{
		if (timerGauche_ > 0)
			timerGauche_ -= temps;
		else
		for (NoeudPaletteG* paletteGauche : listePalettesGauches)
		if (paletteGauche->accepterJoueurVirtuel(this))
		{
			FacadeModele::obtenirInstance()->activerPalettesGJ2();
			timerGauche_ = 0.25;
			boutonGauche_ = true;
			break;
		}
	}
	else
	{
		// Si le bouton EST pesé, compter du temps jusqu'à une certaine valeur et relacher le bouton après cette valeur.
		if (timerGauche_ > 0)
			timerGauche_ -= temps;
		else
		{
			FacadeModele::obtenirInstance()->desactiverPalettesGJ2();
			timerGauche_ = 0.4f;
			boutonGauche_ = false;
		}
	}
	// Même chose pour le bouton de droite.
	if (!boutonDroit_)
	{
		if (timerDroit_ > 0)
			timerDroit_ -= temps;
		else
		for (NoeudPaletteD* paletteDroite : listePalettesDroites)
		if (paletteDroite->accepterJoueurVirtuel(this))
		{
			FacadeModele::obtenirInstance()->activerPalettesDJ2();
			timerDroit_ = 0.25;
			boutonDroit_ = true;
			break;
		}
	}
	else
	{
		if (timerDroit_ > 0)
			timerDroit_ -= temps;
		else
		{
			FacadeModele::obtenirInstance()->desactiverPalettesDJ2();
			timerDroit_ = 0.4f;
			boutonDroit_ = false;
		}
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