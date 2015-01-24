#ifndef __VISITEURS_VISITEURABSTRAIT_H__
#define __VISITEURS_VISITEURABSTRAIT_H__

class VisiteurAbstrait
{
public:

	// Classe abstraite
	virtual ~VisiteurAbstrait() = 0;

	// Traiter l'operation sur un type d'objet
	virtual void traiter(NoeudButoir& butoir);
	virtual void traiter(NoeudPalette& palette);
	virtual void traiter(NoeudMur& mur);
	virtual void traiter(NoeudCible& cible);
	virtual void traiter(NoeudPortail& portail);
	virtual void traiter(NoeudRessort& ressort);
	virtual void traiter(NoeudTrou& trou);
	virtual void traiter(NoeudGenerateur& generateur);

};

#endif // __VISITEURS_VISITEURABSTRAIT_H__