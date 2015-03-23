////////////////////////////////////////////////
/// @file   VisiteurDebug.h
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#ifndef __VISITEURS_VISITEURDEBUG_H__
#define __VISITEURS_VISITEURDEBUG_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDebug
/// @brief Classe pour afficher le debug des objets de l'arbre de rendu
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDebug : public VisiteurAbstrait
{
public:

	/// Constructeur par parametre
	VisiteurDebug(bool valeurDebugBille, bool valeurDebugPortail, bool valeurSpotLight = false);

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
	bool valeurSpotLight_;
};

#endif //__VISITEURS_VISITEURDEBUG_H__