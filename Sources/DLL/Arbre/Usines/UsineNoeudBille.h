#ifndef __ARBRE_USINES_BILLE_H__
#define __ARBRE_USINES_BILLE_H__

#include "UsineNoeud.h"
#include "NoeudBille.h"

class UsineNoeudBille : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudBille(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudBille::UsineNoeudBille(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Bille.obj"))
{}

NoeudAbstrait* UsineNoeudBille::creerNoeud() const
{
	auto noeud = new NoeudBille{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUDBILLE_H__