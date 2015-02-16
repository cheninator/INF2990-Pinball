///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPaletteD.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPALETTED_H__
#define __ARBRE_USINES_USINENOEUDPALETTED_H__

#include "UsineNoeud.h"
#include "NoeudPaletteD.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPaletteD
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudPaletteD.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPaletteD : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudPaletteD(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudPaletteD::UsineNoeudPaletteD(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudPaletteD::UsineNoeudPaletteD(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/PaletteD.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPaletteD::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudPaletteD.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPaletteD::creerNoeud() const
{
	auto noeud = new NoeudPaletteD{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDPALETTED_H__