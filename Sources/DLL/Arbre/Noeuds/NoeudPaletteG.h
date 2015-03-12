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

	/// Activer la palette.
	void activer();

	void activerAI();
	bool estActiveeParBille(NoeudAbstrait* bille);
	/// Desactiver la palette. La faire redescendre.
	void desactiver();

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille);

	double fonctionDroitePaletteOriginale(NoeudAbstrait* bille);
	double fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille);
private:
	/// Enumeration pour contenir l'etat de la palette
	enum Etat { ACTIVE, RETOUR, INACTIVE, ACTIVE_AI, RETOUR_AI };

	/// Etat courant de la palette
	Etat etatPalette_{ INACTIVE };

	/// Angle Original pour le mouvement des palettes selon les touches du clavier
	double angleZOriginal_;
	
	/// Chronometre interne
	float timer_{ 0 };
};

#endif // __ARBRE_NOEUDS_NOEUDPALETTEG_H__