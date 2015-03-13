///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteG.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPALETTEG_H__
#define  __ARBRE_NOEUDS_NOEUDPALETTEG_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteG
/// @brief Classe qui represente une palette gauche.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteG : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPaletteG(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudPaletteG();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Accepte un joueur virtuel
	virtual bool accepterJoueurVirtuel(JoueurVirtuel* joueur);

	/// Activer la palette.
	void activer();

	/// Desactiver la palette.
	void desactiver();

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille);

	/// Obtenir l'angle initial de la palette
	double obtenirAngleZOriginal() const { return angleZOriginal_; };

	/// Modifier la vitesse de monte angulaire de la palette
	void assignerVitesseMonteAngulaire(glm::dvec3 vitesse) { vitesseMonteAngulaire_ = vitesse; };

	/// Modifier la vitesse de descente angulaire de la palette
	void assignerVitesseDescenteAngulaire(glm::dvec3 vitesse) { vitesseDescenteAngulaire_ = vitesse; };




	double fonctionDroitePaletteOriginale(NoeudAbstrait* bille);
	double fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille);

private:

	/// Angle Original pour le mouvement des palettes selon les touches du clavier
	double angleZOriginal_;

	/// Information concernant l'état d'activation de la palette
	bool estActive;
	
	/// Information des vitesses de monte et de descente de la palette
	glm::dvec3 vitesseMonteAngulaire_;
	glm::dvec3 vitesseDescenteAngulaire_;

	/// Chronometre interne
	float timer_{ 0 };

};

#endif // __ARBRE_NOEUDS_NOEUDPALETTEG_H__