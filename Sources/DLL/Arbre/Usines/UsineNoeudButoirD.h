///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoirD.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBUTOIRD_H__
#define __ARBRE_USINES_USINENOEUDBUTOIRD_H__

#include "UsineNoeud.h"
#include "NoeudButoirD.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudButoirD
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudButoirD.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudButoirD : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudButoirD(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudButoirD::UsineNoeudButoirD(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudButoirD::UsineNoeudButoirD(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/ButoirD.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudButoirD::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudButoirD.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudButoirD::creerNoeud() const
{
	auto noeud = new NoeudButoirD{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDBUTOIRD_H__