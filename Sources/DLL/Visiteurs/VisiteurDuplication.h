///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDUPLICATION_H__
#define __VISITEURS_VISITEURDUPLICATION_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en paramètre le point cliqué
///		   Ensuite, appelez la méthode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en paramètre
///
/// @author The Ballers
/// @date 2015-02-02
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : aucun déplacement
	VisiteurDuplication();

	// Destructeur
	~VisiteurDuplication();

	// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

private:

	// Ne touchez pas au constructeur par défaut
	VisiteurDuplication();

	int nbObjetsSelectionne_;
};


#endif //__VISITEURS_VISITEURDUPLICATION_H__