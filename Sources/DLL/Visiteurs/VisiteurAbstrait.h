///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author The Ballers
/// @date 2015-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURABSTRAIT_H__
#define __VISITEURS_VISITEURABSTRAIT_H__

class NoeudAbstrait;
class NoeudButoir;
class NoeudCible;
class NoeudGenerateurBille;
class NoeudMur;
class NoeudPalette;
class NoeudPortail;
class NoeudRessort;
class NoeudTrou;

class VisiteurAbstrait
{
public:

	VisiteurAbstrait(){};

	// Classe abstraite
	virtual ~VisiteurAbstrait(){};

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual bool traiter(NoeudAbstrait& noeud) { return false; };
	virtual bool traiter(NoeudButoir& butoir) { return false; };
	virtual bool traiter(NoeudCible& cible) { return false; };
	virtual bool traiter(NoeudGenerateurBille& generateur) { return false; };
	virtual bool traiter(NoeudMur& mur) { return false; };
	virtual bool traiter(NoeudPalette& palette) { return false; };
	virtual bool traiter(NoeudPortail& portail) { return false; };
	virtual bool traiter(NoeudRessort& ressort) { return false; };
	virtual bool traiter(NoeudTrou& trou) { return false; };
};


#endif // __VISITEURS_VISITEURABSTRAIT_H__

