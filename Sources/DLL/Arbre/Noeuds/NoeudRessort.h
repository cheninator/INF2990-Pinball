///////////////////////////////////////////////////////////////////////////
/// @file NoeudRessort.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDRESSORT_H__
#define  __ARBRE_NOEUDS_NOEUDRESSORT_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRessort
/// @brief Classe qui represente un ressort.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudRessort : public NoeudComposite
{
public:
	/// Constructeur
	NoeudRessort(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudRessort();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Met le ressort en etat de compression quand on appuie sur la touche
	void compresser();

	/// Relache le ressort quand on relache la touche.
	void relacher();

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);

private:
	enum EtatRessort { EN_COMPRESSION, EN_DECOMPRESSION, AU_REPOS, LANCER_BILLE };

	EtatRessort etatRessort_{ AU_REPOS };

	double scaleYOriginal_;
	glm::dvec3 positionOriginale_;
	glm::dvec3 translationCompression_;
	double longueurOriginale_;
	double distanceCompression_; // sera utilisee pour la physique

	/// Angle selon l'axe des X.
	float angleX_{ 0.f };

	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };

	/// Angle de rotation.
	float angleRotation_{ 0.f };
};

#endif // __ARBRE_NOEUDS_NOEUDRESSORT_H__