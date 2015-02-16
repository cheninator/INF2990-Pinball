///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirCirculaire.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__
#define __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirCirculaire
/// @brief Classe qui représente un butoir circulaire.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudButoirCirculaire : public NoeudComposite
{
public:
	/// Constructeur
	NoeudButoirCirculaire(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudButoirCirculaire();

	/// Surchage de la méthode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la méthode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:
	
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };

	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__