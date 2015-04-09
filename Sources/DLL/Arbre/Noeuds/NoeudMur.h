///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author The Ballers
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
/// @brief Classe qui represente un mur.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudComposite
{
public:
	/// Constructeur
	NoeudMur(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudMur();

	/// Surchage de la methode qui affiche l'objet
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet
	virtual void animer(float temps);

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);

	/// Pour accepter un visiteur
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