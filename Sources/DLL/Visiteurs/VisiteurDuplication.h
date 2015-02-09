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
/// @brief Classe pour selectionner les objets de l'arbre de rendu
///
///        Instancier cette classe avec en paramètre le point cliqué
///		   Ensuite, appeler la méthode accepterVisiteur() de l'arbre de 
///		   rendu et lui fournir CE visiteur en paramètre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public VisiteurAbstrait
{
public:

	/// Constructeur par paramètre
	VisiteurDuplication(glm::dvec3 pointDansLeMonde);

	/// Destructeur
	~VisiteurDuplication();

	/// Traiter une opération sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);

private:

	/// Constructeur par défaut
	VisiteurDuplication();

	glm::dvec3 pointDansLeMonde_; ///< Point où le clic de la souris a eu lieu

	std::vector<NoeudAbstrait*> copies_; ///< Contient les copies des objets selectionnés

	double minX; ///< Pour le cas ou il y a eu selection multiple
	double maxX; ///< Pour le cas ou il y a eu selection multiple
	double minY; ///< Pour le cas ou il y a eu selection multiple
	double maxY; ///< Pour le cas ou il y a eu selection multiple

};


#endif //__VISITEURS_VISITEURDUPLICATION_H__