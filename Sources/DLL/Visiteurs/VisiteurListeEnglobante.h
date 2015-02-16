///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurListeEnglobante.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURLISTEENGLOBANTE_H__
#define __VISITEURS_VISITEURLISTEENGLOBANTE_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"
#include <vector>

using conteneur_boite_englobante = std::pair<std::vector<glm::dvec3>, NoeudAbstrait*>;
///////////////////////////////////////////////////////////////////////////
/// @class VisiteurListeEnglobante
/// @brief Classe pour créer une Liste de rectangles englobants.
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurListeEnglobante : public VisiteurAbstrait
{
public:

	/// Constructeur par défaut
	VisiteurListeEnglobante();

	/// Destructeur
	~VisiteurListeEnglobante();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

	std::vector<conteneur_boite_englobante> obtenirListeEnglobante(){ return boitesEnglobantes_; };

private:

	/// Le choix du conteneur pour les enfants.
	std::vector<conteneur_boite_englobante> boitesEnglobantes_;

};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__