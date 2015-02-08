///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudConeCube.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDCONECUBE_H__
#define __ARBRE_USINES_USINENOEUDCONECUBE_H__


#include "UsineNoeud.h"
#include "NoeudConeCube.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudConeCube
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudConeCube.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class UsineNoeudConeCube : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudConeCube(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudConeCube::UsineNoeudConeCube(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudConeCube::UsineNoeudConeCube(const std::string& nom)
: UsineNoeud(nom, std::string{"media/objets/Cubecone.obj"})
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudConeCube::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudConeCube::creerNoeud() const
{
	auto noeud = new NoeudConeCube{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUDCONECUBE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
