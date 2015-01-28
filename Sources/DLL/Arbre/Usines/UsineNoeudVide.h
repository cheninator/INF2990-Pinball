#ifndef __ARBRE_USINES_USINENOEUDVIDE_H__
#define __ARBRE_USINES_USINENOEUDVIDE_H__

#include "UsineNoeud.h"
#include "NoeudVide.h"

class UsineNoeudVide : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudVide(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudVide::UsineNoeudVide(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Vide.obj"))
{}

#endif // __ARBRE_USINES_USINENOEUDVIDE_H__