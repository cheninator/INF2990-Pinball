///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAgrandissement.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURAGRANDISSEMENT_H__
#define __VISITEURS_VISITEURAGRANDISSEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAgrandissement
/// @brief Classe pour agrandir ou rétrécir des objets seletionnés de
///		   l'arbre de rendu.
///
///        Instancier cette classe avec en paramètre le facteur d'agrandissement
///		   en x, y et z. Ensuite, appeler la méthode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en paramètre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurAgrandissement : public VisiteurAbstrait
{
public:
	
	/// Constructeur par paramètre
	VisiteurAgrandissement(glm::dvec3 homothetie);

	/// Destructeur
	~VisiteurAgrandissement();

	/// Méthode d'accès
	glm::dvec3 getAgrandissement() { return homothetie_; };

	/// Méthode de modifications
	void setAgrandissement(glm::dvec3 homothetie) { homothetie_ = homothetie; };

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* noeud);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	/// Constructeur par défaut
	VisiteurAgrandissement();

	glm::dvec3 homothetie_; ///< Facteur d'agrandissement en x, y et z

};

#endif //__VISITEURS_VISITEURAGRANDISSEMENT_H__