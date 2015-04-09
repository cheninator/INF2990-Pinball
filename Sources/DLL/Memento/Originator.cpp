////////////////////////////////////////////////////////////////////////////////////
/// @file Originator.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
///
////////////////////////////////////////////////////////////////////////////////////

#include "Originator.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Originator::Originator()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Originator::Originator()
{
	historique_ = new CareTaker();
	position_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Originator::~Originator()
///
/// Vide la structure de donnee contenant les informations de sauvegarde et 
///	desalloue la memoire.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Originator::~Originator()
{
	delete historique_;

	arbreActuel_ = nullptr;
	historique_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Originator::annuler()
///
/// Methode qui implemente le "undo" et modifie l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Originator::annuler()
{
	// Ne rien faire lorsque qu'il n'y a pas eu de modification
	if (position_ == 0)
		return;

	// Ne rien faire lorsqu'il n'y a pas d'historique
	if (historique_->size() == 0)
		return;

	// Tenter d'obtenir l'element de sauvegarde precedent
	if (historique_->obtenirMemento(position_ - 1) == nullptr)
		return;

	// Obtenir la sauvegarde desiree
	std::map<int, NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(position_ - 1)->obtenirSauvegarde();

	// Appliquer les modifications a l'arbre
	appliquerModifications(sauvegarde);

	// Position courante dans l'historique change
	position_--;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Originator::retablir()
///
/// Methode qui implemente le "redo" et modifie l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Originator::retablir()
{
	// Ne rien faire lorsqu'il n'y a pas eu d'autres modifications
	if (position_ + 1 == historique_->size())
		return;

	// Ne rien faire lorsqu'il n'y a pas d'historique
	if (historique_->size() == 0)
		return;

	// Tenter d'obtenir l'element de sauvegarde suivant
	if (historique_->obtenirMemento(position_ + 1) == nullptr)
		return;
	
	// Obtenir la sauvegarde desiree
	std::map<int, NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(position_ + 1)->obtenirSauvegarde();

	// Appliquer les modifications a l'arbre
	appliquerModifications(sauvegarde);

	// Position courante dans l'historique change
	position_++;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Originator::sauvegarder()
///
/// Methode qui sauvegarde l'arbre et conserve celle-ci dans une structure de donnees.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Originator::sauvegarder()
{
	// La sauvegarde courante est deja la derniere sauvegarde
	if (position_ + 1 == historique_->size())
	{
		historique_->ajouter(new Memento(arbreActuel_));

		// Incrementer la position si seulement elle est inferieur a 10
		if ((position_ + 1 ) != historique_->obtenirTailleMaximale())
			position_++;
	}

	// 1ere sauvegarde
	else if (position_ == 0 && historique_->size() == 0)
	{
		historique_->ajouter(new Memento(arbreActuel_));
	}

	// Ecraser les sauvegardes suivantes
	else if (position_ == 0 && historique_->size() != 0)
	{
		historique_->ecraser(position_);
		historique_->ajouter(new Memento(arbreActuel_));
		position_++;
	}

	// On est entre la 1ere et la derniere sauvegarde
	else if (position_ < historique_->size())
	{
		historique_->ecraser(position_);
		historique_->ajouter(new Memento(arbreActuel_));
		position_++;
	}
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Originator::viderHistorique()
///
/// Methode qui vide l'historique des sauvegardes.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Originator::viderHistorique()
{
	historique_->vider();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Originator::appliquerModifications()
///
/// Methode qui applique des modifications a l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Originator::appliquerModifications(std::map<int, NoeudAbstrait*> sauvegarde)
{
	std::map<int, NoeudAbstrait*>::iterator iter;

	// Vider l'ancien arbre
	arbreActuel_->getEnfant(0)->vider();

	NoeudAbstrait::changerNumero(0);

	// Modifier l'arbre courant avec les informations de sauvegarde
	for (iter = sauvegarde.begin(); iter != sauvegarde.end(); iter++)
	{
		NoeudAbstrait* noeud{ arbreActuel_->creerNoeud(iter->second->obtenirType())};

		noeud->assignerPositionRelative(iter->second->obtenirPositionRelative());
		noeud->assignerEchelle(iter->second->obtenirAgrandissement());
		noeud->assignerRotation(iter->second->obtenirRotation());
		noeud->setColorShift(iter->second->getColorShift());

		arbreActuel_->getEnfant(0)->ajouter(noeud);
	}

}