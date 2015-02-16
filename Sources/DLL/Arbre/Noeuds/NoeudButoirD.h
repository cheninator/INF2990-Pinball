///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirD.h
/// @author Emilio Rivera
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDBUTOIRD_H__
#define __ARBRE_NOEUDS_NOEUDBUTOIRD_H__


#include "NoeudComposite.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirD
/// @brief Classe qui représente un butoir droit.
///
/// @author Emilio Rivera
/// @date 2015-01-19
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudButoirD : public NoeudComposite
{
public:

	/// Constructeur à partir du type du noeud.
	NoeudButoirD(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudButoirD();

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

#endif // __ARBRE_NOEUDS_NOEUDBUTOIRD_H__