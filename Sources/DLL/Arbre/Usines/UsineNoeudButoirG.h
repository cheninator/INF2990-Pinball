///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoirG.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBUTOIRG_H__
#define __ARBRE_USINES_USINENOEUDBUTOIRG_H__

#include "UsineNoeud.h"
#include "NoeudButoirG.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudButoirG
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudButoirG.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudButoirG : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudButoirG(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudButoirG::UsineNoeudButoirG(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudButoirG::UsineNoeudButoirG(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/ButoirG.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudButoirG::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudButoirG.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudButoirG::creerNoeud() const
{
	auto noeud = new NoeudButoirG{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDBUTOIRG_H__