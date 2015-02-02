#ifndef __ARBRE_USINES_USINENOEUDTABLE_H__
#define __ARBRE_USINES_USINENOEUDTABLE_H__

#include "UsineNoeud.h"
#include "NoeudTable.h"

class UsineNoeudTable : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudTable(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudTable::UsineNoeudTable(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Table.obj"))
{}

NoeudAbstrait* UsineNoeudTable::creerNoeud() const
{
	auto noeud = new NoeudTable{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDBUTOIR_H__