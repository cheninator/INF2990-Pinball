///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirG.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDBUTOIRG_H__
#define __ARBRE_NOEUDS_NOEUDBUTOIRG_H__


#include "NoeudComposite.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirG
/// @brief Classe qui représente un butoir.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudButoirG : public NoeudComposite
{
public:

	/// Constructeur à partir du type du noeud.
	NoeudButoirG(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudButoirG();

	/// Affiche le butoir.
	virtual void afficherConcret() const;

	/// Effectue l'animation du butoir.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };

};

#endif // __ARBRE_NOEUDS_NOEUDBUTOIRG_H__