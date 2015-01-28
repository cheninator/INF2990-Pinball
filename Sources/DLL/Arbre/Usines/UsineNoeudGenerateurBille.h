#ifndef __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__
#define __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__

#include "UsineNoeud.h"
#include "NoeudGenerateurBille.h"

class UsineNoeudGenerateurBille : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudGenerateurBille(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudGenerateurBille::UsineNoeudGenerateurBille(const std::string& nom)
	: UsineNoeud(nom, std::string("media/GenerateurBille.obj"))
{}

NoeudAbstrait* UsineNoeudGenerateurBille::creerNoeud() const
{
	auto noeud = new NoeudGenerateurBille{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__