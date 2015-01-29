#ifndef __VISITEURS_VISITEURDEPLACEMENT_H__
#define __VISITEURS_VISITEURDEPLACEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurDeplacement : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : aucun déplacement
	VisiteurDeplacement();

	// Constructeur par paramètre : spécifiez un vecteur de déplacement
	VisiteurDeplacement(glm::dvec3 dep);

	// Destructeur
	~VisiteurDeplacement();

	// Méthode d'acces
	float getDeplacementX() { return deplacement_[0]; };
	float getDeplacementY() { return deplacement_[1]; };
	float getDeplacementZ() { return deplacement_[2]; };
	glm::dvec3 getDeplacement() { return deplacement_; };

	// Méthode de modifications
	void setDeplacementX(float x) { deplacement_[0] = x; };
	void setDeplacementY(float y) { deplacement_[1] = y; };
	void setDeplacementZ(float z) { deplacement_[2] = z; };
	void setDeplacement(glm::dvec3 dep) { deplacement_ = dep; };

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual bool traiter(NoeudAbstrait& noeud);
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