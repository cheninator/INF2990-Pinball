#include "Originator.h"


Originator::Originator(ArbreRenduINF2990* arbre)
{
	arbreActuel_ = arbre;
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
	if (position_ == 0)
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

		arbreActuel_->getEnfant(0)->ajouter(noeud);
	}

	// Position courante dans l'historique change
	position_--;
}

void Originator::retablir()
{
	if (position_ == historique_->size() - 1)
		return;

	// Obtenir la sauvegarde desiree
	std::vector<NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(++position_)->obtenirSauvegarde();

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

		arbreActuel_->getEnfant(0)->ajouter(noeud);
	}

	// Position courante dans l'historique change
	position_++;
}

void Originator::sauvegarder()
{
	// La sauvegarde courante est deja la derniere sauvegarde
	if (position_ == historique_->size() - 1)
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
		historique_->ecraser(++position_);
		historique_->ajouter(new Memento(arbreActuel_));
		position_++;
	}
	
}