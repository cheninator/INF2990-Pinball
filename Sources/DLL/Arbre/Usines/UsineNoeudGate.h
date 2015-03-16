///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudGate.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDGATE_H__
#define __ARBRE_USINES_USINENOEUDGATE_H__

#include "UsineNoeud.h"
#include "NoeudGate.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudGate
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudGate.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudGate : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudGate(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudGate::UsineNoeudGate(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudGate::UsineNoeudGate(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Gate.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudGate::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit un NoeudGate.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudGate::creerNoeud() const
{
	auto noeud = new NoeudGate{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDGATE_H__