#ifndef __VISITEURS_VISITEURROTATION_H__
#define __VISITEURS_VISITEURROTATION_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurRotation : public VisiteurAbstrait
{
public:

	// Constructeur par défaut : Aucune rotation
	VisiteurRotation();

	// Constructeur par paramètre : spécifiez l'angle, l'axe et le sens
	VisiteurRotation(float angle, char axe, bool sensPositif);

	// Destructeur
	~VisiteurRotation();

	// Méthode d'accès
	double getRotation() { return angle_; };
	char getAxe() { return axe_; };
	bool getSens() { return sensPositif_; };

	// Méthode de modifications
	void setRotation(double angle) { angle_ = angle; };
	void setAxe(char axe) { axe_ = axe; }
	void setSens(bool estPositif){ sensPositif_ = estPositif; }

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

	double angle_;
	char axe_;
	bool sensPositif_;

};


#endif //__VISITEURS_VISITEURROTATION_H__