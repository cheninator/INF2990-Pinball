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
#include <deque>

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
	bool ajouter(Memento* memento);

	/// Ecrase les sauvegarde anterieurs a partir d'un index
	void ecraser(int index);

	/// Vider l'historique
	void vider();

	/// Obtenir une certaine sauvegarde
	Memento* obtenirMemento(int index);

	/// La taille actuelle
	int size() const { return (int)historique_.size(); };

private:

	/// Liste de tous les etats passes
	std::deque<Memento*> historique_;

	/// Combien d'etat on veut enregistrer
	const int tailleMax = 10;

};




#endif