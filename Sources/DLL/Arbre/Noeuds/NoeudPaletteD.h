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
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);

	/// Obtenir l'angle initial de la palette
	double obtenirAngleZOriginal() const { return angleZOriginal_; };

	/// Savoir si la palette est activee par une bille
	bool estActiveeParBille(NoeudAbstrait* noeud);

	/// Obtenir la  boite englobante custom.
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Retourne la fonction qui represente la palette originellement
	double fonctionDroitePaletteOriginale(NoeudAbstrait* bille);

	/// Retourne la fonction qui reprensente la palette lorsqu'elle est en mouvement
	double fonctionDroitePaletteEnMouvement(NoeudAbstrait* bille);

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

#endif // __ARBRE_NOEUDS_NOEUDPALETTED_H__