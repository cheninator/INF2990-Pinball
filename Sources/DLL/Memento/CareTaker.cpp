#include "CareTaker.h"


CareTaker::CareTaker()
{

}

CareTaker::~CareTaker()
{
	vider();
}

bool CareTaker::ajouter(Memento* memento)
{
	if (memento == nullptr)
		return false;

	if (historique_.size() < tailleMax)
		historique_.push_back(memento);

	else if (historique_.size() == tailleMax)
	{
		historique_.pop_front();
		historique_.push_back(memento);
		return true;
	}

	return false;
}

void CareTaker::ecraser(int index)
{
	if (index < 0 && index > historique_.size())
		return;
	
	int diff = (int)historique_.size() - index - 1;

	if (diff > historique_.size())
	{
		for (diff; diff != 0; diff--)
			historique_.pop_back();
	}

}

void CareTaker::vider()
{
	historique_.clear();
}

Memento* CareTaker::obtenirMemento(int index)
{
	if (index < 0 && index > historique_.size())
		return nullptr;

	return historique_[index];
}