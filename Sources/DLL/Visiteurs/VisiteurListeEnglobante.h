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

using conteneur_boite_englobante = std::pair<std::vector<glm::dvec3>,NoeudAbstrait*>;
///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeselectionnerTout
/// @brief Classe pour d�s�lectionner tous les objets de la table de rendu.
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurListeEnglobante : public VisiteurAbstrait
{
public:

	/// Constructeur par d�faut : aucun d�placement
	VisiteurListeEnglobante();

	/// Destructeur
	~VisiteurListeEnglobante();

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);
	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* table);

	std::vector<conteneur_boite_englobante> obtenirListeEnglobante(){ return boitesEnglobantes_; };

private:

	
	/// Le choix du conteneur pour les enfants.

	std::vector<conteneur_boite_englobante> boitesEnglobantes_;
};

#endif //__VISITEURS_VISITEURDESELECTIONNERTOUT_H__