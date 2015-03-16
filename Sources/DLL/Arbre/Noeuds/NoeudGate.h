///////////////////////////////////////////////////////////////////////////
/// @file NoeudGate.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDGATE_H__
#define __ARBRES_NOEUDS_NOEUDGATE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudGate
/// @brief Classe qui represente une Gate.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudGate : public NoeudComposite
{
public:
	/// Constructeur
	NoeudGate(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudGate();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille);

	/// Pour la detections des collisions
	virtual aidecollision::DetailsCollision detecterCollisions(NoeudAbstrait* noeud);


private:

	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRES_NOEUDS_NOEUDGATE_H__