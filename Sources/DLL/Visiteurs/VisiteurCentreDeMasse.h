///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCentreDeMasse.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURCENTREDEMASSE_H__
#define __VISITEURS_VISITEURCENTREDEMASSE_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCentreDeMasse
/// @brief Utilisé pour calculer le centre de masse des noeuds sélectionnés
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurCentreDeMasse : public VisiteurAbstrait
{
public:

	/// Constructeur
	VisiteurCentreDeMasse();

	/// Destructeur
	~VisiteurCentreDeMasse();
	
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

	// Obtenir les coordonnées (x,y,z) du centre de masse
	glm::dvec3 obtenirCentreDeMasse() const;

private:
	
	glm::dvec3 centreDeMasse_;	///< Centre de masse d'un noeud
	int nbNoeuds_;				///< Nombre de noeuds
	
};


#endif //__VISITEURS_VISITEURCENTREDEMASSE_H__