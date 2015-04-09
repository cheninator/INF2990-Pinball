//////////////////////////////////////////////////////////////////////////////
/// @file Memento.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __MEMENTO_H__
#define __MEMENTO_H__

#include "../Arbre/ArbreRenduINF2990.h"
#include <map>

///////////////////////////////////////////////////////////////////////////
/// @class Memento
/// @brief Structure de donnee qui contient les informations utiles pour sauvegarder l'arbre.
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
	std::map<int, NoeudAbstrait*> obtenirSauvegarde() const { return sauvegarde; };

private:

	/// Enregistrer l'information des noeuds
	void sauvegarder(ArbreRenduINF2990* arbreAEnregistrer);

	/// Structure de donnee qui contient l'information des noeuds
	std::map<int, NoeudAbstrait*> sauvegarde;

};




#endif