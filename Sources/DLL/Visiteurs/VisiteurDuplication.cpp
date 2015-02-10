////////////////////////////////////////////////
/// @file   VisiteurDuplication.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurDuplication.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication()
///
/// Constructeur par défaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication(glm::dvec3 pointDansLeMonde)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] pointDansLeMonde : Le point ou il y a eu le clic
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication(glm::dvec3 pointDansLeMonde)
{
	pointDansLeMonde_ = pointDansLeMonde;
	maxX = maxY = 0;
	minX = minY = std::numeric_limits<int>::max();
	arbreTemp = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::~VisiteurDuplication()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::~VisiteurDuplication()
{
	for (unsigned int i = 0; i < copies_.size(); i++)
		delete copies_[i];

	copies_.clear();

	delete arbreTemp;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour dupliquer ses enfants selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(ArbreRenduINF2990* arbre)
{
	arbreTemp = arbre;

	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	arbreTemp = nullptr;

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnés de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		// Effectuer une copie des enfants selectionnés et les ajouter à la structure de donnée
		table->getEnfant(i)->accepterVisiteur(this);
	}

	// Si la structure ne contient qu'un seul objet
	if (copies_.size() == 1)
	{
		std::cout << "Nombre d'objets : " << table->obtenirNombreEnfants() << std::endl;
		copies_.front()->assignerPositionRelative(pointDansLeMonde_);
		table->ajouter(copies_.back());
		copies_.pop_back();
		std::cout << "Nombre d'objets maintenant : " << table->obtenirNombreEnfants() << std::endl;
	}

	// Si la structure contient plusieurs objets, trouver le centre de selection
	else if (copies_.size() > 1)
	{
		// Il faudra assigner la position relative des objets copiés en fonction du centre de selection
		double centreX = (maxX - minX) / 2.0;
		double centreY = (maxY - minY) / 2.0;

		// Difference entre la position de l'objet et le centre de selection
		double deltaX, deltaY;
		double posX, posY;

		for (unsigned int i = 0; i < copies_.size(); i++)
		{
			posX = copies_[i]->obtenirPositionRelative().x;
			posY = copies_[i]->obtenirPositionRelative().y;

			deltaX = posX - centreX;
			deltaY = posY - centreY;

			copies_[i]->assignerPositionRelative({posX + pointDansLeMonde_.x, posY + pointDansLeMonde_.y, 0.0});
			table->ajouter(copies_[i]);
		}

		copies_.clear();
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Si ses enfants ont des enfants
/// ils seront aussi traités.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne() && noeud->estModifiable())
	{
		std::cout << "Noeud a copier : " << noeud->getNumero() << std::endl;

		NoeudAbstrait* copie = arbreTemp->creerNoeud(noeud->obtenirType());

		std::cout << "J'ai cree un noeud de type : " << noeud->obtenirType() << std::endl;
		std::cout << "Le nouveau noeud est : " << copie->getNumero() << std::endl;

		copie->assignerRotation(noeud->obtenirRotation());
		copie->assignerEchelle(noeud->obtenirAgrandissement());
		copie->assignerPositionRelative(noeud->obtenirPositionRelative());

		if (maxX < noeud->obtenirPositionRelative().x)
		maxX = noeud->obtenirPositionRelative().x;

		if (minX > noeud->obtenirPositionRelative().x)
		minX = noeud->obtenirPositionRelative().x;

		if (maxY < noeud->obtenirPositionRelative().y)
		maxY = noeud->obtenirPositionRelative().y;

		if (minY > noeud->obtenirPositionRelative().y)
		minY = noeud->obtenirPositionRelative().y;

		copies_.push_back(copie);
	}

	return true;
}