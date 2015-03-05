///////////////////////////////////////////////////////////////////////////////
/// @file VisiteuDebug.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDEBUG_H__
#define __VISITEURS_VISITEURDEBUG_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"

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
class VisiteurDebug : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre
	VisiteurDebug(bool valeurDebugBille, bool valeurDebugPortail);

	/// Destructeur
	~VisiteurDebug();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

private:
	/// Constructeur par defaut
	VisiteurDebug();
	bool valeurDebugBille_;
	bool valeurDebugPortail_;
};

#endif //__VISITEURS_VISITEURDEBUG_H__