#ifndef __ARBRE_USINES_USINENOEUDPORTAIL_H__
#define __ARBRE_USINES_USINENOEUDPORTAIL_H__

#include "UsineNoeud.h"
#include "NoeudPortail.h"

class UsineNoeudPortail : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudPortail(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudPortail::UsineNoeudPortail(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Portail.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDPORTAIL_H__