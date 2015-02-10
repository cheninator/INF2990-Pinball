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
/// @param[in] pointDansLeMonde : Le point ou le clic a lieu.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication(glm::dvec3 pointDansLeMonde)
{
	pointDansLeMonde_ = pointDansLeMonde;
	maxX = maxY = std::numeric_limits<int>::min();
	minX = minY = std::numeric_limits<int>::max();
	arbreTemp = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::~VisiteurDuplication()
///
/// Desallocation de memoire.
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


//////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour dupliquer ses enfants selectionnés.
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// faite correctement.
///
/// @param[in] arbre : L'arbre de rendu à traiter.
///
/// @return Retourne toujours true.
///
//////////////////////////////////////////////////////////////////////////////////
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
/// fait correctement.
///
/// @param[in] table : Le noeud de type Table à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(NoeudTable* table)
{
	// Traiter les enfants de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	// Si la structure ne contient qu'un seul objet
	if (copies_.size() == 1)
	{
		// Centre de selection = clic de souris
		copies_.front()->assignerPositionRelative(pointDansLeMonde_);
		table->ajouter(copies_.back());
		copies_.pop_back();
	}

	// Si la structure contient plusieurs objets, trouver le centre de selection
	else if (copies_.size() > 1)
	{
		// Il faudra assigner la position relative des objets copiés en fonction du centre de selection
		double centreX = ((maxX - minX) / 2.0 ) + minX;
		double centreY = ((maxY - minY) / 2.0 ) + minY;

		// Difference entre la position courante de l'objet et le centre de selection
		double deltaX, deltaY;
		double posX, posY;

		for (unsigned int i = 0; i < copies_.size(); i++)
		{
			posX = copies_[i]->obtenirPositionRelative().x;
			posY = copies_[i]->obtenirPositionRelative().y;

			deltaX = posX - centreX;
			deltaY = posY - centreY;

			copies_[i]->assignerPositionRelative({(deltaX + pointDansLeMonde_.x), (deltaY + pointDansLeMonde_.y), 0.0});
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
/// Cette fonction traite un noeud de l'arbre de rendu. Si ses enfants ont 
/// des enfants, ils seront aussi traités. Cette fonction retourne true pour dire 
/// que l'opération s'est faite correctement
///
/// @param[in] noeud : Noeud de l'arbre à traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDuplication::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		// Copier le jumeau si il est selectionné
		if (noeud->obtenirType() == "portail" && noeud->getTwin()->estSelectionne())
		{
			// Effectuer la copie du portail selectionné
			NoeudAbstrait* copie = arbreTemp->creerNoeud(noeud->obtenirType());
			copie->assignerRotation(noeud->obtenirRotation());
			copie->assignerEchelle(noeud->obtenirAgrandissement());
			copie->assignerPositionRelative(noeud->obtenirPositionRelative());

			// Effectuer la copie du jumeau
			NoeudAbstrait* copieJumeau = arbreTemp->creerNoeud(noeud->obtenirType());
			copieJumeau->assignerRotation(noeud->getTwin()->obtenirRotation());
			copieJumeau->assignerEchelle(noeud->getTwin()->obtenirAgrandissement());
			copieJumeau->assignerPositionRelative(noeud->getTwin()->obtenirPositionRelative());

			// Relier les jumeaux
			copieJumeau->setTwin(copie);
			copie->setTwin(copieJumeau);

			// Ajouter la copie dans une structure de donnée afin de traiter la duplication 
			// multiple par la suite.
			copies_.push_back(copie);
			copies_.push_back(copieJumeau);

			// Trouver les mins et max afin de trouver le centre de selection
			if (maxX < noeud->obtenirPositionRelative().x)
				maxX = noeud->obtenirPositionRelative().x;

			if (minX > noeud->obtenirPositionRelative().x)
				minX = noeud->obtenirPositionRelative().x;

			if (maxY < noeud->obtenirPositionRelative().y)
				maxY = noeud->obtenirPositionRelative().y;

			if (minY > noeud->obtenirPositionRelative().y)
				minY = noeud->obtenirPositionRelative().y;

			if (maxX < noeud->getTwin()->obtenirPositionRelative().x)
				maxX = noeud->getTwin()->obtenirPositionRelative().x;

			if (minX > noeud->getTwin()->obtenirPositionRelative().x)
				minX = noeud->getTwin()->obtenirPositionRelative().x;

			if (maxY < noeud->getTwin()->obtenirPositionRelative().y)
				maxY = noeud->getTwin()->obtenirPositionRelative().y;

			if (minY > noeud->getTwin()->obtenirPositionRelative().y)
				minY = noeud->getTwin()->obtenirPositionRelative().y;

			noeud->getTwin()->assignerSelection(false);
		}

		else if (noeud->obtenirType() != "portail")
		{
			// Effectuer la copie
			NoeudAbstrait* copie = arbreTemp->creerNoeud(noeud->obtenirType());
			copie->assignerRotation(noeud->obtenirRotation());
			copie->assignerEchelle(noeud->obtenirAgrandissement());
			copie->assignerPositionRelative(noeud->obtenirPositionRelative());

			// Ajouter la copie dans une structure de donnée afin de traiter la duplication 
			// multiple par la suite.
			copies_.push_back(copie);

			// Trouver les mins et max afin de trouver le centre de selection
			if (maxX < noeud->obtenirPositionRelative().x)
				maxX = noeud->obtenirPositionRelative().x;

			if (minX > noeud->obtenirPositionRelative().x)
				minX = noeud->obtenirPositionRelative().x;

			if (maxY < noeud->obtenirPositionRelative().y)
				maxY = noeud->obtenirPositionRelative().y;

			if (minY > noeud->obtenirPositionRelative().y)
				minY = noeud->obtenirPositionRelative().y;
		}

		noeud->assignerSelection(false);
	}

	return true;
}
