///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURPAUSE_H__
#define __VISITEURS_VISITEURPAUSE_H__

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
class VisiteurPause : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre
	VisiteurPause(bool pause);

	/// Destructeur
	~VisiteurPause();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

private:
	/// Constructeur par defaut
	VisiteurPause();

	bool pause_;
};

#endif //__VISITEURS_VISITEURSELECTION_H__