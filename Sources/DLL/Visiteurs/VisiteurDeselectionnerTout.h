///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeselectionnerTout.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDESELECTIONNERTOUT_H__
#define __VISITEURS_VISITEURDESELECTIONNERTOUT_H__

#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeselectionnerTout
/// @brief Classe pour désélectionner tous les objets de la table de rendu.
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDeselectionnerTout : public VisiteurAbstrait
{
public:

	/// Constructeur par défaut : aucun déplacement
	VisiteurDeselectionnerTout();

	/// Destructeur
	~VisiteurDeselectionnerTout();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* table);


private:

};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__