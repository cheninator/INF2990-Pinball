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
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
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
	

		// On trouve le z le plus haut de l'objet : zOriginal.
		//===================================================
		glm::dvec3 position = noeud->obtenirPositionRelative();
		glm::dvec3 boiteInitiale[4];
		noeud->obtenirVecteursBoite(boiteInitiale[0], boiteInitiale[1], boiteInitiale[2], boiteInitiale[3]);
		double deltaZInitial = boiteInitiale[0].z;
		for (int i = 1; i < 4; i++) // Trouver le point le plus haut de la boite englobante.  
		{
			if (deltaZInitial < boiteInitiale[i].z)
				deltaZInitial = boiteInitiale[i].z;
		}
		// std::cout << "Valeur de deltaZInitial : " << deltaZInitial << std::endl;

		// Ici, deltaZFinal est la distance en z entre l'attribut position et le point le plus haut de l'objet.
		// Donc zOriginal est le z du point le plus haut de l'objet.
		double zOriginal = position.z + deltaZInitial;
		// std::cout << "Valeur de zOriginal     : " << zOriginal << std::endl;

		// On applique la mise à l'échelle,
		// =================================
		noeud->assignerEchelle(scaleFinal);

		// Et on s'arrange pour que le nouveau z le plus haut de l'objet soit zOriginal.
		// =============================================================================
		// Pour ce faire, on trouve le z le plus haut de l'objet scalé.
		glm::dvec3 boiteFinale[4];
		noeud->obtenirVecteursBoite(boiteFinale[0], boiteFinale[1], boiteFinale[2], boiteFinale[3]);
		double deltaZFinal = boiteFinale[0].z;
		for (int i = 1; i < 4; i++) // Trouver le point le plus haut de la boite englobante.  
		{
			if (deltaZFinal < boiteFinale[i].z)
				deltaZFinal = boiteFinale[i].z;
		}
		// std::cout << "Valeur de deltaZFinal   : " << deltaZFinal << std::endl;

		// Ici, deltaZFinal est la distance en z entre l'attribut position et le point le plus haut de l'objet.
		// Donc si on veut que le point le plus haut de l'objet soit à zOriginal, il faut que 
		// l'attribut position soit deltaZFinal unités en dessous de zOriginal.
		if (scaleFinal.x * noeud->obtenirAgrandissement().x < 1){
			noeud->assignerPositionRelative(glm::dvec3{ position.x, position.y, zOriginal - deltaZFinal });
			std::cout << "Valeur finale du z le plus haut de l'objet : " << noeud->obtenirPositionRelative().z + deltaZFinal << std::endl << " ==============================================" << std::endl;
		}
		
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

bool VisiteurAgrandissement::traiter(NoeudGenerateurBille* noeud)
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

		glm::dvec3 position = noeud->obtenirPositionRelative();
		glm::dvec3 boite[4];
		noeud->obtenirVecteursBoite(boite[0], boite[1], boite[2], boite[3]); // Je sais que c<est pas beau, le 3e, c'est le point le plus haut de la boite englobante
		double zTop = boite[0].z;
		for (int i = 1; i < 4; i++) // Trouver le point le plus haut de la boite englobante.  
		{
			if (zTop < boite[i].z)
				zTop = boite[i].z;
		}
		double distancePositionTop = zTop;
		double correctionZ = (1 - homothetie_[0]) * distancePositionTop; // Homothetie[0] est de l'ordre de 1.003, donc (1-homothetie[0]) est petie, donc la correction en z est petite.
		position += glm::dvec3{ 0, 0, correctionZ };
		// std::cout << "AVANT position.z : " << position.z << "   distancePositionTop : " << distancePositionTop << "    TOP : " << position.z + zTop << std::endl;
		noeud->assignerEchelle(scaleFinal);
		if (scaleFinal.x * noeud->obtenirAgrandissement().x < 1)
			noeud->assignerPositionRelative(position);
	}
	return true;
}