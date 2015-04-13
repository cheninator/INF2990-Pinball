////////////////////////////////////////////////
/// @file   VisiteurDeselectionnerTout.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurConstruireListes.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
///
/// Constructeur par defaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurConstruireListes::VisiteurConstruireListes()
{
	// Bloque
}


VisiteurConstruireListes::VisiteurConstruireListes(std::set<NoeudPaletteG*>* listePalettesGJ1,
	std::set<NoeudPaletteD*>* listePalettesDJ1,
	std::set<NoeudPaletteG*>* listePalettesGJ2,
	std::set<NoeudPaletteD*>* listePalettesDJ2)
:listePalettesGJ1_{ listePalettesGJ1 },
 listePalettesDJ1_{ listePalettesDJ1 },
 listePalettesGJ2_{ listePalettesGJ2 },
 listePalettesDJ2_{ listePalettesDJ2 }
{
	listePalettesGJ1_->clear();
	listePalettesDJ1_->clear();
	listePalettesGJ2_->clear();
	listePalettesDJ2_->clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
///
/// Destructeur vide.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurConstruireListes::~VisiteurConstruireListes()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] arbre : L'arbre de rendu a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurConstruireListes::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurConstruireListes::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudAbstrait* noeud)
///
/// Ce visiteur deselectionne un noeud.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurConstruireListes::traiter(NoeudAbstrait*)
{
	return true;
}


bool VisiteurConstruireListes::traiter(NoeudPaletteG* noeud)
{
	if (!noeud->getColorShift())
		listePalettesGJ1_->insert(noeud);
	else
		listePalettesGJ2_->insert(noeud);
	return true;
}

bool VisiteurConstruireListes::traiter(NoeudPaletteD* noeud)
{
	if (!noeud->getColorShift())
		listePalettesDJ1_->insert(noeud);
	else
		listePalettesDJ2_->insert(noeud);
	return true;
}