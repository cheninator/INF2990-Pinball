///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
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
///		   déplacement. Ensuite, appeler la méthode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en paramètre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	/// Constructeur par paramètre : spécifiez un vecteur de déplacement
	VisiteurDeplacement(glm::dvec3 dep);

	/// Destructeur
	~VisiteurDeplacement();

	/// Méthode d'acces
	glm::dvec3 getDeplacement() { return deplacement_; };

	/// Méthode de modifications
	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	/// Constructeur par défaut
	VisiteurDeplacement();

	glm::dvec3 deplacement_; ///< Vecteur de déplacement

};


#endif //__VISITEURS_VISITEURDEPLACEMENT_H__