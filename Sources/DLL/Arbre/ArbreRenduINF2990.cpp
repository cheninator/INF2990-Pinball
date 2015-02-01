///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"

#include "Usines/UsineNoeudAraignee.h"
#include "Usines/UsineNoeudButoir.h"
#include "Usines/UsineNoeudButoirCirculaire.h"
#include "Usines/UsineNoeudCible.h"
#include "Usines/UsineNoeudConeCube.h"
#include "Usines/UsineNoeudBille.h"
#include "Usines/UsineNoeudGenerateurBille.h"
#include "Usines/UsineNoeudMur.h"
#include "Usines/UsineNoeudPalette.h"
#include "Usines/UsineNoeudPortail.h"
#include "Usines/UsineNoeudRessort.h"
#include "Usines/UsineNoeudTrou.h"
#include "Usines/UsineNoeudVide.h"
#include "Usines/UsineNoeudTable.h"

#include "EtatOpenGL.h"


/// La chaîne représentant les types
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
const std::string ArbreRenduINF2990::NOM_BUTOIR{ "butoir" };
const std::string ArbreRenduINF2990::NOM_BUTOIRCIRCULAIRE{ "butoircirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
const std::string ArbreRenduINF2990::NOM_BILLE{ "bille" };
const std::string ArbreRenduINF2990::NOM_GENERATEURBILLE{ "generateurbille" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PALETTE{ "palette" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_VIDE{ "vide" };
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeudAraignee{ NOM_ARAIGNEE });
	ajouterUsine(NOM_BUTOIR, new UsineNoeudButoir{ NOM_BUTOIR });
	ajouterUsine(NOM_BUTOIRCIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIRCIRCULAIRE });
	ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	ajouterUsine(NOM_CONECUBE, new UsineNoeudConeCube{ NOM_CONECUBE });
	ajouterUsine(NOM_BILLE, new UsineNoeudBille{ NOM_BILLE });
	ajouterUsine(NOM_GENERATEURBILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEURBILLE });
	ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	ajouterUsine(NOM_PALETTE, new UsineNoeudPalette{ NOM_PALETTE });
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	ajouterUsine(NOM_VIDE, new UsineNoeudTrou{ NOM_VIDE });
	ajouterUsine(NOM_TABLE, new UsineNoeudTable{ NOM_TABLE });
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	NoeudAbstrait* noeud{ creerNoeud(NOM_TABLE) };
	//noeud->ajouter(creerNoeud(NOM_CONECUBE));
	ajouter(noeud);
	
}

NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position)
{
	if (position > enfants_.size() || position < 0)
		return nullptr;
	else
		return enfants_[position];
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
