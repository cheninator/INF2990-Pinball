///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBille.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_BILLE_H__
#define __ARBRE_USINES_BILLE_H__

#include "UsineNoeud.h"
#include "NoeudBille.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBille
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudBille.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBille : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudBille(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudBille::UsineNoeudBille(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBille::UsineNoeudBille(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Bille.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBille::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudBille.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBille::creerNoeud() const
{
	auto noeud = new NoeudBille{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDBILLE_H__