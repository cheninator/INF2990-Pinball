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
/// @brief Classe qui assigne une possibilit� � un noeud de l'arbre
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurPossibilite : public VisiteurAbstrait
{
public:

	/// Constructeur par d�faut
	VisiteurPossibilite();

	/// Destructeur
	~VisiteurPossibilite();

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__