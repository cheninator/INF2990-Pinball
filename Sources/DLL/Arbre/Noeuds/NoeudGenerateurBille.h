///////////////////////////////////////////////////////////////////////////
/// @file NoeudGenerateurBille.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDGENERATEURBILLE_H__
#define __ARBRES_NOEUDS_NOEUDGENERATEURBILLE_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudGenerateurBille
/// @brief Classe qui represente un generateur de bille.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudGenerateurBille : public NoeudComposite
{
public:
	/// Constructeur
	NoeudGenerateurBille(const std::string& typeNoeud);

	// Destructeur 
	~NoeudGenerateurBille();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);
	
	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:
	int direction_; // between 0 and 3
	int power_; // between -5 and 5
};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__