////////////////////////////////////////////////
/// @file   Originator.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup Memento
////////////////////////////////////////////////

#ifndef __ORIGINATOR_H__
#define __ORIGINATOR_H__


#include "../Arbre/ArbreRenduINF2990.h"
#include "Memento.h"
#include "CareTaker.h"

///////////////////////////////////////////////////////////////////////////
/// @class Originator
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class Originator
{

public :

	/// Constructeur
	Originator();

	/// Destructeur
	~Originator();

	/// Operation annuler
	void annuler();

	/// Operation retablir
	void retablir();

	/// Sauvegarder l'arbre dans un memento
	void sauvegarder();

	/// Assigner un arbre de rendu
	void assignerArbre(ArbreRenduINF2990* arbre) { arbreActuel_ = arbre; };

private:

	/// L'arbre dont il faut manipuler les changements d'etats
	ArbreRenduINF2990* arbreActuel_;

	/// Contient l'historique des etats
	CareTaker* historique_;

	/// Position courrante
	int position_;

};




#endif