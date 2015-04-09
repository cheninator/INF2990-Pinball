////////////////////////////////////////////////////////////////////////////////////
/// @file CareTaker.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
///
////////////////////////////////////////////////////////////////////////////////////

#include "CareTaker.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn CareTaker::CareTaker()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
CareTaker::CareTaker()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn CareTaker::~CareTaker()
///
/// Appelle la methode vider()
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
CareTaker::~CareTaker()
{
	vider();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void CareTaker::ajouter(Memento* memento)
///
/// Methode qui ajoute a sa structure de donnee un memento
///
/// @param[in] memento : Le memento a ajouter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////
///
/// @fn void CareTaker::ecraser(int index)
///
/// Methode qui ecrase les sauvegardes a partir d'un index
///
/// @param[in] index : L'index a partir duquel il faut ecraser les sauvegardes
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CareTaker::ecraser(int index)
{
	if (index < 0 || index > historique_.size())
		return;
	
	int diff = (int)historique_.size() - index - 1;

	if (diff < historique_.size())
	{
		for (diff; diff != 0; diff--)
			historique_.pop_back();
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn CareTaker::vider()
///
/// Vide la structure de donnee contenant les informations de sauvegarde et 
///	desalloue la memoire.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void CareTaker::vider()
{
	historique_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn CareTaker::obtenirMemento(int index)
///
/// Obtient un Memento* selon l'index qui est passe en parametre
///
/// @param[in] index : L'index dans la structure de donnees
///
/// @return Memento* 
///
////////////////////////////////////////////////////////////////////////
Memento* CareTaker::obtenirMemento(int index)
{
	if (index < 0 && index > historique_.size())
		return nullptr;

	return historique_[index];
}