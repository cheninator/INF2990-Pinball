////////////////////////////////////////////////
/// @file   VisiteurAgrandissement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurAgrandissement.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::VisiteurAgrandissement()
///
/// VIDE
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAgrandissement::VisiteurAgrandissement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::VisiteurAgrandissement(glm::dvec3 homothethie)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] homothethie : Le facteur d'agrandissement
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAgrandissement::VisiteurAgrandissement(glm::dvec3 homothethie)
{
	homothetie_ = homothethie;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::~VisiteurAgrandissement()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAgrandissement::~VisiteurAgrandissement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour effectuer un agrandissement
/// sur les objets selectionnés
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(ArbreRenduINF2990* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		traiter(noeud->getEnfant(i));
	}

	return true;
}


bool VisiteurAgrandissement::traiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudAbstrait* arbre)
///
/// Cette fonction traite les enfants de l'arbre de rendu pour effectuer 
/// un agrandissement
///
/// Cette fonction retourne true pour dire que l'opération s'est
/// fait correctement
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudAbstrait* noeud)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Si l'élément est une table, visiter ses enfants
	if (nom == "table")
	{
		// Traiter les enfants selectionnés de la table
		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			if (noeud->chercher(i)->estSelectionne())
				traiter(noeud->chercher(i));
		}
	}

	else
	{
		// LOGIQUE D'AGRANDISSEMENT
		// REMARQUE: LE SCALE EST QUELQUE CHOSE DE MULTIPLICATIF
		// et on utilise un déplacement pour la définir, qui est "additif". 
		// Qu'est-ce qui transforme l'addition en multiplication? A^(x + y) = (A^x) * (A^y)
		// c'est pour ça qu'il y a une exponentielle dans la fonction de facadeModele qui calcule le scale a donner au visiteur.
		glm::dvec3 scaleInit = noeud->obtenirAgrandissement();
		glm::dvec3 scaleFinal = glm::dvec3{ scaleInit[0] * homothetie_[0], scaleInit[1] * homothetie_[1], scaleInit[2] * homothetie_[2] };
		noeud->assignerEchelle(scaleFinal);
		
	}

	return true;
}
