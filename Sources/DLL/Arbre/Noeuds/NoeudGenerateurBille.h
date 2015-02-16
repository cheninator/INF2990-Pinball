///////////////////////////////////////////////////////////////////////////
/// @file NoeudGenerateurBille.h
/// @author Yonni Chen
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
/// @brief Classe qui représente un générateur de bille.
///
/// @author Yonni Chen
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

	/// Surchage de la méthode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la méthode qui anime l'objet.
	virtual void animer(float temps);
	
	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

private:

};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__