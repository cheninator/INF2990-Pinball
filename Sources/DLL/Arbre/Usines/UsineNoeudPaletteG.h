///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPaletteG.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPALETTEG_H__
#define __ARBRE_USINES_USINENOEUDPALETTEG_H__

#include "UsineNoeud.h"
#include "NoeudPaletteG.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPaletteG
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudPaletteG.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPaletteG : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudPaletteG(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudPaletteG::UsineNoeudPaletteG(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudPaletteG::UsineNoeudPaletteG(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/PaletteG.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPaletteG::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit une NoeudPaletteG.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPaletteG::creerNoeud() const
{
	auto noeud = new NoeudPaletteG{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDPALETTED_H__