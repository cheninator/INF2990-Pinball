#ifndef __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__
#define __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__

#include "UsineNoeud.h"
#include "NoeudGenerateurBille.h"

class UsineNoeudGenerateurBille : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudGenerateurBille(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudGenerateurBille::UsineNoeudGenerateurBille(const std::string& nom)
	: UsineNoeud(nom, std::string("media/GenerateurBille.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__