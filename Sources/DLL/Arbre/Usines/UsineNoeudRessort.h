#ifndef __ARBRE_USINES_USINENOEUDRESSORT_H__
#define __ARBRE_USINES_USINENOEUDRESSORT_H__

#include "UsineNoeud.h"
#include "NoeudRessort.h"

class UsineNoeudRessort : public UsineNoeud
{
public:
	// Constructeur
	UsineNoeudRessort(const std::string& nom);
	// Création d'un noeud
	virtual NoeudAbstrait* creerNoeud() const;
};


UsineNoeudRessort::UsineNoeudRessort(const std::string& nom)
	: UsineNoeud(nom, std::string("media/Ressort.obj"))
{}




#endif // __ARBRE_USINES_USINENOEUDRESSORT_H__