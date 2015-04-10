//////////////////////////////////////////////////////////////////////////////
/// @file Originator.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
///
//////////////////////////////////////////////////////////////////////////////

#ifndef __ORIGINATOR_H__
#define __ORIGINATOR_H__


#include "../Arbre/ArbreRenduINF2990.h"
#include "Memento.h"
#include "CareTaker.h"

///////////////////////////////////////////////////////////////////////////
/// @class Originator
/// @brief Classe qui gère l'historique des modifications. Permet de faire l'operation undo/redo
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

	/// Vider l'historique des modifications
	void viderHistorique();

	/// Assigner un arbre de rendu
	void assignerArbre(ArbreRenduINF2990* arbre) { arbreActuel_ = arbre; };

	/// Retourne vrai si on n'est pas à la fin de l'historique de sauvegarde
	bool possedeSuivant()	const{ return (position_ + 1 != historique_->size()); };

	/// Retourne vrai si on n'est pas au debut de l'historique de sauvegarde
	bool possedePrecedent() const{ return (position_ != 0); };

private:

	/// L'arbre dont il faut manipuler les changements d'etats
	ArbreRenduINF2990* arbreActuel_;

	/// Contient l'historique des etats
	CareTaker* historique_;

	/// Position courrante
	int position_;

	/// Appliquer les modifications à l'arbre de rendu a partir de la sauvegarde
	void appliquerModifications(std::map<int, NoeudAbstrait*> sauvegarde);

};




#endif