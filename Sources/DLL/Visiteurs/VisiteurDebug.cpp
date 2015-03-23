////////////////////////////////////////////////
/// @file   VisiteurDebug.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurDebug.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDebug::VisiteurDebug()
///
/// Constructeur par defaut (vide).
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDebug::VisiteurDebug()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDebug::VisiteurDebug(bool valeurDebugBille, bool valeurDebugPortail, bool valeurSpotLight)
///
/// Constructeur par parametres
///
/// @param[in] bool valeurDebugBille : Le mode debug (on/off) a mettre pour la bille
/// @param[in] bool valeurDebugPortail : Le mode debug (on/off) a mettre le portail
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDebug::VisiteurDebug(bool valeurDebugBille, bool valeurDebugPortail, bool valeurSpotLight)
{
	valeurDebugBille_ = valeurDebugBille;
	valeurDebugPortail_ = valeurDebugPortail;
	valeurSpotLight_ = valeurSpotLight;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDebug::~VisiteurDebug()
///
/// Destructeur vide 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDebug::~VisiteurDebug()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement.
///
/// @param[in] arbre : L'arbre de rendu a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDebug::traiter(ArbreRenduINF2990* arbre)
{
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurPossibilite::traiter(NoeudTable* table)
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
bool VisiteurDebug::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSelection::traiter(NoeudAbstrait* noeud)
/// @brief Cette fonction traite les enfants de l'arbre de rendu. 
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurDebug::traiter(NoeudAbstrait* noeud)
{
	std::string nomObjet(noeud->obtenirType());
	if (nomObjet == "portail")
		noeud->setDebug(valeurDebugPortail_);
	else if (nomObjet == "bille") {
		noeud->setDebug(valeurDebugBille_);
		noeud->setSpotLight(valeurSpotLight_);
	}
	return true;
}