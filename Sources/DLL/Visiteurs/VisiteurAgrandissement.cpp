////////////////////////////////////////////////
/// @file   VisiteurAgrandissement.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurAgrandissement.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudMur.h"
#include "../Arbre/Noeuds/NoeudGenerateurBille.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAgrandissement::VisiteurAgrandissement()
///
/// Constructeur par defaut (Vide).
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
/// sur les objets selectionnes. Cette fonction retourne true pour dire que 
/// l'operation s'est faite correctement.
///
/// @param[in] arbre : L'arbre de rendu a traiter.
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
/// Cette fonction traite la table de l'arbre pour effectuer un agrandissement
/// sur ses enfants. Cette fonction retourne true si l'operation s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
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
/// un agrandissement. Cette fonction retourne true pour dire que l'operation 
/// s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre de rendu a traiter.
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
		// et on utilise un deplacement pour la definir, qui est "additif". 
		// Qu'est-ce qui transforme l'addition en multiplication? A^(x + y) = (A^x) * (A^y)
		// c'est pour ca qu'il y a une exponentielle dans la fonction de facadeModele qui calcule le scale a donner au visiteur.
		glm::dvec3 scaleInit = noeud->obtenirAgrandissement();
		glm::dvec3 scaleFinal = glm::dvec3{ scaleInit[0] * homothetie_[0], scaleInit[1] * homothetie_[1], scaleInit[2] * homothetie_[2] };
	
		glm::dvec3 position = noeud->obtenirPositionRelative();
		glm::dvec3 boite[4];
		noeud->obtenirVecteursBoite(boite[0], boite[1], boite[2], boite[3]); // Je sais que c'est pas beau, le 3e, c'est le point le plus haut de la boite englobante
		double zTop = boite[0].z;

		for (int i = 1; i < 4; i++) // Trouver le point le plus haut de la boite englobante.  
		{
			if (zTop > boite[i].z)
				zTop = boite[i].z;
		}

		double distancePositionTop = zTop;
		// On as plus besoin de la correction en Z grace aux boites englobantes
		//double correctionZ = (1 - homothetie_[0]) * distancePositionTop; // Homothetie[0] est de l'ordre de 1.003, donc (1-homothetie[0]) est petie, donc la correction en z est petite.
		//position += glm::dvec3{ 0, 0, -correctionZ };
		noeud->assignerEchelle(scaleFinal);
		noeud->assignerPositionRelative(position);
		
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudMur* noeud)
///
/// Cette fonction traite un mur de l'arbre de rendu pour effectuer 
/// un agrandissement. Cette fonction retourne true pour dire que l'operation 
/// s'est faite correctement.
///
/// @param[in] noeud : NoeudMur de l'arbre de rendu a traiter.
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
		// et on utilise un deplacement pour la definir, qui est "additif". 
		// Qu'est-ce qui transforme l'addition en multiplication? A^(x + y) = (A^x) * (A^y)
		// c'est pour ca qu'il y a une exponentielle dans la fonction de facadeModele qui calcule le scale a donner au visiteur.
		glm::dvec3 scaleInit = noeud->obtenirAgrandissement();
		glm::dvec3 scaleFinal = glm::dvec3{ scaleInit[0], scaleInit[1] * homothetie_[1], scaleInit[2] };
		noeud->assignerEchelle(scaleFinal);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudGenerateurBille* noeud)
///
/// Cette fonction traite un generateur de bille de l'arbre de rendu pour effectuer 
/// un agrandissement. Cette fonction retourne true pour dire que l'operation 
/// s'est faite correctement.
///
/// @param[in] noeud : NoeudGenerateurBille de l'arbre de rendu a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudGenerateurBille* noeud)
{

	if (noeud->estSelectionne() && noeud->estAjustable() && noeud->estModifiable())
	{
		// LOGIQUE D'AGRANDISSEMENT
		// REMARQUE: LE SCALE EST QUELQUE CHOSE DE MULTIPLICATIF
		// et on utilise un deplacement pour la definir, qui est "additif". 
		// Qu'est-ce qui transforme l'addition en multiplication? A^(x + y) = (A^x) * (A^y)
		// c'est pour ca qu'il y a une exponentielle dans la fonction de facadeModele qui calcule le scale a donner au visiteur.
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
		// SingletonGlobal::obtenirInstance()->outPutStream_<< "AVANT position.z : " << position.z << "   distancePositionTop : " << distancePositionTop << "    TOP : " << position.z + zTop << std::endl;
		noeud->assignerEchelle(scaleFinal);
		if (scaleFinal.x * noeud->obtenirAgrandissement().x < 1)
			noeud->assignerPositionRelative(position);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurAgrandissement::traiter(NoeudPortail* noeud)
///
/// Cette fonction traite un portail de l'arbre de rendu pour effectuer 
/// un agrandissement. Cette fonction retourne true pour dire que l'operation 
/// s'est faite correctement.
///
/// @param[in] noeud : NoeudPortail de l'arbre de rendu a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurAgrandissement::traiter(NoeudPortail* noeud)
{
	if (noeud->estSelectionne())
	{
		glm::dvec3 scaleInit = noeud->obtenirAgrandissement();
		glm::dvec3 scaleFinal = glm::dvec3{ scaleInit[0] * homothetie_[0], scaleInit[1] * homothetie_[1], scaleInit[2] };
		noeud->assignerEchelle(scaleFinal);
		return true;
	}
	return false;
}