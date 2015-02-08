///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCentreDeMasse.h
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
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
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

	// Constructeur
	VisiteurCentreDeMasse();

	// Destructeur
	~VisiteurCentreDeMasse();
	
	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

	glm::dvec3 obtenirCentreDeMasse()
	{
		return glm::dvec3{ centreDeMasse_.x / nbNoeuds_,
							centreDeMasse_.y / nbNoeuds_,
							centreDeMasse_.z / nbNoeuds_};
	}

private:
	
	glm::dvec3 centreDeMasse_;
	int nbNoeuds_;
	
};


#endif //__VISITEURS_VISITEURCENTREDEMASSE_H__