#ifndef __ARBRE_USINES_USINENOEUDPALETTE_H__
#define __ARBRE_USINES_USINENOEUDPALETTE_H__

#include "UsineNoeud.h"
#include "NoeudPalette.h"

class UsineNoeudPalette : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudPalette(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudPalette::UsineNoeudPalette(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Palette.obj"))
{}

NoeudAbstrait* UsineNoeudPalette::creerNoeud() const
{
	auto noeud = new NoeudPalette{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUDPALETTE_H__