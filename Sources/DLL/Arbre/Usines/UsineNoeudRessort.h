#ifndef __ARBRE_USINES_USINENOEUDRESSORT_H__
#define __ARBRE_USINES_USINENOEUDRESSORT_H__

#include "UsineNoeud.h"
#include "NoeudRessort.h"

class UsineNoeudRessort : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudRessort(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudRessort::UsineNoeudRessort(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Ressort.obj"))
{}

NoeudAbstrait* UsineNoeudRessort::creerNoeud() const
{
	auto noeud = new NoeudRessort{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDRESSORT_H__