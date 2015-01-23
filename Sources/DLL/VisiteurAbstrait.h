#ifndef __VISITEURS_VISITEURABSTRAIT_H__
#define __VISITEURS_VISITEURABSTRAIT_H__

class VisiteurAbstrait
{
public:

	// Classe abstraite
	virtual ~VisiteurAbstrait() = 0;

	// Traiter l'operation sur un type d'objet
	virtual void traiter(Butoir& butoir);
	virtual void traiter(Palette& palette);
	virtual void traiter(Mur& mur);
	virtual void traiter(Cible& cible);
	virtual void traiter(Portail& portail);
	virtual void traiter(Ressort& ressort);
	virtual void traiter(Trou& trou);
	virtual void traiter(Generateur& generateur);

};

#endif // __VISITEURS_VISITEURABSTRAIT_H__