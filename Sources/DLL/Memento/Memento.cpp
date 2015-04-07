#include "Memento.h"


Memento::Memento(ArbreRenduINF2990* arbre)
{
	sauvegarder(arbre);
}

Memento::~Memento()
{
	sauvegarde.clear();
}

void Memento::sauvegarder(ArbreRenduINF2990* arbre)
{
	std::vector<NoeudAbstrait*> temp = arbre->obtenirElementsTable();

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		NoeudAbstrait* noeud{ arbre->creerNoeud(temp[i]->obtenirType()) };

		// Copier les informations
		noeud->assignerPositionRelative(temp[i]->obtenirPositionRelative());
		noeud->assignerEchelle(temp[i]->obtenirAgrandissement());
		noeud->assignerRotation(temp[i]->obtenirRotation());
		noeud->setColorShift(temp[i]->getColorShift());

		sauvegarde.push_back(noeud);
	}

}

