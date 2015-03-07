///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPortailTorus.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPORTAILTORUS_H__
#define __ARBRE_USINES_USINENOEUDPORTAILTORUS_H__

#include "UsineNoeud.h"
#include "NoeudPortailTorus.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPortailTorus
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type UsineNoeudPortailTorus.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPortailTorus : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudPortailTorus(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudPortailTorus::UsineNoeudPortailTorus(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudPortailTorus::UsineNoeudPortailTorus(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/PortailTorus.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPortailTorus::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudPortailTorus
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPortailTorus::creerNoeud() const
{
	auto noeud = new NoeudPortailTorus{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDPORTAILTORUS_H__