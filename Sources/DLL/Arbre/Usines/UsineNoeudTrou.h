#ifndef __ARBRE_USINES_USINENOEUDTROU_H__
#define __ARBRE_USINES_USINENOEUDTROU_H__

#include "UsineNoeud.h"
#include "NoeudTrou.h"

class UsineNoeudTrou : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudTrou(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudTrou::UsineNoeudTrou(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Trou.obj"))
{}

NoeudAbstrait* UsineNoeudTrou::creerNoeud() const
{
	auto noeud = new NoeudTrou{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDTROU_H__