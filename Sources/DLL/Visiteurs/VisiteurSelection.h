#ifndef __VISITEURS_VISITEURSELECTION_H__
#define __VISITEURS_VISITEURSELECTION_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurSelection : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : aucun déplacement
	VisiteurSelection();

	// Destructeur
	~VisiteurSelection();

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudButoir* butoir);
	virtual bool traiter(NoeudCible* cible);
	virtual bool traiter(NoeudGenerateurBille* generateur);
	virtual bool traiter(NoeudMur* mur);
	virtual bool traiter(NoeudPalette* palette);
	virtual bool traiter(NoeudPortail* portail);
	virtual bool traiter(NoeudRessort* ressort);
	virtual bool traiter(NoeudTrou* trou);
	virtual bool traiter(NoeudTable* table);

private:
	
	// Paramètre spécifiques?

};


#endif //__VISITEURS_VISITEURSELECTION_H__