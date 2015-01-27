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

	// Classe abstraite
	virtual ~VisiteurAbstrait();

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual bool traiter(NoeudButoir& butoir);
	virtual bool traiter(NoeudCible& cible);
	virtual bool traiter(NoeudGenerateurBille& generateur);
	virtual bool traiter(NoeudMur& mur);
	virtual bool traiter(NoeudPalette& palette);
	virtual bool traiter(NoeudPortail& portail);
	virtual bool traiter(NoeudRessort& ressort);
	virtual bool traiter(NoeudTrou& trou);
};


#endif // __VISITEURS_VISITEURABSTRAIT_H__

