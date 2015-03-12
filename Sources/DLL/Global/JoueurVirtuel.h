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

class NoeudAbstrait;
class NoeudPaletteG;
class NoeudPaletteD;
class QuadTree;

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
	JoueurVirtuel(QuadTree* quad);

	/// Destructeur
	virtual ~JoueurVirtuel();

	/// Traiter une operation sur les palettes gauches
	virtual bool traiter(NoeudPaletteG* noeud);

	/// Traiter une operation sur les palettes droites
	virtual bool traiter(NoeudPaletteD* noeud);

private:

	QuadTree* quad_;

};


#endif // __VISITEURS_VISITEURABSTRAIT_H__