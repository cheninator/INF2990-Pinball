#ifndef __VISITEURS_VISITEURROTATION_H__
#define __VISITEURS_VISITEURROTATION_H__

#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class VisiteurRotation : public VisiteurAbstrait
{
public:

	VisiteurRotation::VisiteurRotation(float angle)
	{
		angle_ = angle;
	}
	~VisiteurRotation();

	void setRotation(double angle) {};

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual bool traiter(NoeudButoir& butoir);
	virtual bool traiter(NoeudCible& cible);
	virtual bool traiter(NoeudGenerateurBille& generateur);
	virtual bool traiter(NoeudMur& mur);
	virtual bool traiter(NoeudPalette& palette);
	virtual bool traiter(NoeudPortail& portail);
	virtual bool traiter(NoeudRessort& ressort);
	virtual bool traiter(NoeudTrou& trou);

private:

	float angle_;

};


#endif //__VISITEURS_VISITEURROTATION_H__