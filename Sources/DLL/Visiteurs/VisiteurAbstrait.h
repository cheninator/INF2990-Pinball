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


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
///
/// @brief Interface du patron Visiteur
///
/// Classe de base de laquelle dérivent les visiteurs.
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurAbstrait
{
public:

	/// Constructeur par défaut
	VisiteurAbstrait(){};

	/// Classe abstraite
	virtual ~VisiteurAbstrait(){};

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre) { return false; };
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* noeud) { return false; };
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud){ return false; };
	/// Si traiter(NoeudMur*) n'est pas réimplémenté, on va appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST réimplémentée.
	virtual bool traiter(NoeudMur* noeud){ return traiter((NoeudAbstrait*)noeud); };
	/// Si traiter(NoeudGenerateurBille*) n'est pas réimplémenté, on va appeler celui de NoeudAbstrait qui appelle traiter(NoeudAbstrait*), qui EST réimplémentée.
	virtual bool traiter(NoeudGenerateurBille* noeud){ return traiter((NoeudAbstrait*)noeud); };

};


#endif // __VISITEURS_VISITEURABSTRAIT_H__

