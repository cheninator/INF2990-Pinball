#ifndef __ARBRE_USINES_USINENOEUDPALETTE_H__
#define __ARBRE_USINES_USINENOEUDPALETTE_H__

#include "UsineNoeud.h"
#include "NoeudPalette.h"

class UsineNoeudPalette : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudPalette(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudPalette::UsineNoeudPalette(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Palette.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDPALETTE_H__