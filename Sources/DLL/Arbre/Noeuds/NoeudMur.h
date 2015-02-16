///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author Yonni Chen
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDMUR_H__
#define __ARBRES_NOEUDS_NOEUDMUR_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudMur
/// @brief Classe qui représente un mur.
///
/// @author Yonni Chen
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudComposite
{
public:
	// Constructeur
	NoeudMur(const std::string& typeNoeud);

	// Destructeur 
	~NoeudMur();

	// Surchage de la méthode qui affiche l'objet
	virtual void afficherConcret() const;

	// Surchage de la méthode qui anime l'objet
	virtual void animer(float temps);

	// Pour accepter un visiteur
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

	/// Angle selon l'axe des X.
	float angleX_{ 0.f };

	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDMUR_H__