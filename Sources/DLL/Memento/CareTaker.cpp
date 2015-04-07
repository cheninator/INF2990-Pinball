#include "CareTaker.h"


CareTaker::CareTaker()
{

}

CareTaker::~CareTaker()
{
	vider();
}

void CareTaker::ajouter(Memento* memento)
{
	if (memento == nullptr)
		return;

	if (historique_.size() < tailleMax)
		historique_.push_back(memento);

	else if (historique_.size() == tailleMax)
	{
		historique_.pop_front();
		historique_.push_back(memento);
	}
}

void CareTaker::ecraser(int index)
{
	if (index < 0 && index > historique_.size())
		return;

	std::list<Memento*>::iterator iter = historique_.begin();

	for (unsigned int i = 0; i < index; i++)
		iter++;

	historique_.erase(iter, historique_.end());
}

void CareTaker::vider()
{
	historique_.clear();
}

Memento* CareTaker::obtenirMemento(int index)
{
	if (index < 0 && index > historique_.size())
		return nullptr;

	std::list<Memento*>::iterator iter = historique_.begin();

	for (unsigned int i = 0; i < index; i++)
		iter++;

	return *iter;
}