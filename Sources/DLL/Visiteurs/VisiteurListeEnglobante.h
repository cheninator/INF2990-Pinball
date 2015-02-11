///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeselectionnerTout.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURLISTEENGLOBANTE_H__
#define __VISITEURS_VISITEURLISTEENGLOBANTE_H__

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
class VisiteurListeEnglobante : public VisiteurAbstrait
{
public:

	/// Constructeur par défaut : aucun déplacement
	VisiteurListeEnglobante();

	/// Destructeur
	~VisiteurListeEnglobante();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* table);


private:

	std::vector<glm::dvec3> pointsEnglobant_;
};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__