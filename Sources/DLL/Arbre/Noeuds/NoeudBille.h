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
/// @brief Classe qui représente une bille.
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

	/// Surchage de la méthode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la méthode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__