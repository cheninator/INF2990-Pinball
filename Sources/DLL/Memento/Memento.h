////////////////////////////////////////////////
/// @file   Memento.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup Memento
////////////////////////////////////////////////

#ifndef __MEMENTO_H__
#define __MEMENTO_H__


#include "../Arbre/ArbreRenduINF2990.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class Originator
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class Memento
{

public:

	/// Constructeur
	Memento(ArbreRenduINF2990* arbreAEnregistrer);

	/// Destructeur
	~Memento();

	/// Obtenir la sauvegarde
	std::vector<NoeudAbstrait*> obtenirSauvegarde() const { return sauvegarde; };

private:

	/// Enregistrer l'information des noeuds
	void sauvegarder(ArbreRenduINF2990* arbreAEnregistrer);

	/// Structure de donnee qui contient l'information des noeuds
	std::vector<NoeudAbstrait*> sauvegarde;

};




#endif