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
/// @brief Classe pour agrandir ou retrecir des objets seletionnes de
///		   l'arbre de rendu.
///
///        Instancier cette classe avec en parametre le facteur d'agrandissement
///		   en x, y et z. Ensuite, appeler la methode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en parametre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurAgrandissement : public VisiteurAbstrait
{
public:
	
	/// Constructeur par parametre
	VisiteurAgrandissement(glm::dvec3 homothetie);

	/// Destructeur
	~VisiteurAgrandissement();

	/// Methode d'acces
	glm::dvec3 getAgrandissement() { return homothetie_; };

	/// Methode de modifications
	void setAgrandissement(glm::dvec3 homothetie) { homothetie_ = homothetie; };

	/// Traiter une operation sur l'arbre de rendu
	virtual bool traiter(ArbreRenduINF2990* arbre);

	/// Traiter une operation sur la table de l'arbre de rendu
	virtual bool traiter(NoeudTable* noeud);

	/// Traiter une operation sur les noeuds abstraits de l'arbre de rendu
	virtual bool traiter(NoeudAbstrait* noeud);

	/// Traiter un mur differement d'un NoeudAbstrait
	virtual bool traiter(NoeudMur* noeud);

	/// Traiter un generateur de bille differement d'un NoeudAbstrait
	virtual bool traiter(NoeudGenerateurBille* noeud);

private:

	/// Constructeur par defaut
	VisiteurAgrandissement();

	glm::dvec3 homothetie_; ///< Facteur d'agrandissement en x, y et z

};

#endif //__VISITEURS_VISITEURAGRANDISSEMENT_H__