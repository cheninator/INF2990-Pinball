///////////////////////////////////////////////////////////////////////////////
/// @file JoueurVirtuel.h
/// @author The Ballers
/// @date 2015-01-26
/// @version 1.0
///
/// @ingroup Global
///////////////////////////////////////////////////////////////////////////////

/** @defgroup Global
*	@ingroup Noyau
*/

#ifndef __JOUEURVIRTUEL_H__
#define __JOUEURVIRTUEL_H__

#include <vector>
#include <set>

class NoeudAbstrait;
class NoeudPaletteG;
class NoeudPaletteD;

///////////////////////////////////////////////////////////////////////////
/// @class JoueurVirtuel
///
/// @brief Cette classe est issu du patron Visiteur. Elle représente le 
///		   concept d'intelligence artificielle pour le 2eme joueur
///
/// Classe de base de laquelle derivent les visiteurs.
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Global
///////////////////////////////////////////////////////////////////////////
class JoueurVirtuel
{
public:

	/// Constructeur par defaut
	JoueurVirtuel();

	/// Destructeur
	virtual ~JoueurVirtuel();

	/// Comportement du joueur virtuel
	virtual void jouer(const std::vector<NoeudAbstrait*>& listeBilles);

	/// Traitement des noeuds abstraits
	virtual bool traiter(NoeudAbstrait* noeud) { return false; };

	/// Traiter une operation sur les palettes gauches
	virtual bool traiter(NoeudPaletteG* noeud);

	/// Traiter une operation sur les palettes droites
	virtual bool traiter(NoeudPaletteD* noeud);

	/// Assigner les palettes du joueur virtuel
	virtual void assignerPalettes(const std::set<NoeudPaletteG*>& gauche, const std::set<NoeudPaletteD*>& droite);

private:

	/// Ce que le joueur virtuel doit connaitre pour prendre ses decisions
	std::vector<NoeudPaletteG*> palettesGauche_;
	std::vector<NoeudPaletteD*> palettesDroite_;
	std::vector<NoeudAbstrait*> billes_;

};


#endif // __VISITEURS_VISITEURABSTRAIT_H__