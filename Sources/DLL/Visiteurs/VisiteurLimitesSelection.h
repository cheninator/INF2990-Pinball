///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCentreDeMasse.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURLIMITESELECTION_H__
#define __VISITEURS_VISITEURLIMITESELECTION_H__

#include "VisiteurAbstrait.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCentreDeMasse
/// @brief Utilisé pour calculer le centre de masse des noeuds sélectionnés
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurLimitesSelection : public VisiteurAbstrait
{
public:

	/// Constructeur
	VisiteurLimitesSelection();

	/// Destructeur
	~VisiteurLimitesSelection();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

	double getXMin(){ return xMin_; };
	double getYMin(){ return yMin_; };


	double getXMax(){ return xMax_; };
	double getYMax(){ return yMax_; };

private:

	double xMin_, xMax_;
	double yMin_, yMax_;

};


#endif //__VISITEURS_VISITEURLIMITESELECTION_H__