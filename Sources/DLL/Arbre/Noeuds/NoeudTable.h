///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDTABLE_H__
#define  __ARBRE_NOEUDS_NOEUDTABLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Classe qui represente une table.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudTable : public NoeudComposite
{
public:
	/// Constructeur
	NoeudTable(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudTable();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Retourne l'enfant du noeud courant.
	virtual NoeudAbstrait* getEnfant(int i) { return NoeudComposite::getEnfant(i); };

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

#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__