///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author The Ballers
/// @date 2015-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURABSTRAIT_H__
#define __VISITEURS_VISITEURABSTRAIT_H__

class NoeudAbstrait;
class ArbreRenduINF2990;


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
///
/// @brief Interface du patron Visiteur
///
///        Dérivez les visiteurs concrets de cette classe de base
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurAbstrait
{
public:

	// Constructeur par défaut
	VisiteurAbstrait(){};

	// Classe abstraite
	virtual ~VisiteurAbstrait(){};

	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre) { return false; };
	virtual bool traiter(NoeudAbstrait* noeud) { return false; };

};


#endif // __VISITEURS_VISITEURABSTRAIT_H__

