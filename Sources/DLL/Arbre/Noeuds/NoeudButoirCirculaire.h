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
/// @brief Classe qui represente un butoir circulaire.
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

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Redefinition de boite englobante pour objet circulaire
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Pour la detections des collisions
	virtual aidecollision::DetailsCollision detecterCollisions(NoeudAbstrait* noeud);

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille);

private:
	
	// Pour l'animation
	enum Etat { ALLER, RETOUR, INITIAL };
	Etat etatButoir_ { ALLER };
	Etat etatPrecedentButoir_ { INITIAL };
	float compteurAnimation { -1 };
	float scalePrecedentMax { 0 };
};

#endif // __ARBRES_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__