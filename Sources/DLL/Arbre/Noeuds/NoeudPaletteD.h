///////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteD.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDPALETTED_H__
#define  __ARBRE_NOEUDS_NOEUDPALETTED_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteD
/// @brief Classe qui represente une palette droite.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteD : public NoeudComposite
{
public:
	/// Constructeur
	NoeudPaletteD(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudPaletteD();

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

	/// Modifier le comportement pour que ce soit un joueur virtuel
	void activerJoueurVirtuel(bool active) { estJoueurVirtuel = active; };

	/// Savoir si la palette vient tout juste d'etre construit
	bool obtenirInitial() const { return initial_; };

	/// Assigner l'angle original de la palette apres la construction
	void assignerAngleOriginal(double angle) { angle = angleZOriginal_; };


	double fonctionDroitePaletteOriginale(NoeudAbstrait* bille);
	double fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille);

private:

	/// Angle Original pour le mouvement des palettes selon les touches du clavier
	double angleZOriginal_;

	/// Information concernant l'état d'activation de la palette
	bool estActive, estJoueurVirtuel, initial_;

	/// Information des vitesses de monte et de descente de la palette
	glm::dvec3 vitesseMonteAngulaire_;
	glm::dvec3 vitesseDescenteAngulaire_;

	/// Chronometre interne
	float timer_{ 0 };
};

#endif // __ARBRE_NOEUDS_NOEUDPALETTED_H__