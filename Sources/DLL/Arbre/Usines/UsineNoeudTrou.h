///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudTrou.h
/// @author Emilio Rivera
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
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type Trou.
///
/// @author Emilio Rivera
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudTrou : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudTrou(const std::string& nom);
	/// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudTrou::UsineNoeudTrou(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudTrou::UsineNoeudTrou(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Trou.obj"))
{}

NoeudAbstrait* UsineNoeudTrou::creerNoeud() const
{
	auto noeud = new NoeudTrou{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDTROU_H__