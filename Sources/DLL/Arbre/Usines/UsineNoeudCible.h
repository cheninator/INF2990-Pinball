#ifndef __ARBRE_USINES_USINENOEUDCIBLE_H__
#define __ARBRE_USINES_USINENOEUDCIBLE_H__

#include "UsineNoeud.h"
#include "NoeudCible.h"

class UsineNoeudCible : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudCible(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudCible::UsineNoeudCible(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Cible.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDCIBLE_H__