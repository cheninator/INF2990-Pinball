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

	/// Constructeur
	CareTaker();

	/// Destructeur
	~CareTaker();

	/// Ajouter une sauvegarde dans l'historique
	void ajouter(Memento* memento);

	/// Vider l'historique
	void vider();

	/// Obtenir une certaine sauvegarde
	Memento* obtenirMemento(int index);

	/// La taille actuelle
	int size() const { return historique_.size(); };

private:

	/// Liste de tous les etats passes
	std::list<Memento*> historique_;

	/// Combien d'etat on veut enregistrer
	const int tailleMax = 10;

};




#endif