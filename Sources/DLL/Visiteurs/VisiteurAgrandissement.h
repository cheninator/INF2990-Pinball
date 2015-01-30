#ifndef __VISITEURS_VISITEURAGRANDISSEMENT_H__
#define __VISITEURS_VISITEURAGRANDISSEMENT_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurAgrandissement : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : aucun agrandissement
	VisiteurAgrandissement();
	
	// Constructeur par paramètre : spécifiez l'agrandissement en X, Y et Z
	VisiteurAgrandissement(glm::dvec3 homothetie);

	// Destructeur
	~VisiteurAgrandissement();

	// Méthode d'accès
	double getAgrandissementX() { return homothetie_[0]; };
	double getAgrandissementY() { return homothetie_[1]; };
	double getAgrandissementZ() { return homothetie_[2]; };
	glm::dvec3 getAgrandissement() { return homothetie_; };

	// Méthode de modifications
	void setAgrandissementX(float x) { homothetie_[0] = x; };
	void setAgrandissementY(float y) { homothetie_[1] = y; };
	void setAgrandissementZ(float z) { homothetie_[2] = z; };
	void setAgrandissement(glm::dvec3 homothetie) { homothetie_ = homothetie; };

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
	virtual bool traiter(NoeudTable& table);

private:

	// homothetie_[0] = X   Facteur d'agrandissement selon l'axe des x
	// homothetie_[1] = Y   Facteur d'agrandissement selon l'axe des y  
	// homothetie_[2] = Z   Facteur d'agrandissement selon l'axe des z
	glm::dvec3 homothetie_;

};


#endif //__VISITEURS_VISITEURAGRANDISSEMENT_H__