////////////////////////////////////////////////////////////////////////////////////
/// @file Memento.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
///
////////////////////////////////////////////////////////////////////////////////////

#include "Memento.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn Memento::Memento(ArbreRenduINF2990* arbre)
///
/// Appelle la methode sauvegarder(ArbreRenduINF2990*)
///
/// @param[in] arbre : L'arbre que l'on veut sauvegarder
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Memento::Memento(ArbreRenduINF2990* arbre)
{
	sauvegarder(arbre);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Memento::~Memento()
///
/// Vide la structure de donnee contenant les informations de sauvegarde
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Memento::~Memento()
{
	sauvegarde.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Memento::sauvegarder(ArbreRenduINF2990* arbre)
///
/// Methode qui sauvegarde l'arbre de donnee dans une structure de donnees
///
/// @param[in] arbre : L'arbre que l'on veut sauvegarder
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Memento::sauvegarder(ArbreRenduINF2990* arbre)
{
	std::vector<NoeudAbstrait*> temp = arbre->obtenirElementsTable();

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (temp[i]->estSelectionne())
		{
			NoeudAbstrait* noeud{ arbre->creerNoeud(temp[i]->obtenirType())};

			// Copier les informations
			noeud->assignerPositionRelative(temp[i]->obtenirPositionRelative());
			noeud->assignerEchelle(temp[i]->obtenirAgrandissement());
			noeud->assignerRotation(temp[i]->obtenirRotation());
			noeud->setColorShift(temp[i]->getColorShift());
			noeud->setNumero(255);

			// Inserer la sauvegarde dans une structure de donnee
			sauvegarde.insert(std::make_pair(temp[i]->getNumero(), noeud));
		}

	}

}

