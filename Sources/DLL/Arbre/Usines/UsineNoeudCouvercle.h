#ifndef __ARBRE_USINES_USINENOEUDCOUVERCLE_H__
#define __ARBRE_USINES_USINENOEUDCOUVERCLE_H__

#include "UsineNoeud.h"
#include "NoeudCouvercle.h"

class UsineNoeudCouvercle : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudCouvercle(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudCouvercle::UsineNoeudCouvercle(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Couvercle.obj"))
{}

NoeudAbstrait* UsineNoeudCouvercle::creerNoeud() const
{
	auto noeud = new NoeudCouvercle{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDCOUVERCLE_H__