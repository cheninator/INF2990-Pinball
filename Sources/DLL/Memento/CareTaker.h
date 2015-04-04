////////////////////////////////////////////////
/// @file   CareTaker.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup Memento
////////////////////////////////////////////////

#ifndef __CARETAKER_H__
#define __CARETAKER_H__


#include "Memento.h"
#include <list>

///////////////////////////////////////////////////////////////////////////
/// @class CareTaker
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class CareTaker
{

public:

	void ajouter(Memento* memento);

	void obtenirMemento(int index);

private:

	/// Liste de tous les etats passes
	std::list<Memento*> arbres_;

	/// Combien d'etat on veut enregistrer
	int tailleMax;

	/// Nombre d'etat actuelle present dans la liste
	int tailleActuelle_;

};




#endif