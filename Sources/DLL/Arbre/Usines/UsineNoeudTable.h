///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudTable.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDTABLE_H__
#define __ARBRE_USINES_USINENOEUDTABLE_H__

#include "UsineNoeud.h"
#include "NoeudTable.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudTable
/// @brief Classe qui represente une usine capable de creer des noeuds de
///        type NoeudTable.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudTable : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudTable(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

///////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudTable::UsineNoeudTable(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe de base
/// et donner des valeurs par defaut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
inline UsineNoeudTable::UsineNoeudTable(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Table.obj"))
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudTable::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine, soit une NoeudTable.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudTable::creerNoeud() const
{
	auto noeud = new NoeudTable{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	utilitaire::BoiteEnglobante boite;
	noeud->obtenirBoiteModele(boite.coinMax, glm::dvec3(), boite.coinMin, glm::dvec3());
	SingletonGlobal::obtenirInstance()->setBoiteTable(boite);
	return noeud;
}

#endif // __ARBRE_USINES_USINENOEUDTABLE_H__