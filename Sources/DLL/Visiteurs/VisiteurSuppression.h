///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURSUPPRESSION_H__
#define __VISITEURS_VISITEURSUPPRESSION_H__

#include "VisiteurAbstrait.h"
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSuppression
/// @brief Classe pour supprimer les objets selectionnés.
///
///        Instancier cette classe. Ensuite, appeler la méthode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en paramètre
///
/// @author Yonni Chen
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurSuppression : public VisiteurAbstrait
{
public:

	/// Constructeur par défaut
	VisiteurSuppression();

	/// Destructeur
	~VisiteurSuppression();

	/// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudAbstrait* noeud);

private:

	ArbreRenduINF2990* arbreTemp;
	std::vector<NoeudAbstrait*> suppression;
};

#endif //__VISITEURS_VISITEURSUPPRESSION_H__