///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudCible.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDCIBLE_H__
#define __ARBRE_USINES_USINENOEUDCIBLE_H__

#include "UsineNoeud.h"
#include "NoeudCible.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudCible
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudCible.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudCible : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudCible(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudCible::UsineNoeudCible(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudCible::UsineNoeudCible(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Cible.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudCible::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudCible.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudCible::creerNoeud() const
{
	auto noeud = new NoeudCible{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDCIBLE_H__