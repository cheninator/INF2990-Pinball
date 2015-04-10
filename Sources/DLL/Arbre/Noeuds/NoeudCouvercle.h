///////////////////////////////////////////////////////////////////////////
/// @file NoeudCouvercle.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDCOUVERCLE_H__
#define  __ARBRE_NOEUDS_NOEUDCOUVERCLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCouvercle
/// @brief Classe qui represente un couvercle.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudCouvercle : public NoeudComposite
{
public:
	/// Constructeur
	NoeudCouvercle(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudCouvercle();

	/// Surchage de la methode qui affiche l'objet
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Retourne l'enfant du noeud courant.
	virtual NoeudAbstrait* getEnfant(int i) { return NoeudComposite::getEnfant(i); };

	///Obtenir les 4 vecteurs de la boite englobante modifie
	virtual void obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4);
	 
private:

};

#endif // __ARBRE_NOEUDS_NOEUDCOUVERCLE_H__