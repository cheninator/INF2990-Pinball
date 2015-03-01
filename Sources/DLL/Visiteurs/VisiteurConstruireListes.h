///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeselectionnerTout.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURCONSTRUIRELISTES_H__
#define __VISITEURS_VISITEURCONSTRUIRELISTES_H__

#include "NoeudAbstrait.h"
#include "NoeudComposite.h"
#include "NoeudPaletteG.h"
#include "NoeudPaletteD.h"
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"
#include <set>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeselectionnerTout
/// @brief Classe pour deselectionner tous les objets de la table de rendu.
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurConstruireListes : public VisiteurAbstrait
{
public:

	/// Constructeur par defaut
	VisiteurConstruireListes(std::set<NoeudPaletteG*>* listePalettesGJ1,
		std::set<NoeudPaletteD*>* listePalettesDJ1,
		std::set<NoeudPaletteG*>* listePalettesGJ2,
		std::set<NoeudPaletteD*>* listePalettesDJ2
		);

	/// Destructeur
	~VisiteurConstruireListes();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudPaletteG* noeud);
	virtual bool traiter(NoeudPaletteD* noeud);

private:
	// Bloquer le constructeur par defaut.
	VisiteurConstruireListes();

	
	std::set<NoeudPaletteG*>* listePalettesGJ1_;
	std::set<NoeudPaletteD*>* listePalettesDJ1_;
	std::set<NoeudPaletteG*>* listePalettesGJ2_;
	std::set<NoeudPaletteD*>* listePalettesDJ2_;


};

#endif //__VISITEURS_VISITEURCONSTRUIRELISTES_H__