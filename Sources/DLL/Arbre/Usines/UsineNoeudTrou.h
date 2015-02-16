///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudTrou.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDTROU_H__
#define __ARBRE_USINES_USINENOEUDTROU_H__

#include "UsineNoeud.h"
#include "NoeudTrou.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudTrou
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudTrou.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudTrou : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudTrou(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudTrou::UsineNoeudTrou(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudTrou::UsineNoeudTrou(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Trou.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudTrou::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudTrou.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudTrou::creerNoeud() const
{
	auto noeud = new NoeudTrou{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDTROU_H__