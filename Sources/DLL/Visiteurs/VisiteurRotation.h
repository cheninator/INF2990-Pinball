///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURROTATION_H__
#define __VISITEURS_VISITEURROTATION_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotation
/// @brief Classe pour effectuer une rotation sur des objets seletionnés de
///		   l'arbre de rendu.
///
///        Instancier cette classe avec en paramètre les angles de rotation.
///		   Ensuite, appelez la méthode accepterVisiteur() de l'arbre de rendu 
///		   et lui fournir CE visiteur en paramètre.
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurRotation : public VisiteurAbstrait
{
public:

	// Constructeur par paramètre : spécifiez l'angle, l'axe et le sens
	VisiteurRotation(glm::dvec3 angles);

	// Destructeur
	~VisiteurRotation();

	// Méthode d'accès
	glm::dvec3 getRotation() { return angles_; };

	// Méthode de modifications
	void setRotation(glm::dvec3 dep) { angles_ = dep; };

	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	// Ne touchez pas au constructeur par défaut
	VisiteurRotation();

	// Angles de rotation en x, y et z
	glm::dvec3 angles_;

};


#endif //__VISITEURS_VISITEURROTATION_H__