#ifndef __ARBRE_USINES_USINENOEUDCIBLE_H__
#define __ARBRE_USINES_USINENOEUDCIBLE_H__

#include "UsineNoeud.h"
#include "NoeudCible.h"

class UsineNoeudCible : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudCible(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudCible::UsineNoeudCible(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Cible.obj"))
{}

NoeudAbstrait* UsineNoeudCible::creerNoeud() const
{
	auto noeud = new NoeudCible{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDCIBLE_H__