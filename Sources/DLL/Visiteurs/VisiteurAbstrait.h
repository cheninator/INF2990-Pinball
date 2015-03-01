///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author The Ballers
/// @date 2015-01-26
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////

/** @defgroup Visiteur Visiteur
*	@ingroup Noyau
*/

#ifndef __VISITEURS_VISITEURABSTRAIT_H__
#define __VISITEURS_VISITEURABSTRAIT_H__

class NoeudAbstrait;
class ArbreRenduINF2990;
class NoeudTable;
class NoeudMur;
class NoeudGenerateurBille;
class NoeudPortail;
class NoeudPaletteG;
class NoeudPaletteD;


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
///
/// @brief Interface du patron Visiteur
///
/// Classe de base de laquelle derivent les visiteurs.
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurAbstrait
{
public:

	/// Constructeur par defaut
	VisiteurAbstrait(){};

	/// Classe abstraite
	virtual ~VisiteurAbstrait(){};

	/// Traiter une operation sur l'arbre de rendu
	virtual bool traiter(ArbreRenduINF2990* arbre) { return false; };

	/// Traiter une operation sur la table de l'arbre de rendu
	virtual bool traiter(NoeudTable* noeud) { return false; };

	/// Traiter une operation sur les noeuds abstraits de l'arbre de rendu
	virtual bool traiter(NoeudAbstrait* noeud){ return false; };

	/// Si traiter(NoeudMur* ) n'est pas reimplemente, appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST reimplementee.
	virtual bool traiter(NoeudMur* noeud){ return traiter((NoeudAbstrait*)noeud); };

	/// Si traiter(NoeudGenerateurBille*) n'est pas reimplemente, appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST reimplementee.
	virtual bool traiter(NoeudGenerateurBille* noeud){ return traiter((NoeudAbstrait*)noeud); };

	/// Si traiter(NoeudPortail*) n'est pas reimplemente, appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST reimplementee.
	virtual bool traiter(NoeudPortail* noeud){ return traiter((NoeudAbstrait*)noeud); };

	/// Si traiter(NoeudPaletteG*) n'est pas reimplemente, appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST reimplementee.
	virtual bool traiter(NoeudPaletteG* noeud){ return traiter((NoeudAbstrait*)noeud); };

	/// Si traiter(NoeudPaletteD*) n'est pas reimplemente, appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST reimplementee.
	virtual bool traiter(NoeudPaletteD* noeud){ return traiter((NoeudAbstrait*)noeud); };

};


#endif // __VISITEURS_VISITEURABSTRAIT_H__

