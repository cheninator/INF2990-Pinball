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

#include "NoeudButoir.h"
#include "NoeudCible.h"
#include "NoeudGenerateurBille.h"
#include "NoeudMur.h"
#include "NoeudPalette.h"
#include "NoeudPortail.h"
#include "NoeudRessort.h"
#include "NoeudTrou.h"

class VisiteurAbstrait
{
public:

	// Classe abstraite
	virtual ~VisiteurAbstrait() = 0;

	// Traiter une opération selon le type spécifique de l'objet en paramètre
	virtual void traiter(NoeudButoir& butoir);
	virtual void traiter(NoeudCible& cible);
	virtual void traiter(NoeudGenerateurBille& generateur);
	virtual void traiter(NoeudMur& mur);
	virtual void traiter(NoeudPalette& palette);
	virtual void traiter(NoeudPortail& portail);
	virtual void traiter(NoeudRessort& ressort);
	virtual void traiter(NoeudTrou& trou);

};


#endif // __VISITEURS_VISITEURABSTRAIT_H__

