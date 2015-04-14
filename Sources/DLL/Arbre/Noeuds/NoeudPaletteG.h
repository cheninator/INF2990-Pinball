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
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);

	/// Obtenir l'angle initial de la palette
	double obtenirAngleZOriginal() const { return angleZOriginal_; };

	/// Savoir si la palette est activee par une bille
	bool estActiveeParBille(NoeudAbstrait* noeud);

	/// Obtenir la premiere boite englobante custom de l'histoire!
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Fonction de droite pour la palette a l'etat original
	double fonctionDroitePaletteOriginale(NoeudAbstrait* bille) const;

	/// Fonction de droite pour la palette lorsqu'elle est en mouvement
	double fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille) const;

private:

	static std::vector<glm::dvec3> boiteEnglobanteModele_;

	/// Angle Original pour le mouvement des palettes selon les touches du clavier
	double angleZOriginal_;

	/// Enumeration pour contenir l'etat de la palette
	enum Etat { ACTIVE, RETOUR, INACTIVE, BLOQUEE };

	/// Etat courant de la palette
	Etat etatPalette_{ INACTIVE };

	double vitesseAngulaire_;
};

#endif // __ARBRE_NOEUDS_NOEUDPALETTEG_H__