#ifndef __VISITEURS_VISITEURDEPLACEMENT_H__
#define __VISITEURS_VISITEURDEPLACEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	VisiteurDeplacement(glm::dvec3 dep);
	~VisiteurDeplacement();

	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudButoir& butoir);
	virtual bool traiter(NoeudCible& cible);
	virtual bool traiter(NoeudGenerateurBille& generateur);
	virtual bool traiter(NoeudMur& mur);
	virtual bool traiter(NoeudPalette& palette);
	virtual bool traiter(NoeudPortail& portail);
	virtual bool traiter(NoeudRessort& ressort);
	virtual bool traiter(NoeudTrou& trou);

private:

	glm::dvec3 deplacement_;

};


#endif //__VISITEURS_VISITEURDEPLACEMENT_H__