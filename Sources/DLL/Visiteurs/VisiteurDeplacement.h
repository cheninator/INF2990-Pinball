///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDEPLACEMENT_H__
#define __VISITEURS_VISITEURDEPLACEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeplacement
/// @brief Classe pour deplacer les objets selectionnés de l'arbre de rendu
///
///        Instancier cette classe avec en paramètre le vecteur de 
///		   déplacement. Ensuite, appelez la méthode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en paramètre
///
/// @author Yonni Chen
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	// Constructeur par paramètre : spécifiez un vecteur de déplacement
	VisiteurDeplacement(glm::dvec3 dep);

	// Destructeur
	~VisiteurDeplacement();

	// Méthode d'acces
	glm::dvec3 getDeplacement() { return deplacement_; };

	// Méthode de modifications
	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	// Ne touchez pas au constructeur de déplacement
	VisiteurDeplacement();

	// Vecteur de déplacement
	glm::dvec3 deplacement_;

};


#endif //__VISITEURS_VISITEURDEPLACEMENT_H__