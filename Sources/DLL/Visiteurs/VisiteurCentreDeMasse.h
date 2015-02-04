///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURCENTREDEMASSE_H__
#define __VISITEURS_VISITEURCENTREDEMASSE_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCentreDeMasse
/// @brief 
///
/// @author Philippe Carphin
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurCentreDeMasse : public VisiteurAbstrait
{
public:

	// Constructeur par paramètre : spécifiez l'angle, l'axe et le sens
	VisiteurCentreDeMasse();

	// Destructeur
	~VisiteurCentreDeMasse();
	
	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);

private:
	
	glm::dvec3 centreDeMasse_;
	
};


#endif //__VISITEURS_VISITEURCENTREDEMASSE_H__