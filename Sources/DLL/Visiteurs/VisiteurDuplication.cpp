////////////////////////////////////////////////
/// @file   VisiteurDuplication.cpp
/// @author Yonni Chen
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
/// Constructeur par défaut qui initialise les valeurs par défaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication()
{
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
///
/// Cette fonction traite l'arbre de rendu pour dupliquer ses enfants selectionnés.
///	Cette fonction retourne true pour dire que l'opération s'est faite correctement.
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
///
/// Cette fonction traite la table de l'arbre de rendu. Cette fonction retourne 
///	true pour dire que l'opération s'est faite correctement.
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

	if (!copies_.empty())
	{
		// Ajouter les copies à la table
		for (unsigned int i = 0; i < copies_.size(); i++)
		{
			table->ajouter(copies_[i]);
		}

		// Vider le vecteur contenant les copies
		copies_.clear();
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDuplication::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu. Cette fonction 
///	retourne true pour dire que l'opération s'est faite correctement
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
		// Effectuer la copie du noeud
		NoeudAbstrait* copie = arbreTemp->creerNoeud(noeud->obtenirType());
		copie->assignerRotation(noeud->obtenirRotation());
		copie->assignerEchelle(noeud->obtenirAgrandissement());
		copie->assignerPositionRelative(noeud->obtenirPositionRelative());
		copie->setColorShift(noeud->getColorShift());
		copie->assignerSelection(true);

		// Copier le jumeau du portail si il est selectionné
		if (noeud->obtenirType() == "portail" && noeud->getTwin()->estSelectionne())
		{
			// Effectuer la copie du jumeau
			NoeudAbstrait* copieJumeau = arbreTemp->creerNoeud(noeud->getTwin()->obtenirType());
			copieJumeau->assignerRotation(noeud->getTwin()->obtenirRotation());
			copieJumeau->assignerEchelle(noeud->getTwin()->obtenirAgrandissement());
			copieJumeau->assignerPositionRelative(noeud->getTwin()->obtenirPositionRelative());
			copieJumeau->assignerSelection(true);

			// Relier les jumeaux
			copieJumeau->setTwin(copie);
			copie->setTwin(copieJumeau);

			// Ajouter les copies dans une structure de donnée
			copies_.push_back(copie);
			copies_.push_back(copieJumeau);

			// Eviter d'effectuer une double copie lorsque le jumeau du portail est aussi selectionné
			noeud->getTwin()->assignerSelection(false);
		}
		
		// Supprimer le noeud si c'est un portail et que son jumeau n'est pas selectionné
		else if (noeud->obtenirType() == "portail" && !(noeud->getTwin()->estSelectionne()))
		{
			delete copie;
			copie = 0;
		}
		
		// Ajouter la copie à la structure de donnée
		else
		{
			copies_.push_back(copie);
		}

		// Déselectionner le noeud original
		noeud->assignerSelection(false);

	}

	return true;
}