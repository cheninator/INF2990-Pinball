///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurPossibilite.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURPOSSSIBILITE_H__
#define __VISITEURS_VISITEURPOSSSIBILITE_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurPossibilite
/// @brief Classe qui assigne une possibilite a un noeud de l'arbre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurPossibilite : public VisiteurAbstrait
{
public:

	/// Constructeur par defaut
	VisiteurPossibilite();

	/// Destructeur
	~VisiteurPossibilite();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__