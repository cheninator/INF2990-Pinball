#include "Originator.h"


Originator::Originator()
{
	arbreActuel_ = nullptr;
}

void Originator::assigner(ArbreRenduINF2990* arbre)
{
	*arbreActuel_ = *arbre;
}

ArbreRenduINF2990* Originator::restaurerMemento(Memento* memento)
{
	if (memento == nullptr)
		return nullptr;

	arbreActuel_ = memento->obtenirArbreEnregistrer();

	return arbreActuel_;
}