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
#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectionInverseMultiple
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en paramètre le point cliqué
///		   Ensuite, appeler la méthode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en paramètre
///
/// @author Philippe Carphin
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurSelectionInverseMultiple : public VisiteurAbstrait
{
public:

	/// Constructeur par défaut : aucun déplacement
	VisiteurSelectionInverseMultiple(glm::dvec3 selectionBasGauche, glm::dvec3 selectionHautDroit);

	/// Destructeur
	~VisiteurSelectionInverseMultiple();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudAbstrait* noeud);
	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(NoeudTable* table);

	//////////////////////////////////////////////////////////////////////////
	///
	/// @fn int obtenirNbObjetsSelectionne()
	///
	/// Méthode get pour l'attribut nbObjetsSelectionne_.
	///
	/// @return Nombre d'objets sélectionnés (attribut).
	///
	//////////////////////////////////////////////////////////////////////////
	int obtenirNbObjetsSelectionne()
	{
		return nbObjetsSelectionne_;
	}

private:

	/// Constructeur par défaut
	VisiteurSelectionInverseMultiple();

	glm::dvec3 selectionBasGauche_; ///< Point cliqué (bas gauche)
	glm::dvec3 selectionHautDroit_; ///< Point cliqué (haut droit)

	int nbObjetsSelectionne_; ///< Nombre d'objets sélectionnés
};


#endif //__VISITEURS_VISITEURSELECTIONINVERSEMULTIPLE_H__