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
///        Instancier cette classe avec en param�tre le point cliqu�
///		   Ensuite, appeler la m�thode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en param�tre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurSelection : public VisiteurAbstrait
{
public:

	/// Constructeur par param�tre
	VisiteurSelection(glm::dvec3 pointDansLeMonde, int valeurStencil);

	/// Destructeur
	~VisiteurSelection();

	/// Traiter une op�ration sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

	/// Nombre d'objets s�lectionn�s disponnible pour les clients
	int obtenirNbObjetsSelectionne() const { return nbObjetsSelectionne_; }

private:
	
	/// Constructeur par d�faut
	VisiteurSelection();
	
	glm::dvec3 pointDansLeMonde_;	///> Point cliqu�
	int valeurStencil_;				///> Valeur du stencil � comparer au num�ro des noeuds
	int nbObjetsSelectionne_;		///> Nombre d'objets s�lectionn�s disponnible pour les clients
};

#endif //__VISITEURS_VISITEURSELECTION_H__