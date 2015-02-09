///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudAraignee.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDARAIGNEE_H__
#define __ARBRE_USINES_USINENOEUDARAIGNEE_H__


#include "UsineNoeud.h"
#include "NoeudAraignee.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudAraignee
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudAraignee.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudAraignee : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudAraignee(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline UsineNoeudAraignee::UsineNoeudAraignee(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudAraignee::UsineNoeudAraignee(const std::string& nom)
: UsineNoeud(nom, std::string{"media/objets/Spider.obj"})
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudAraignee::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudAraignee::creerNoeud() const
{
	auto noeud = new NoeudAraignee{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUDARAIGNEE_H__
