///////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirD.h
/// @author The Ballers
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
/// @brief Classe qui represente un butoir droit.
///
/// @author The Ballers
/// @date 2015-01-19
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudButoirD : public NoeudComposite
{
public:

	/// Constructeur a partir du type du noeud.
	NoeudButoirD(const std::string& typeNoeud);

	/// Destructeur.
	~NoeudButoirD();

	/// Affiche le butoir.
	virtual void afficherConcret() const;

	/// Effectue l'animation du butoir.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Generer les boites englobantes de façon différente pour le butoir triangulaire
	//Obtenir les 4 vecteurs de la boite englobante modifie
	virtual void obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4);

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille);

private:

	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };

};

#endif // __ARBRE_NOEUDS_NOEUDBUTOIRD_H__