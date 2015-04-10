///////////////////////////////////////////////////////////////////////////
/// @file NoeudBille.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDBILLE_H__
#define __ARBRES_NOEUDS_NOEUDBILLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudBille
/// @brief Classe qui represente une bille.
///
/// @author The Ballers
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudBille : public NoeudComposite
{
public:
	/// Constructeur
	NoeudBille(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudBille();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Activer ou desactiver le mode debug.
	virtual void setDebug( bool debug);

	/// Activer ou desactiver le mode spotLight.
	virtual void setSpotLight(bool debug);

	/// Afficher la vitesse
	void afficherVitesse(glm::dvec3 nouvelleVitesse);

	/// Redefinition de boite englobante pour objet circulaire
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Traiter collisions qui implante la physique de collision bille-bille.
	void traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond = 1.0);

	/// Met a jout le pointage des collisions
	void NoeudBille::mettreAJourCollision(NoeudAbstrait* noeud);

private:
	float timerMove_{ 0 };
	bool enCreation_{ true };
	double posZinitial;
	double posZfinal;
};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__