////////////////////////////////////////////////
/// @file   VisiteurAgrandissement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurAgrandissement.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::VisiteurAgrandissement()
///
/// Constructeur par défaut (Vide).
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
/// Constructeur qui initialise les variables membres de la classe.
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
/// Destructeur vide.
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
/// sur les objets selectionnés. Cette fonction retourne true pour dire que 
/// l'opération s'est faite correctement.
///
/// @param[in] arbre : L'arbre de rendu à traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(ArbreRenduINF2990* arbre)
{
	// Traiter les enfants de l'arbre de rendu
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudTable* table)
///
/// Cette fonction traite l'arbre de rendu pour effectuer un agrandissement
/// sur un noeud de type table. Cette fonction retourne true si l'opération s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table à traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudTable* table)
{
	// Traiter les enfants de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu pour effectuer 
/// un agrandissement. Cette fonction retourne true pour dire que l'opération 
/// s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre de rendu à traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudAbstrait* noeud)
{

	if (noeud->estSelectionne() && noeud->estAjustable() && noeud->estModifiable())
	{
		// LOGIQUE D'AGRANDISSEMENT
		// REMARQUE: LE SCALE EST QUELQUE CHOSE DE MULTIPLICATIF
		// et on utilise un déplacement pour la définir, qui est "additif". 
		// Qu'est-ce qui transforme l'addition en multiplication? A^(x + y) = (A^x) * (A^y)
		// c'est pour ça qu'il y a une exponentielle dans la fonction de facadeModele qui calcule le scale à donner au visiteur.
		glm::dvec3 scaleInit = noeud->obtenirAgrandissement();
		glm::dvec3 scaleFinal = glm::dvec3{ scaleInit[0] * homothetie_[0], scaleInit[1] * homothetie_[1], scaleInit[2] * homothetie_[2] };
		noeud->assignerEchelle(scaleFinal);
		
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudMur* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu pour effectuer 
/// un agrandissement. Cette fonction retourne true pour dire que l'opération 
/// s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre de rendu à traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudMur* noeud)
{
	if (noeud->estSelectionne() && noeud->estAjustable() && noeud->estModifiable())
	{
		// LOGIQUE D'AGRANDISSEMENT
		// REMARQUE: LE SCALE EST QUELQUE CHOSE DE MULTIPLICATIF
		// et on utilise un déplacement pour la définir, qui est "additif". 
		// Qu'est-ce qui transforme l'addition en multiplication? A^(x + y) = (A^x) * (A^y)
		// c'est pour ça qu'il y a une exponentielle dans la fonction de facadeModele qui calcule le scale à donner au visiteur.
		glm::dvec3 scaleInit = noeud->obtenirAgrandissement();
		glm::dvec3 scaleFinal = glm::dvec3{ scaleInit[0], scaleInit[1] * homothetie_[1] , scaleInit[2] };
		noeud->assignerEchelle(scaleFinal);
	}

	return true;
}
