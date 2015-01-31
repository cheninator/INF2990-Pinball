#ifndef __ARBRE_USINES_USINENOEUDBUTOIR_H__
#define __ARBRE_USINES_USINENOEUDBUTOIR_H__

#include "UsineNoeud.h"
#include "NoeudButoir.h"

class UsineNoeudButoir : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudButoir(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudButoir::UsineNoeudButoir(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Butoir.obj"))
{}

NoeudAbstrait* UsineNoeudButoir::creerNoeud() const
{
	auto noeud = new NoeudButoir{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDBUTOIR_H__