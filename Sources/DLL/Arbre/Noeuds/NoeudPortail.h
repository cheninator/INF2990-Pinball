///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPORTAIL_H__
#define  __ARBRE_NOEUDS_NOEUDPORTAIL_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPortail
/// @brief Classe qui represente un portail.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPortail : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPortail(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudPortail();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Activer ou desactiver le mode debug.
	virtual void setDebug(bool debug);

	/// Redefinition de boite englobante pour objet circulaire
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);

	/// Pour la detections des collisions
	virtual aidecollision::DetailsCollision detecterCollisions(NoeudAbstrait* noeud);


private:
	
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };

	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

	/// Angle de rotation.
	float angleRotation_{ 0.f };

};

#endif // __ARBRE_NOEUDS_NOEUDPORTAIL_H__