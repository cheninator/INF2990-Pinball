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
/// @brief Utilise pour calculer les limites de la selection
///
/// @author The Ballers
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

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

	/// Obtenir les limites inferieures de la selection
	double getXMin() const { return xMin_; };
	double getYMin() const { return yMin_; };

	/// Obtenir les limites superieures de la selection
	double getXMax() const { return xMax_; };
	double getYMax() const { return yMax_; };

private:

	double xMin_, xMax_;
	double yMin_, yMax_;

};


#endif //__VISITEURS_VISITEURLIMITESELECTION_H__