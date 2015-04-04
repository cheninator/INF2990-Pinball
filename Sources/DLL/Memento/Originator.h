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

	/// Assigner un arbre a l'Originator
	void assigner(ArbreRenduINF2990* arbre);

	/// Sauvegarder l'arbre dans un memento
	Memento* sauvegarderMemento() { return new Memento(arbreActuel_); };

	/// Restaurer l'arbre à partir d'un memento
	ArbreRenduINF2990* restaurerMemento(Memento* memento);

private:

	ArbreRenduINF2990* arbreActuel_;

};




#endif