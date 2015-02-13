///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeselectionnerTout.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURPOSSSIBILITE_H__
#define __VISITEURS_VISITEURPOSSSIBILITE_H__

#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeselectionnerTout
/// @brief Classe pour désélectionner tous les objets de la table de rendu.
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurPossibilite : public VisiteurAbstrait
{
public:

	/// Constructeur par défaut : aucun déplacement
	VisiteurPossibilite();

	/// Destructeur
	~VisiteurPossibilite();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* table);


private:

};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__