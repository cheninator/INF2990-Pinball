#ifndef __ARBRE_USINES_USINENOEUDPORTAIL_H__
#define __ARBRE_USINES_USINENOEUDPORTAIL_H__

#include "UsineNoeud.h"
#include "NoeudTrou.h"

class UsineNoeudPortail : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudPortail(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudPortail::UsineNoeudPortail(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Portail.obj"))
{}

NoeudAbstrait* UsineNoeudPortail::creerNoeud() const
{
	auto noeud = new NoeudTrou{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDPORTAIL_H__