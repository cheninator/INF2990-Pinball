#ifndef __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__
#define __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__

#include "UsineNoeud.h"
#include "NoeudButoirCirculaire.h"

class UsineNoeudButoirCirculaire : public UsineNoeud
{
public:
	// Constructeur
	inline UsineNoeudButoirCirculaire(const std::string& nom);
	// Création d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};


inline UsineNoeudButoirCirculaire::UsineNoeudButoirCirculaire(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/ButoirCirculaire.obj"))
{}

NoeudAbstrait* UsineNoeudButoirCirculaire::creerNoeud() const
{
	auto noeud = new NoeudButoirCirculaire{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}



#endif // __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__