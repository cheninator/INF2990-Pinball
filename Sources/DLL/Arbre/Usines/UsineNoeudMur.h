#ifndef __ARBRE_USINES_USINENOEUDMUR_H__
#define __ARBRE_USINES_USINENOEUDMUR_H__

#include "UsineNoeud.h"
#include "NoeudMur.h"

class UsineNoeudMur : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudMur(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudMur::UsineNoeudMur(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Mur.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDMUR_H__