////////////////////////////////////////////////
/// @file   VisiteurDeplacement.cpp
/// @author Yonni Chen
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
#include "../Arbre/ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement()
///
/// Constructeur par d�faut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 dep)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] dev : Le vecteur de deplacement
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 dep)
{
	deplacement_ = dep;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::~VisiteurDeplacement()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::~VisiteurDeplacement()
{

}


//////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour deplacer ses enfants selectionn�s.
///
/// Cette fonction retourne true pour dire que l'op�ration s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu � traiter.
///
/// @return Retourne toujours true.
///
//////////////////////////////////////////////////////////////////////////////////
bool VisiteurDeplacement::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		traiter(arbre->getEnfant(i));
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeplacement::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite un noeud de l'arbre de rendu. Si ses enfants ont 
/// des enfants, ils seront aussi trait�s. Cette fonction retourne true pour dire 
/// que l'op�ration s'est faite correctement
///
/// @param[in] noeud : Noeud de l'arbre � traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDeplacement::traiter(NoeudAbstrait* noeud)
{
	// Connaitre le type du noeud
	std::string nom = noeud->obtenirType();

	// Si l'�l�ment est une table, visiter ses enfants
	if (nom == "table")
	{
		// Traiter les enfants selectionn�s de la table
		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			if (noeud->chercher(i)->estSelectionne())
				traiter(noeud->chercher(i));
		}
	}

	else
	{
		// LOGIQUE DE D�PLACEMENT
		glm::dvec3 nouvellePosition{ noeud->obtenirPositionRelative() + deplacement_ };
		if (noeud->estSelectionne())
			noeud->assignerPositionRelative(nouvellePosition);
	}

	return true;
}
