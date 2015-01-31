#ifndef __ARBRE_USINES_USINENOEUDMUR_H__
#define __ARBRE_USINES_USINENOEUDMUR_H__

#include "UsineNoeud.h"
#include "NoeudMur.h"

class UsineNoeudMur : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudMur(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudMur::UsineNoeudMur(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Mur.obj"))
{}

NoeudAbstrait* UsineNoeudMur::creerNoeud() const
{
	auto noeud = new NoeudMur{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDMUR_H__