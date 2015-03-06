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
/// @brief Classe qui represente une bille.
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

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Activer ou desactiver le mode debug.
	virtual void setDebug( bool debug);
};

#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__