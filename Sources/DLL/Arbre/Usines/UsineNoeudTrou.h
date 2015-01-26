#ifndef __ARBRE_USINES_USINENOEUDTROU_H__
#define __ARBRE_USINES_USINENOEUDTROU_H__

#include "UsineNoeud.h"
#include "NoeudTrou.h"

class UsineNoeudTrou : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudTrou(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudTrou::UsineNoeudTrou(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Trou.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDTROU_H__