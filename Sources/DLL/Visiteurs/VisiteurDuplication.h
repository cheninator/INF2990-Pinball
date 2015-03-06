///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURDUPLICATION_H__
#define __VISITEURS_VISITEURDUPLICATION_H__

#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Classe pour dupliquer les objets selectionnes de l'arbre de rendu
///
///        Instancier cette classe. Ensuite, appeler la methode accepterVisiteur() 
///		   de l'arbre de rendu et lui fournir CE visiteur en parametre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:

	/// Constructeur par defaut
	VisiteurDuplication();	

	/// Destructeur
	~VisiteurDuplication();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

private:

	std::vector<NoeudAbstrait*> copies_;	///< Contient les copies des objets selectionnes
	ArbreRenduINF2990* arbreTemp;			///< Pointeur vers l'arbre de rendu original
};

#endif //__VISITEURS_VISITEURDUPLICATION_H__