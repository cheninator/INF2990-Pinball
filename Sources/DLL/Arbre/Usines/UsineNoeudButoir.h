#ifndef __ARBRE_USINES_USINENOEUDBUTOIR_H__
#define __ARBRE_USINES_USINENOEUDBUTOIR_H__

#include "UsineNoeud.h"
#include "NoeudButoir.h"

class UsineNoeudButoir : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudButoir(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudButoir::UsineNoeudButoir(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Butoir.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDBUTOIR_H__