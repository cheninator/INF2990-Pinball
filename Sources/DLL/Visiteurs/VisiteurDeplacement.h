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
/// @brief Classe pour deplacer les objets selectionnes de l'arbre de rendu
///
///        Instancier cette classe avec en parametre le vecteur de 
///		   deplacement. Ensuite, appeler la methode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en parametre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre : specifiez un vecteur de deplacement
	VisiteurDeplacement(glm::dvec3 dep);

	/// Destructeur
	~VisiteurDeplacement();

	/// Methode d'acces
	glm::dvec3 getDeplacement() const { return deplacement_; };

	/// Methode de modifications
	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

	/// Assignateurs
	void setEstDansLaTable(bool b) { estDansLaTable_ = b; };
	void setEstDuplication(bool b) { estDuplication_ = b; };

private:

	/// Constructeur par defaut
	VisiteurDeplacement();

	glm::dvec3 deplacement_; ///< Vecteur de deplacement

	bool estDansLaTable_;
	bool estDuplication_;
};


#endif //__VISITEURS_VISITEURDEPLACEMENT_H__