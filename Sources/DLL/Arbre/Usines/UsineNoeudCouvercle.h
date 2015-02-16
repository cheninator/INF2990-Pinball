///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudCouvercle.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDCOUVERCLE_H__
#define __ARBRE_USINES_USINENOEUDCOUVERCLE_H__

#include "UsineNoeud.h"
#include "NoeudCouvercle.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudCouvercle
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudCouvercle.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudCouvercle : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudCouvercle(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudCouvercle::UsineNoeudCouvercle(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudCouvercle::UsineNoeudCouvercle(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Couvercle.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudCouvercle::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudCouvercle.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudCouvercle::creerNoeud() const
{
	auto noeud = new NoeudCouvercle{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDCOUVERCLE_H__