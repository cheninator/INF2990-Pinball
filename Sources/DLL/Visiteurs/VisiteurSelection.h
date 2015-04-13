///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSELECTION_H__
#define __VISITEURS_VISITEURSELECTION_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en parametre le point clique
///		   Ensuite, appeler la methode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en parametre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurSelection : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre
	VisiteurSelection(glm::dvec3 pointDansLeMonde, int valeurStencil, bool gaucheEnfonce, bool sourisSurSelection);

	/// Destructeur
	~VisiteurSelection();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudPortail* noeud);

	/// Nombre d'objets selectionnes disponnible pour les clients
	int obtenirNbObjetsSelectionne() const { return nbObjetsSelectionne_; }

private:
	
	/// Constructeur par defaut
	VisiteurSelection();
	
	glm::dvec3 pointDansLeMonde_;	///> Point clique
	int valeurStencil_;				///> Valeur du stencil a comparer au numero des noeuds
	int nbObjetsSelectionne_;		///> Nombre d'objets selectionnes disponnible pour les clients
	bool gaucheEnfonce_;			///> true si le bouton de gauche est enfonce
	bool sourisSurSelection_;		///> true si la souris est sur un objet deja selectionne
};

#endif //__VISITEURS_VISITEURSELECTION_H__