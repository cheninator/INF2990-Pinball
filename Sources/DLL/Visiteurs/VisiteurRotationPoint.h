///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotationPoint.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURROTATIONPOINT_H__
#define __VISITEURS_VISITEURROTATIONPOINT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotationPoint
/// @brief Classe pour effectuer une rotation sur des objets seletionnés de
///		   l'arbre de rendu autour d'un point donné
///
///        Instancier cette classe avec en paramètre les angles de rotation.
///		   Ensuite, appeler la méthode accepterVisiteur() de l'arbre de rendu 
///		   et lui fournir CE visiteur en paramètre.
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurRotationPoint : public VisiteurAbstrait
{
public:

	/// Constructeur par paramètre : spécifiez l'angle et le centre de rotation
	VisiteurRotationPoint(glm::dvec3 angles ,glm::dvec3 centreRotation);

	/// Destructeur
	~VisiteurRotationPoint();

	/// Méthode d'accès
	glm::dvec3 getRotation() const { return angles_; };

	/// Méthode de modifications
	void setRotation(glm::dvec3 dep) { angles_ = dep; };

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* noeud);

private:

	/// Constructeur par défaut
	VisiteurRotationPoint();

	glm::dvec3 angles_; ///< Angles de rotation en x, y et z

	glm::dvec3 centreRotation_;///< Centre de rotation

};

#endif //__VISITEURS_VISITEURROTATIONPOINT_H__