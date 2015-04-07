#include "Originator.h"


Originator::Originator()
{
	historique_ = new CareTaker();
	position_ = 0;
}

Originator::~Originator()
{
	delete historique_;

	arbreActuel_ = nullptr;
	historique_ = nullptr;
}

void Originator::annuler()
{
	// Ne rien faire lorsque qu'il n'y a pas eu de modification
	if (position_ == 0)
		return;

	// Tenter d'obtenir l'element de sauvegarde precedent
	if (historique_->obtenirMemento(position_ - 1) == nullptr)
		return;

	// Obtenir la sauvegarde desiree
	std::vector<NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(position_ - 1)->obtenirSauvegarde();

	// Vider l'ancien arbre
	arbreActuel_->getEnfant(0)->vider();

	// Repeupler avec les informations de sauvegarde
	for (unsigned int i = 0; i < sauvegarde.size(); i++)
	{
		NoeudAbstrait* noeud{ arbreActuel_->creerNoeud(sauvegarde[i]->obtenirType())};

		// Copier les informations
		noeud->assignerPositionRelative(sauvegarde[i]->obtenirPositionRelative());
		noeud->assignerEchelle(sauvegarde[i]->obtenirAgrandissement());
		noeud->assignerRotation(sauvegarde[i]->obtenirRotation());
		noeud->setColorShift(sauvegarde[i]->getColorShift());

		arbreActuel_->getEnfant(0)->ajouter(noeud);
	}

	// Position courante dans l'historique change
	position_--;
}

void Originator::retablir()
{
	// Ne rien faire lorsqu'il n'y a pas eu d'autres modifications
	if (position_ == historique_->size() - 1)
		return;

	// Tenter d'obtenir l'element de sauvegarde suivant
	if (historique_->obtenirMemento(position_ + 1) == nullptr)
		return;
	
	// Obtenir la sauvegarde desiree
	std::vector<NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(position_ + 1)->obtenirSauvegarde();

	// Vider l'ancien arbre
	arbreActuel_->getEnfant(0)->vider();

	// Repeupler avec les informations de sauvegarde
	for (unsigned int i = 0; i < sauvegarde.size(); i++)
	{
		NoeudAbstrait* noeud{ arbreActuel_->creerNoeud(sauvegarde[i]->obtenirType()) };

		// Copier les informations
		noeud->assignerPositionRelative(sauvegarde[i]->obtenirPositionRelative());
		noeud->assignerEchelle(sauvegarde[i]->obtenirAgrandissement());
		noeud->assignerRotation(sauvegarde[i]->obtenirRotation());
		noeud->setColorShift(sauvegarde[i]->getColorShift());

		arbreActuel_->getEnfant(0)->ajouter(noeud);
	}

	// Position courante dans l'historique change
	position_++;
}

void Originator::sauvegarder()
{
	// La sauvegarde courante est deja la derniere sauvegarde
	if (position_ + 1 == historique_->size())
	{
		historique_->ajouter(new Memento(arbreActuel_));
		position_++;
	}

	// On est au debut
	else if (position_ == 0)
	{
		historique_->vider();
		historique_->ajouter(new Memento(arbreActuel_));
	}

	// On est au milieu
	else
	{
		historique_->ecraser(position_);
		historique_->ajouter(new Memento(arbreActuel_));
		position_++;
	}
	
}