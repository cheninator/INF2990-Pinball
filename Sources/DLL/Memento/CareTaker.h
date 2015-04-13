//////////////////////////////////////////////////////////////////////////////
/// @file CareTaker.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __CARETAKER_H__
#define __CARETAKER_H__

#include "Memento.h"
#include <deque>

///////////////////////////////////////////////////////////////////////////
/// @class CareTaker
/// @brief Structure de donnee qui contient des Memento. Offre des interfaces utiles.
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class CareTaker
{

public:

	/// Constructeur
	CareTaker();

	/// Assignation par copie non-necessaire dans le contexte
	CareTaker& operator=(CareTaker const&) = delete;

	/// Destructeur
	~CareTaker();

	/// Ajouter une sauvegarde dans l'historique
	void ajouter(Memento* memento);

	/// Ecrase les sauvegarde anterieurs a partir d'un index
	void ecraser(int index);

	/// Vider l'historique
	void vider();

	/// Obtenir une certaine sauvegarde
	Memento* obtenirMemento(int index);

	/// La taille actuelle
	int size() const { return (int)historique_.size(); };

	/// Obtenir la taille maximale
	int obtenirTailleMaximale() const { return tailleMax; };

private:

	/// Liste de tous les etats passes
	std::deque<Memento*> historique_;

	/// Combien d'etat on veut enregistrer
	const int tailleMax = 15;

};




#endif