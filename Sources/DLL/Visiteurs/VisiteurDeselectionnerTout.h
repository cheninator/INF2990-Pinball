///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDESELECTIONNERTOUT_H__
#define __VISITEURS_VISITEURDESELECTIONNERTOUT_H__

#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Classe pour désélectionner tous les objets de la table de rendu
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurDeselectionnerTout : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : aucun déplacement
	VisiteurDeselectionnerTout();

	// Destructeur
	~VisiteurDeselectionnerTout();

	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);


private:


};


#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__