///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelectionInverseMultiple.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSELECTIONINVERSEMULTIPLE_H__
#define __VISITEURS_VISITEURSELECTIONINVERSEMULTIPLE_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectionInverseMultiple
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
class VisiteurSelectionInverseMultiple : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre
	VisiteurSelectionInverseMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit);

	/// Destructeur
	~VisiteurSelectionInverseMultiple();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

	//////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNbObjetsSelectionne()
	///
	/// Methode get pour l'attribut nbObjetsSelectionne_.
	///
	/// @return Nombre d'objets selectionnes (attribut).
	///
	//////////////////////////////////////////////////////////////////////////
	int obtenirNbObjetsSelectionne() const { return nbObjetsSelectionne_; } ;

private:

	/// Constructeur par defaut
	VisiteurSelectionInverseMultiple();

	glm::dvec3 selectionBasGauche_; ///< Point clique (bas gauche)
	glm::dvec3 selectionHautDroit_; ///< Point clique (haut droit)

	int nbObjetsSelectionne_;		///< Nombre d'objets selectionnes
};


#endif //__VISITEURS_VISITEURSELECTIONINVERSEMULTIPLE_H__